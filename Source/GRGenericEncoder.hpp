// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <Pothos/Framework.hpp>

#include <gnuradio/fec/generic_encoder.h>

class GRGenericEncoder: public Pothos::Block
{
    public:
        GRGenericEncoder(const gr::fec::generic_encoder::sptr& genericEncoderSPtr);
        virtual ~GRGenericEncoder();

        double rate() const;

        size_t inputSize() const;

        size_t outputSize() const;

        std::string inputConversion() const;

        std::string outputConversion() const;

        virtual void work() override;

    protected:
        gr::fec::generic_encoder::sptr _genericEncoderSPtr;
};
