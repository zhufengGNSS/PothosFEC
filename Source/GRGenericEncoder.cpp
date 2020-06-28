// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericEncoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

GRGenericEncoder::GRGenericEncoder(const gr::fec::generic_encoder::sptr& genericEncoderSPtr):
    Pothos::Block(),
    _genericEncoderSPtr(genericEncoderSPtr)
{
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericEncoder, rate));
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericEncoder, inputSize));
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericEncoder, outputSize));
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericEncoder, inputConversion));
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericEncoder, outputConversion));

    this->registerProbe("rate");
    this->registerProbe("inputSize");
    this->registerProbe("outputSize");
    this->registerProbe("inputConversion");
    this->registerProbe("outputConversion");
}

GRGenericEncoder::~GRGenericEncoder(){}

double GRGenericEncoder::rate() const
{
    return _genericEncoderSPtr->rate();
}

size_t GRGenericEncoder::inputSize() const
{
    return static_cast<size_t>(_genericEncoderSPtr->get_input_size());
}

size_t GRGenericEncoder::outputSize() const
{
    return static_cast<size_t>(_genericEncoderSPtr->get_output_size());
}

std::string GRGenericEncoder::inputConversion() const
{
    return _genericEncoderSPtr->get_input_conversion();
}

std::string GRGenericEncoder::outputConversion() const
{
    return _genericEncoderSPtr->get_output_conversion();
}

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
