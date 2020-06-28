// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericEncoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/polar_encoder_systematic.h>

#include <cstdint>
#include <vector>

class PolarEncoderSystematic: public GRGenericEncoder
{
    public:
        static Pothos::Block* make(
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions);

        PolarEncoderSystematic(
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions);
        virtual ~PolarEncoderSystematic();
};

Pothos::Block* PolarEncoderSystematic::make(
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions)
{
    return new PolarEncoderSystematic(blockSize, numInfoBits, frozenBitPositions);
}

PolarEncoderSystematic::PolarEncoderSystematic(
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions
):
    GRGenericEncoder(gr::fec::code::polar_encoder_systematic::make(
                         static_cast<int>(blockSize),
                         static_cast<int>(numInfoBits),
                         frozenBitPositions))
{
    this->setupInput(0, Pothos::DType("uint8"));
    this->setupOutput(0, Pothos::DType("uint8"));
}

PolarEncoderSystematic::~PolarEncoderSystematic(){}

//
// Registration
//

/*
 * |PothosDoc Polar Encoder (Systematic)
 *
 * |category /FEC/Polar
 * |keywords coder
 * |factory /fec/polar_encoder_systematic(blockSize,numInfoBits,frozenBitPositions)
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
static Pothos::BlockRegistry registerPolarEncoderSystematic(
    "/fec/polar_encoder_systematic",
    Pothos::Callable(&PolarEncoderSystematic::make));
