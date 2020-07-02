// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericDecoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/ldpc_decoder.h>

#include <cstdint>
#include <string>

class LDPCDecoder: public GRGenericDecoder
{
    public:
        static Pothos::Block* make(const std::string& afile, float sigma, size_t maxIterations);

        LDPCDecoder(const std::string& afile, float sigma, size_t maxIterations);
        virtual ~LDPCDecoder();

        std::string afilePath() const;

        float sigma() const;

        size_t maxIterations() const;

    private:
        std::string _afilePath;
        float _sigma;
        size_t _maxIterations;
};

Pothos::Block* LDPCDecoder::make(const std::string& afile, float sigma, size_t maxIterations)
{
    return new LDPCDecoder(afile, sigma, maxIterations);
}

LDPCDecoder::LDPCDecoder(const std::string& afile, float sigma, size_t maxIterations):
    GRGenericDecoder(gr::fec::ldpc_decoder::make(afile, sigma, static_cast<int>(maxIterations))),
    _afilePath(afile),
    _sigma(sigma),
    _maxIterations(maxIterations)
{
    this->setupInput(0, Pothos::DType("float32"));
    this->setupOutput(0, Pothos::DType("uint8"));

    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCDecoder, afilePath));
    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCDecoder, sigma));
    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCDecoder, maxIterations));

    this->registerProbe("afilePath");
    this->registerProbe("sigma");
    this->registerProbe("maxIterations");
}

LDPCDecoder::~LDPCDecoder(){}

std::string LDPCDecoder::afilePath() const
{
    return _afilePath;
}

float LDPCDecoder::sigma() const
{
    return _sigma;
}

size_t LDPCDecoder::maxIterations() const
{
    return _maxIterations;
}

//
// Registration
//

/*
 * |PothosDoc LDPC Decoder
 *
 * |category /FEC/LDPC
 * |keywords coder matrix
 * |factory /fec/ldpc_decoder(afilePath,sigma,maxIterations)
 *
 * |param afilePath[AFile Path]
 * |widget FileEntry(mode=open)
 * |preview enable
 *
 * |param sigma[Sigma]
 * |widget DoubleSpinBox(minimum=0)
 * |default 0.5
 * |preview enable
 *
 * |param maxIterations[Max Iterations]
 * |widget SpinBox(minimum=1)
 * |default 50
 * |preview enable
 */
static Pothos::BlockRegistry registerLDPCDecoder(
    "/fec/ldpc_decoder",
    Pothos::Callable(&LDPCDecoder::make));
