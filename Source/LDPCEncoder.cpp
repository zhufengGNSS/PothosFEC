// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericEncoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/ldpc_encoder.h>

#include <cstdint>
#include <string>

class LDPCEncoder: public GRGenericEncoder
{
    public:
        static Pothos::Block* make(const std::string& afile);

        LDPCEncoder(const std::string& afile);
        virtual ~LDPCEncoder();

        std::string afilePath() const;

    private:
        std::string _afilePath;
};

Pothos::Block* LDPCEncoder::make(const std::string& afile)
{
    return new LDPCEncoder(afile);
}

LDPCEncoder::LDPCEncoder(const std::string& afile):
    GRGenericEncoder(gr::fec::ldpc_encoder::make(afile)),
    _afilePath(afile)
{
    this->setupInput(0, Pothos::DType("uint8"));
    this->setupOutput(0, Pothos::DType("uint8"));

    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCEncoder, afilePath));
    this->registerProbe("afilePath");
}

LDPCEncoder::~LDPCEncoder(){}

std::string LDPCEncoder::afilePath() const
{
    return _afilePath;
}

//
// Registration
//

/*
 * |PothosDoc LDPC Encoder
 *
 * |category /FEC/LDPC
 * |keywords coder matrix
 * |factory /fec/ldpc_encoder(afilePath)
 *
 * |param afilePath[AFile Path]
 * |widget FileEntry(mode=open)
 * |preview enable
 */
static Pothos::BlockRegistry registerLDPCEncoder(
    "/fec/ldpc_encoder",
    Pothos::Callable(&LDPCEncoder::make));
