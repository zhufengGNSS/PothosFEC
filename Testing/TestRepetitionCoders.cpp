// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TestUtility.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Proxy.hpp>
#include <Pothos/Testing.hpp>

#include <Poco/Thread.h>

#include <string>
#include <vector>

using namespace FECTests;

POTHOS_TEST_BLOCK("/fec/tests", test_repetition_coder_symmetry)
{
    constexpr size_t frameSize = 60;
    constexpr size_t numRepetitions = 3;
    const Pothos::DType dtype("uint8");
    constexpr std::uint8_t constant = 10;
    constexpr float apProbability = 0.5f;

    auto constantSource = Pothos::BlockRegistry::make("/blocks/constant_source", dtype);
    constantSource.call("setConstant", constant);

    auto repetitionEncoder = Pothos::BlockRegistry::make(
                                 "/fec/repetition_encoder",
                                 frameSize,
                                 numRepetitions);

    auto bytesToSymbols = Pothos::BlockRegistry::make("/comms/bytes_to_symbols");
    bytesToSymbols.call("setModulus", 8);
    bytesToSymbols.call("setBitOrder", "LSBit");

    auto converter = Pothos::BlockRegistry::make("/blocks/converter", "float32");
    auto repetitionDecoder = Pothos::BlockRegistry::make(
                                 "/fec/repetition_decoder",
                                 frameSize,
                                 numRepetitions,
                                 apProbability);

    {
        Pothos::Topology topology;
        topology.connect(constantSource, 0, repetitionEncoder, 0);
        topology.connect(repetitionEncoder, 0, bytesToSymbols, 0);
        topology.connect(bytesToSymbols, 0, converter, 0);
        topology.connect(converter, 0, repetitionDecoder, 0);

        topology.commit();
        Poco::Thread::sleep(100);
    }
}
