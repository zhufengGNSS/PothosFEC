// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Utility.hpp"

#include <Pothos/Exception.hpp>
#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <aff3ct.hpp>

#include <vector>

template <typename BT, typename RT>
class ReedSolomonDecoder: public Pothos::Block
{
    using Class = ReedSolomonDecoder<BT,RT>;

    public:
        ReedSolomonDecoder(size_t K, size_t N, size_t T, size_t dimension);
        virtual ~ReedSolomonDecoder() {}

        size_t K() const;

        size_t N() const;

        size_t T() const;

        size_t D() const;

        size_t numRedundancyBits() const;

        std::vector<int> polyGenCoeffs() const;

        void work() override;

    private:
        aff3ct::tools::RS_polynomial_generator _rsPolyGen;
        aff3ct::module::Decoder_RS_std<BT,RT> _decoder;
};

template <typename BT, typename RT>
ReedSolomonDecoder<BT,RT>::ReedSolomonDecoder(size_t K, size_t N, size_t T, size_t dimension):
    Pothos::Block(),
    _rsPolyGen(static_cast<int>(N), static_cast<int>(T)),
    _decoder(static_cast<int>(K), static_cast<int>(N), _rsPolyGen)
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

template <typename BT, typename RT>
size_t ReedSolomonDecoder<BT,RT>::K() const
{
    return static_cast<size_t>(_decoder.get_K());
}

template <typename BT, typename RT>
size_t ReedSolomonDecoder<BT,RT>::N() const
{
    return static_cast<size_t>(_decoder.get_N());
}

template <typename BT, typename RT>
size_t ReedSolomonDecoder<BT,RT>::T() const
{
    return static_cast<size_t>(_rsPolyGen.get_t());
}

template <typename BT, typename RT>
size_t ReedSolomonDecoder<BT,RT>::D() const
{
    return static_cast<size_t>(_rsPolyGen.get_d());
}

template <typename BT, typename RT>
size_t ReedSolomonDecoder<BT,RT>::numRedundancyBits() const
{
    return static_cast<size_t>(_rsPolyGen.get_n_rdncy());
}

template <typename BT, typename RT>
std::vector<int> ReedSolomonDecoder<BT,RT>::polyGenCoeffs() const
{
    return _rsPolyGen.get_g();
}

template <typename BT, typename RT>
void ReedSolomonDecoder<BT,RT>::work()
{
    const auto elems = this->workInfo().minElements;
    if(0 == elems) return;

    auto input = this->input(0);
    auto output = this->output(0);

    const auto inputFrameSize = this->N();
    const auto outputFrameSize = this->K();

    const auto maxInputFrames = elems / inputFrameSize;
    const auto maxOutputFrames = elems / outputFrameSize;
    const auto numFrames = std::min(maxInputFrames, maxOutputFrames);

    const RT* buffIn = input->buffer();
    BT* buffOut = output->buffer();

    for(size_t frameIndex = 0; frameIndex < numFrames; ++frameIndex)
    {
        _decoder.decode_siho(buffIn, buffOut);

        buffIn += inputFrameSize;
        buffOut += outputFrameSize;
    }

    input->consume(numFrames * inputFrameSize);
    output->produce(numFrames * outputFrameSize);
}

static Pothos::Block* makeReedSolomonDecoder(
    const Pothos::DType& bitDType,
    const Pothos::DType& realDType,
    size_t K,
    size_t N,
    size_t T)
{
    if(bitDType.dimension() != realDType.dimension())
    {
        throw Pothos::InvalidArgumentException("Bit and real DTypes must have the same dimension");
    }

#define IfTypeThenReturn(bitType,realType) \
    if(Pothos::DType::fromDType(bitDType, 1) == Pothos::DType(typeid(bitType))) \
        if(Pothos::DType::fromDType(realDType, 1) == Pothos::DType(typeid(realType))) \
            return new ReedSolomonDecoder<bitType,realType>(K,N,T,bitDType.dimension());

#ifdef AFF3CT_MULTI_PREC
    IfTypeThenReturn(B_8,Q_8)
    //IfTypeThenReturn(B_16,Q_16)
    //IfTypeThenReturn(B_32,Q_32)
    //IfTypeThenReturn(B_64,Q_64)
#else
    IfTypeThenReturn(B,Q)
#endif

    throw Pothos::InvalidArgumentException("Invalid dtypes: bit="+bitDType.toString()+", real="+realDType.toString());
}

static Pothos::BlockRegistry registerReedSolomonDecoder(
    "/fec/reed_solomon_decoder",
    Pothos::Callable(&makeReedSolomonDecoder));
