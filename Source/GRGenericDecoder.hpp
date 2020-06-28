// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "Utility.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/generic_decoder.h>

#include <cstdint>
#include <iostream>
#include <vector>

class GRGenericDecoder: public Pothos::Block
{
    public:
        GRGenericDecoder(const gr::fec::generic_decoder::sptr& genericDecoderSPtr);
        virtual ~GRGenericDecoder();

        double rate() const;

        int inputSize() const;

        int outputSize() const;

        int history() const;

        float shift() const;

        int inputItemSize() const;

        int outputItemSize() const;

        std::string inputConversion() const;

        std::string outputConversion() const;

        float iterations() const;

        virtual void work() override;

    protected:
        gr::fec::generic_decoder::sptr _genericDecoderSPtr;
};
