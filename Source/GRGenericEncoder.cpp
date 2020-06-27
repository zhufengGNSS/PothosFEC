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
    const auto minSize = std::max(_genericEncoderSPtr->get_input_size(), _genericEncoderSPtr->get_output_size());

    const auto elems = this->workInfo().minElements;
    if(elems < static_cast<size_t>(minSize)) return;

    const auto input = this->input(0);
    const auto output = this->output(0);

    _genericEncoderSPtr->generic_work(input, output);

    input->consume(_genericEncoderSPtr->get_input_size());
    output->produce(_genericEncoderSPtr->get_output_size());
}
