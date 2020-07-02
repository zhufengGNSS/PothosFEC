// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericDecoder.hpp"

#include <Pothos/Exception.hpp>
#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/ldpc_bit_flip_decoder.h>
#include <gnuradio/fec/ldpc_G_matrix.h>
#include <gnuradio/fec/ldpc_H_matrix.h>

#include <string>

class LDPCBitFlipDecoder: public GRGenericDecoder
{
    public:
        static Pothos::Block* make(
            const std::string& afile,
            const std::string& matrixType,
            unsigned int hMatrixGap,
            size_t maxIterations);

        LDPCBitFlipDecoder(
            const std::string& afile,
            const std::string& matrixType,
            unsigned int hMatrixGap,
            size_t maxIterations);
        virtual ~LDPCBitFlipDecoder();

        std::string afilePath() const;

        std::string matrixType() const;

        unsigned int gap() const;

        size_t maxIterations() const;

    private:
        std::string _afilePath;
        std::string _matrixType;
        unsigned int _gap;
        size_t _maxIterations;
};

Pothos::Block* LDPCBitFlipDecoder::make(
    const std::string& afile,
    const std::string& matrixType,
    unsigned int hMatrixGap,
    size_t maxIterations)
{
    return new LDPCBitFlipDecoder(afile, matrixType, hMatrixGap, maxIterations);
}

LDPCBitFlipDecoder::LDPCBitFlipDecoder(
    const std::string& afile,
    const std::string& matrixType,
    unsigned int hMatrixGap,
    size_t maxIterations
):
    GRGenericDecoder(gr::fec::generic_decoder::sptr()),
    _afilePath(afile),
    _matrixType(matrixType),
    _gap(hMatrixGap),
    _maxIterations(maxIterations)
{
    gr::fec::code::fec_mtrx_sptr fecMtrxSPtr;

    if("G" == matrixType)       fecMtrxSPtr = gr::fec::code::ldpc_G_matrix::make(afile);
    else if ("H" == matrixType) fecMtrxSPtr = gr::fec::code::ldpc_H_matrix::make(afile, hMatrixGap);
    else throw Pothos::InvalidArgumentException("Invalid matrix type: "+matrixType);

    this->_genericDecoderSPtr = gr::fec::code::ldpc_bit_flip_decoder::make(fecMtrxSPtr, _maxIterations);

    this->setupInput(0, Pothos::DType("float32"));
    this->setupOutput(0, Pothos::DType("uint8"));

    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCBitFlipDecoder, afilePath));
    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCBitFlipDecoder, matrixType));
    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCBitFlipDecoder, gap));
    this->registerCall(this, POTHOS_FCN_TUPLE(LDPCBitFlipDecoder, maxIterations));

    this->registerProbe("afilePath");
    this->registerProbe("matrixType");
    this->registerProbe("gap");
    this->registerProbe("maxIterations");
}

LDPCBitFlipDecoder::~LDPCBitFlipDecoder(){}

std::string LDPCBitFlipDecoder::afilePath() const
{
    return _afilePath;
}

std::string LDPCBitFlipDecoder::matrixType() const
{
    return _matrixType;
}

unsigned int LDPCBitFlipDecoder::gap() const
{
    return _gap;
}

size_t LDPCBitFlipDecoder::maxIterations() const
{
    return _maxIterations;
}

//
// Registration
//

/*
 * |PothosDoc LDPC Bit Flip Decoder
 *
 * |category /FEC/LDPC
 * |keywords coder matrix
 * |factory /fec/ldpc_bit_flip_decoder(afilePath,matrixType,gap,maxIterations)
 *
 * |param afilePath[AFile Path]
 * |widget FileEntry(mode=open)
 * |preview enable
 *
 * |param matrixType[Matrix Type]
 * |widget ComboBox(editable=false)
 * |option [G] "G"
 * |option [H] "H"
 * |default "G"
 * |preview enable
 *
 * |param gap[Gap] H matrix only
 * |widget SpinBox(minimum=0)
 * |default 0
 * |preview when(enum=matrixType, "H")
 *
 * |param maxIterations[Max Iterations]
 * |widget SpinBox(minimum=1)
 * |default 100
 * |preview enable
 */
static Pothos::BlockRegistry registerLDPCBitFlipDecoder(
    "/fec/ldpc_bit_flip_decoder",
    Pothos::Callable(&LDPCBitFlipDecoder::make));
