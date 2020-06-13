// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Utility.hpp"

#include <Pothos/Exception.hpp>
#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <aff3ct.hpp>

#include <cstring>
#include <vector>

template <typename BT>
class ReedSolomonEncoder: public Pothos::Block
{
    using Class = ReedSolomonEncoder<BT>;

    public:
        ReedSolomonEncoder(size_t K, size_t N, size_t T, size_t dimension);
        virtual ~ReedSolomonEncoder() {}

        size_t K() const;

        size_t N() const;

        size_t T() const;

        size_t D() const;

        size_t numRedundancyBits() const;

        std::vector<int> polyGenCoeffs() const;

        void work() override;

    private:
        aff3ct::tools::RS_polynomial_generator _rsPolyGen;
        aff3ct::module::Encoder_RS<BT> _encoder;
};

template <typename BT>
ReedSolomonEncoder<BT>::ReedSolomonEncoder(size_t K, size_t N, size_t T, size_t dimension):
    Pothos::Block(),
    _rsPolyGen(static_cast<int>(N), static_cast<int>(T)),
    _encoder(static_cast<int>(K), static_cast<int>(N), _rsPolyGen)
{
    this->setupInput(0, Pothos::DType(typeid(BT), dimension));
    this->setupOutput(0, Pothos::DType(typeid(BT), dimension));

    this->registerCall(this, POTHOS_FCN_TUPLE(Class, K));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, N));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, T));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, D));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, numRedundancyBits));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, polyGenCoeffs));

    this->registerProbe("K");
    this->registerProbe("N");
    this->registerProbe("T");
    this->registerProbe("D");
    this->registerProbe("numRedundancyBits");
    this->registerProbe("polyGenCoeffs");
}

template <typename BT>
size_t ReedSolomonEncoder<BT>::K() const
{
    return static_cast<size_t>(_encoder.get_K());
}

template <typename BT>
size_t ReedSolomonEncoder<BT>::N() const
{
    return static_cast<size_t>(_encoder.get_N());
}

template <typename BT>
size_t ReedSolomonEncoder<BT>::T() const
{
    return static_cast<size_t>(_rsPolyGen.get_t());
}

template <typename BT>
size_t ReedSolomonEncoder<BT>::D() const
{
    return static_cast<size_t>(_rsPolyGen.get_d());
}

template <typename BT>
size_t ReedSolomonEncoder<BT>::numRedundancyBits() const
{
    return static_cast<size_t>(_rsPolyGen.get_n_rdncy());
}

template <typename BT>
std::vector<int> ReedSolomonEncoder<BT>::polyGenCoeffs() const
{
    return _rsPolyGen.get_g();
}

template <typename BT>
void ReedSolomonEncoder<BT>::work()
{
    const auto elems = this->workInfo().minElements;
    if(0 == elems) return;

    auto input = this->input(0);
    auto output = this->output(0);

    const auto inputFrameSize = this->K();
    const auto outputFrameSize = this->N();

    const auto maxInputFrames = input->elements() / inputFrameSize;
    const auto maxOutputFrames = output->elements() / outputFrameSize;
    const auto numFrames = std::min(maxInputFrames, maxOutputFrames);

    const BT* buffIn = input->buffer();
    BT* buffOut = output->buffer();

    if(elems >= inputFrameSize)
    {
        for(size_t frameIndex = 0; frameIndex < numFrames; ++frameIndex)
        {
            _encoder.encode(buffIn, buffOut);

            buffIn += inputFrameSize;
            buffOut += outputFrameSize;
        }

        input->consume(numFrames * inputFrameSize);
        output->produce(numFrames * outputFrameSize);
    }
    else
    {
        // We have an incomplete frame, so leftpad the input with zeros, encode
        // this padded buffer, and pass along the part we care about.
        std::vector<BT> paddedInput(inputFrameSize, 0);
        std::vector<BT> paddedOutput(outputFrameSize, 0);

        const auto inputElemsBytes = elems*sizeof(BT);
        const auto padding = inputFrameSize - elems;
        const auto outputElems = outputFrameSize - padding;
        const auto outputElemsBytes = outputElems*sizeof(BT);

        std::memcpy(&paddedInput[padding], buffIn, inputElemsBytes);
        _encoder.encode(paddedInput.data(), paddedOutput.data());
        std::memcpy(buffOut, &paddedOutput[padding], outputElemsBytes);

        input->consume(elems);
        output->produce(outputElems);
    }
}

static Pothos::Block* makeReedSolomonEncoder(
    const Pothos::DType& dtype,
    size_t K,
    size_t N,
    size_t T)
{
#define IfTypeThenReturn(type) \
    if(Pothos::DType::fromDType(dtype, 1) == Pothos::DType(typeid(type))) \
        return new ReedSolomonEncoder<type>(K,N,T,dtype.dimension());

#ifdef AFF3CT_MULTI_PREC
    IfTypeThenReturn(B_8)
    IfTypeThenReturn(B_16)
    IfTypeThenReturn(B_32)
    IfTypeThenReturn(B_64)
#else
    IfTypeThenReturn(B)
#endif

    throw Pothos::InvalidArgumentException("Invalid dtype: "+dtype.toString());
}

static Pothos::BlockRegistry registerReedSolomonEncoder(
    "/fec/reed_solomon_encoder",
    Pothos::Callable(&makeReedSolomonEncoder));
