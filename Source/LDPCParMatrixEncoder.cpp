// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericEncoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/ldpc_par_mtrx_encoder.h>

#include <cstdint>
#include <string>

class LDPCParMatrixEncoder: public GRGenericEncoder
{
    public:
        static Pothos::Block* make(const std::string& afile, unsigned int gap);

        LDPCParMatrixEncoder(const std::string& afile, unsigned int gap);
        virtual ~LDPCParMatrixEncoder();

        std::string afilePath() const;

        unsigned int gap() const;

    private:
        std::string _afilePath;
        unsigned int _gap;
};

Pothos::Block* LDPCParMatrixEncoder::make(const std::string& afile, unsigned int gap)
{
    return new LDPCParMatrixEncoder(afile, gap);
}

LDPCParMatrixEncoder::LDPCParMatrixEncoder(const std::string& afile, unsigned int gap):
    GRGenericEncoder(gr::fec::code::ldpc_par_mtrx_encoder::make(afile, gap)),
    _afilePath(afile),
    _gap(gap)
{
    this->setupInput(0, Pothos::DType("uint8"));
    this->setupOutput(0, Pothos::DType("uint8"));

    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCParMatrixEncoder, afilePath));
    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCParMatrixEncoder, gap));

    this->registerProbe("afilePath");
    this->registerProbe("gap");
}

LDPCParMatrixEncoder::~LDPCParMatrixEncoder(){}

std::string LDPCParMatrixEncoder::afilePath() const
{
    return _afilePath;
}

unsigned int LDPCParMatrixEncoder::gap() const
{
    return _gap;
}

//
// Registration
//

/*
 * |PothosDoc LDPC Parity Matrix Encoder
 *
 * |category /FEC/LDPC
 * |keywords coder
 * |factory /fec/ldpc_par_matrix_encoder(afilePath,gap)
 *
 * |param afilePath[AFile Path]
 * |widget FileEntry(mode=open)
 * |preview enable
 *
 * |param gap[Gap]
 * |widget SpinBox(minimum=0)
 * |default 0
 * |preview enable
 */
static Pothos::BlockRegistry registerLDPCParMatrixEncoder(
    "/fec/ldpc_par_matrix_encoder",
    Pothos::Callable(&LDPCParMatrixEncoder::make));
