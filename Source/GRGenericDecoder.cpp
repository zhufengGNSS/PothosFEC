// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericDecoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

GRGenericDecoder::GRGenericDecoder(const gr::fec::generic_decoder::sptr& genericDecoderSPtr):
    Pothos::Block(),
    _genericDecoderSPtr(genericDecoderSPtr)
{
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericDecoder, rate));
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericDecoder, inputSize));
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericDecoder, outputSize));
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericDecoder, inputConversion));
    this->registerCall(this, POTHOS_FCN_TUPLE(GRGenericDecoder, outputConversion));

    this->registerProbe("rate");
    this->registerProbe("inputSize");
    this->registerProbe("outputSize");
    this->registerProbe("inputConversion");
    this->registerProbe("outputConversion");
}

GRGenericDecoder::~GRGenericDecoder(){}

double GRGenericDecoder::rate() const
{
    return _genericDecoderSPtr->rate();
}

int GRGenericDecoder::inputSize() const
{
    return _genericDecoderSPtr->get_input_size();
}

int GRGenericDecoder::outputSize() const
{
    return _genericDecoderSPtr->get_output_size();
}

int GRGenericDecoder::history() const
{
    return _genericDecoderSPtr->get_history();
}

float GRGenericDecoder::shift() const
{
    return _genericDecoderSPtr->get_shift();
}

int GRGenericDecoder::inputItemSize() const
{
    return _genericDecoderSPtr->get_input_item_size();
}

int GRGenericDecoder::outputItemSize() const
{
    return _genericDecoderSPtr->get_output_item_size();
}

std::string GRGenericDecoder::inputConversion() const
{
    return _genericDecoderSPtr->get_input_conversion();
}

std::string GRGenericDecoder::outputConversion() const
{
    return _genericDecoderSPtr->get_output_conversion();
}

void GRGenericDecoder::work()
{
    const auto inputCoderSize = _genericDecoderSPtr->get_input_size();
    const auto outputCoderSize = _genericDecoderSPtr->get_output_size();
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
        _genericDecoderSPtr->generic_work(
            input->buffer(),
            output->buffer());

        inBuff += inputCoderSize;
        outBuff += outputCoderSize;
    }

    input->consume(_genericDecoderSPtr->get_input_size() * numFrames);
    output->produce(_genericDecoderSPtr->get_output_size() * numFrames);
}
