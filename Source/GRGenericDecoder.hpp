// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <Pothos/Framework.hpp>

#include <gnuradio/fec/generic_decoder.h>

class GRGenericDecoder: public Pothos::Block
{
    public:
        GRGenericDecoder(const gr::fec::generic_decoder::sptr& genericDecoderSPtr);
        virtual ~GRGenericDecoder();

        double rate() const;

        size_t inputSize() const;

        size_t outputSize() const;

        size_t history() const;

        float shift() const;

        size_t inputItemSize() const;

        size_t outputItemSize() const;

        std::string inputConversion() const;

        std::string outputConversion() const;

        ssize_t iterations() const;

        virtual void work() override;

    protected:
        gr::fec::generic_decoder::sptr _genericDecoderSPtr;
};
