// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Utility.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/polar_encoder.h>

#include <cstdint>
#include <iostream>
#include <vector>

class PolarEncoder: public Pothos::Block
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

        void work() override;

    private:
        gr::fec::generic_encoder::sptr _polarEncoderSPtr;
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
    Pothos::Block(),
    _polarEncoderSPtr(gr::fec::code::polar_encoder::make(
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

void PolarEncoder::work()
{
    const auto minSize = std::max(_polarEncoderSPtr->get_input_size(), _polarEncoderSPtr->get_output_size());

    const auto elems = this->workInfo().minElements;
    if(elems < static_cast<size_t>(minSize)) return;

    const auto input = this->input(0);
    const auto output = this->output(0);

    _polarEncoderSPtr->generic_work(input, output);

    input->consume(_polarEncoderSPtr->get_input_size());
    output->produce(_polarEncoderSPtr->get_output_size());
}

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
