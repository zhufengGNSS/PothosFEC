// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Utility.hpp"

#include <Pothos/Exception.hpp>
#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <aff3ct.hpp>

#include <algorithm>
#include <memory>
#include <vector>

template <typename T>
class PolarEncoder: public Pothos::Block
{
    using Class = PolarEncoder<T>;

    public:
        PolarEncoder(size_t K, size_t N, const std::vector<bool>& frozenBits, bool systematic, size_t dimension);
        virtual ~PolarEncoder() = default;

        size_t K() const;

        size_t N() const;

        std::vector<bool> frozenBits() const;

        void work() override;

    private:
        std::unique_ptr<aff3ct::module::Encoder_polar<T>> _polarEncoderUPtr;

        // Not accessible through AFF3CT
        std::vector<bool> _frozenBits;
};

template <typename T>
PolarEncoder<T>::PolarEncoder(size_t K, size_t N, const std::vector<bool>& frozenBits, bool systematic, size_t dimension):
    Pothos::Block(),
    _frozenBits(frozenBits)
{
    //
    // Input validation
    //

    if(0 == K) throw Pothos::RangeException("K must be > 0");
    if(0 == N) throw Pothos::RangeException("N must be > 0");

    if(_frozenBits.size() != static_cast<size_t>(N))
    {
        throw Pothos::InvalidArgumentException("The frozen bits input must be of size N");
    }
    size_t numZeros = std::count(_frozenBits.begin(), _frozenBits.end(), false);
    if(K != numZeros)
    {
        throw Pothos::InvalidArgumentException("The number of information bits in the frozen bits must match K");
    }

    //
    // Block setup
    //

    if(systematic) _polarEncoderUPtr.reset(new aff3ct::module::Encoder_polar_sys<T>(
                                                   static_cast<int>(K),
                                                   static_cast<int>(N),
                                                   _frozenBits));
    else           _polarEncoderUPtr.reset(new aff3ct::module::Encoder_polar<T>(
                                                   static_cast<int>(K),
                                                   static_cast<int>(N),
                                                   _frozenBits));

    this->setupInput(0, Pothos::DType(typeid(T), dimension));
    this->setupOutput(0, Pothos::DType(typeid(T), dimension));

    this->registerCall(this, POTHOS_FCN_TUPLE(Class, K));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, N));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, frozenBits));

    this->registerProbe("K");
    this->registerProbe("N");
    this->registerProbe("frozenBits");
}

template <typename T>
size_t PolarEncoder<T>::K() const
{
    return static_cast<size_t>(_polarEncoderUPtr->get_K());
}

template <typename T>
size_t PolarEncoder<T>::N() const
{
    return static_cast<size_t>(_polarEncoderUPtr->get_N());
}

template <typename T>
std::vector<bool> PolarEncoder<T>::frozenBits() const
{
    return _frozenBits;
}

template <typename T>
void PolarEncoder<T>::work()
{
    const auto elems = this->workInfo().minElements;
    if(0 == elems) return;

    auto input = this->input(0);
    auto output = this->output(0);

    const auto inputLen = this->K();
    const auto outputLen = this->N();

    const auto maxInputFrames = elems / inputLen;
    const auto maxOutputFrames = elems / outputLen;
    const auto numFrames = std::min(maxInputFrames, maxOutputFrames);

    const T* buffIn = input->buffer();
    T* buffOut = output->buffer();

    for(size_t frameIndex = 0; frameIndex < numFrames; ++frameIndex)
    {
        _polarEncoderUPtr->encode(buffIn, buffOut);

        buffIn += inputLen;
        buffOut += outputLen;
    }

    input->consume(numFrames * inputLen);
    output->produce(numFrames * outputLen);
}

static Pothos::Block* makePolarEncoder(
    const Pothos::DType& dtype,
    size_t K,
    size_t N,
    const std::vector<bool>& frozenBits,
    bool systematic)
{
#define IfTypeThenReturn(T) \
    if(Pothos::DType::fromDType(dtype, 1) == Pothos::DType(typeid(T))) \
        return new PolarEncoder<T>(K, N, frozenBits, systematic, dtype.dimension());

#ifdef AFF3CT_MULTI_PREC
    IfTypeThenReturn(B_8)
    IfTypeThenReturn(B_16)
    IfTypeThenReturn(B_32)
    IfTypeThenReturn(B_64)
#else
    IfTypeThenReturn(B)
#endif

    throw Pothos::InvalidArgumentException("PolarEncoder: invalid dtype: "+dtype.name());
}

static Pothos::BlockRegistry registerPolarEncoder(
    "/fec/polar_encoder",
    Pothos::Callable(&makePolarEncoder));
