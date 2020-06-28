// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericEncoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

GRGenericEncoder::GRGenericEncoder(const gr::fec::generic_encoder::sptr& genericEncoderSPtr):
    Pothos::Block(),
    _genericEncoderSPtr(genericEncoderSPtr)
{}

GRGenericEncoder::~GRGenericEncoder(){}

void GRGenericEncoder::work()
{
    const auto inputCoderSize = _genericEncoderSPtr->get_input_size();
    const auto outputCoderSize = _genericEncoderSPtr->get_output_size();
    const auto maxCoderSize = std::max(inputCoderSize, outputCoderSize);

    const auto elems = this->workInfo().minElements;
    if(elems < static_cast<size_t>(maxCoderSize)) return;

    auto input = this->input(0);
    auto output = this->output(0);

    auto inBuff = input->buffer().as<std::uint8_t*>(); // GR needs it non-const, but it won't be updated.
    auto outBuff = output->buffer().as<std::uint8_t*>();

    const auto numFrames = elems / maxCoderSize;
    for(size_t frameIndex = 0; frameIndex < numFrames; ++frameIndex)
    {
        _genericEncoderSPtr->generic_work(
            input->buffer(),
            output->buffer());

        inBuff += inputCoderSize;
        outBuff += outputCoderSize;
    }

    input->consume(_genericEncoderSPtr->get_input_size() * numFrames);
    output->produce(_genericEncoderSPtr->get_output_size() * numFrames);
}
