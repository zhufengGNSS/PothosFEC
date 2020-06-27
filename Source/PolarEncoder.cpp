// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericEncoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/polar_encoder.h>

#include <cstdint>
#include <vector>

class PolarEncoder: public GRGenericEncoder
{
    public:
        static Pothos::Block* make(
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions,
            const std::vector<std::uint8_t>& frozenBitValues,
            bool isPacked);

        PolarEncoder(
            size_t blockSize,
            size_t numInfoBits,
            const std::vector<int>& frozenBitPositions,
            const std::vector<std::uint8_t>& frozenBitValues,
            bool isPacked);
        virtual ~PolarEncoder();
};

Pothos::Block* PolarEncoder::make(
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions,
    const std::vector<std::uint8_t>& frozenBitValues,
    bool isPacked)
{
    return new PolarEncoder(blockSize, numInfoBits, frozenBitPositions, frozenBitValues, isPacked);
}

PolarEncoder::PolarEncoder(
    size_t blockSize,
    size_t numInfoBits,
    const std::vector<int>& frozenBitPositions,
    const std::vector<std::uint8_t>& frozenBitValues,
    bool isPacked
):
    GRGenericEncoder(gr::fec::code::polar_encoder::make(
                         static_cast<int>(blockSize),
                         static_cast<int>(numInfoBits),
                         frozenBitPositions,
                         frozenBitValues,
                         isPacked))
{
    this->setupInput(0, Pothos::DType("uint8"));
    this->setupOutput(0, Pothos::DType("uint8"));
}

PolarEncoder::~PolarEncoder(){}

//
// Registration
//

/*
 * |PothosDoc Polar Encoder
 *
 * |category /FEC/Polar
 * |keywords coder
 * |factory /fec/polar_encoder(blockSize,numInfoBits,frozenBitPositions,frozenBitValues,isPacked)
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
 *
 * |param isPacked[Is packed?]
 * |widget ToggleSwitch(on="True",off="False")
 * |default false
 * |preview enable
 */
static Pothos::BlockRegistry registerPolarEncoder(
    "/fec/polar_encoder",
    Pothos::Callable(&PolarEncoder::make));
