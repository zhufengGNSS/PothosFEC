// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericDecoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/polar_decoder_sc_systematic.h>

#include <cstdint>
#include <vector>

class PolarDecoderSCSystematic: public GRGenericDecoder
{
    public:
        static Pothos::Block* make(
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions);

        PolarDecoderSCSystematic(
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions);
        virtual ~PolarDecoderSCSystematic();
};

Pothos::Block* PolarDecoderSCSystematic::make(
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions)
{
    return new PolarDecoderSCSystematic(blockSize, numInfoBits, frozenBitPositions);
}

PolarDecoderSCSystematic::PolarDecoderSCSystematic(
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions
):
    GRGenericDecoder(gr::fec::code::polar_decoder_sc_systematic::make(
                         static_cast<int>(blockSize),
                         static_cast<int>(numInfoBits),
                         frozenBitPositions))
{
    this->setupInput(0, Pothos::DType("float32"));
    this->setupOutput(0, Pothos::DType("uint8"));
}

PolarDecoderSCSystematic::~PolarDecoderSCSystematic(){}

//
// Registration
//

/*
 * |PothosDoc Polar Decoder (Systematic SC)
 *
 * |category /FEC/Polar
 * |keywords coder
 * |factory /fec/polar_decoder_sc_systematic(blockSize,numInfoBits,frozenBitPositions)
 *
 * |param blockSize[Block Size]
 * |widget SpinBox(minimum=2)
 * |default 2
 * |preview enable
 *
 * |param numInfoBits[Num Info Bits]
 * |widget SpinBox(minimum=1)
 * |default 1
 * |preview enable
 *
 * |param frozenBitPositions[Frozen Bit Positions]
 * |widget LineEdit()
 * |default [0]
 * |preview enable
 */
static Pothos::BlockRegistry registerPolarDecoderSCSystematic(
    "/fec/polar_decoder_sc_systematic",
    Pothos::Callable(&PolarDecoderSCSystematic::make));
