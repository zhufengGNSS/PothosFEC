// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericDecoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/polar_decoder_sc.h>

#include <cstdint>
#include <vector>

class PolarDecoderSC: public GRGenericDecoder
{
    public:
        static Pothos::Block* make(
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions,
            const std::vector<std::uint8_t>& frozenBitValues);

        PolarDecoderSC(
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions,
            const std::vector<std::uint8_t>& frozenBitValues);
        virtual ~PolarDecoderSC();
};

Pothos::Block* PolarDecoderSC::make(
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions,
    const std::vector<std::uint8_t>& frozenBitValues)
{
    return new PolarDecoderSC(blockSize, numInfoBits, frozenBitPositions, frozenBitValues);
}

PolarDecoderSC::PolarDecoderSC(
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions,
    const std::vector<std::uint8_t>& frozenBitValues
):
    GRGenericDecoder(gr::fec::code::polar_decoder_sc::make(
                         static_cast<int>(blockSize),
                         static_cast<int>(numInfoBits),
                         frozenBitPositions,
                         frozenBitValues))
{
    this->setupInput(0, Pothos::DType("float32"));
    this->setupOutput(0, Pothos::DType("uint8"));
}

PolarDecoderSC::~PolarDecoderSC(){}

//
// Registration
//

/*
 * |PothosDoc Polar Decoder (SC)
 *
 * |category /FEC/Polar
 * |keywords coder
 * |factory /fec/polar_decoder_sc(blockSize,numInfoBits,frozenBitPositions,frozenBitValues)
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
 *
 * |param frozenBitValues[Frozen Bit Values]
 * |widget LineEdit()
 * |default [1]
 * |preview enable
 */
static Pothos::BlockRegistry registerPolarDecoderSC(
    "/fec/polar_decoder_sc",
    Pothos::Callable(&PolarDecoderSC::make));
