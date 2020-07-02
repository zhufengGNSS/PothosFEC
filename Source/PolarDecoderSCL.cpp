// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericDecoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/polar_decoder_sc_list.h>

#include <cstdint>
#include <vector>

class PolarDecoderSCL: public GRGenericDecoder
{
    public:
        static Pothos::Block* make(
            size_t maxListSize,
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions,
            const std::vector<std::uint8_t>& frozenBitValues);

        PolarDecoderSCL(
            size_t maxListSize,
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions,
            const std::vector<std::uint8_t>& frozenBitValues);
        virtual ~PolarDecoderSCL();
};

Pothos::Block* PolarDecoderSCL::make(
    size_t maxListSize,
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions,
    const std::vector<std::uint8_t>& frozenBitValues)
{
    return new PolarDecoderSCL(maxListSize, blockSize, numInfoBits, frozenBitPositions, frozenBitValues);
}

PolarDecoderSCL::PolarDecoderSCL(
    size_t maxListSize,
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions,
    const std::vector<std::uint8_t>& frozenBitValues
):
    GRGenericDecoder(gr::fec::code::polar_decoder_sc_list::make(
                         static_cast<int>(maxListSize),
                         static_cast<int>(blockSize),
                         static_cast<int>(numInfoBits),
                         frozenBitPositions,
                         frozenBitValues))
{
    this->setupInput(0, Pothos::DType("float32"));
    this->setupOutput(0, Pothos::DType("uint8"));
}

PolarDecoderSCL::~PolarDecoderSCL(){}

//
// Registration
//

/*
 * |PothosDoc Polar Decoder (SCL)
 *
 * |category /FEC/Polar
 * |keywords coder
 * |factory /fec/polar_decoder_sc_list(maxListSize,blockSize,numInfoBits,frozenBitPositions,frozenBitValues)
 *
 * |param maxListSize[Max List Size]
 * |widget SpinBox(minimum=1)
 * |default 1
 * |preview enable
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
static Pothos::BlockRegistry registerPolarDecoderSCL(
    "/fec/polar_decoder_sc_list",
    Pothos::Callable(&PolarDecoderSCL::make));
