// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TestUtility.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Proxy.hpp>
#include <Pothos/Testing.hpp>

#include <aff3ct.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace FECTests;

template <typename BT, typename RT>
static void testReedSolomonCoderSymmetry()
{
    constexpr size_t msgLen = 512;
    constexpr size_t K = 3;
    constexpr size_t N = 7;
    constexpr size_t t = 2;

    const Pothos::DType bDType(typeid(BT));
    const Pothos::DType rDType(typeid(RT));

    std::cout << "Testing bit=" << bDType.name() << ", real=" << rDType.name() << "..." << std::endl;

    const auto randomInput = getRandomInput<BT>(msgLen);

    auto feederSource = Pothos::BlockRegistry::make("/blocks/feeder_source", bDType);
    feederSource.call("feedBuffer", randomInput);

    auto encoder = Pothos::BlockRegistry::make("/fec/reed_solomon_encoder", bDType, K, N, t);
    auto decoder = Pothos::BlockRegistry::make("/fec/reed_solomon_decoder", bDType, rDType, K, N, t);
    auto collectorSink = Pothos::BlockRegistry::make("/blocks/collector_sink", bDType);

    {
        Pothos::Topology topology;

        topology.connect(feederSource, 0, encoder, 0);
        topology.connect(encoder, 0, decoder, 0);
        topology.connect(decoder, 0, collectorSink, 0);

        topology.commit();
        POTHOS_TEST_TRUE(topology.waitInactive(0.1));
    }

    auto sinkOutput = collectorSink.call<Pothos::BufferChunk>("getBuffer");
    POTHOS_TEST_GT(sinkOutput.elements(), 0);
    /*POTHOS_TEST_EQUAL(randomInput.elements(), sinkOutput.elements());
    POTHOS_TEST_EQUALA(
        (const BT*)randomInput,
        (const BT*)sinkOutput,
        randomInput.elements());*/
}

POTHOS_TEST_BLOCK("/fec/tests", test_reedsolomon_coder_symmetry)
{
#ifdef AFF3CT_MULTI_PREC
    testReedSolomonCoderSymmetry<B_8,Q_8>();
    testReedSolomonCoderSymmetry<B_16,Q_16>();
    testReedSolomonCoderSymmetry<B_32,Q_32>();
    testReedSolomonCoderSymmetry<B_64,Q_64>();
#else
    testReedSolomonCoderSymmetry<B,Q>();
#endif
}
