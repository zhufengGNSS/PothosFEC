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

/**************************************************************************
 * Declarations
 **************************************************************************/

//
// Base
//

template <typename BitType, typename RealType>
class PolarDecoder: public Pothos::Block
{
    using Class = PolarDecoder<BitType, RealType>;

    public:
        PolarDecoder(const std::vector<bool>& frozenBits, size_t dimension);
        virtual ~PolarDecoder() = default;

        size_t K() const;

        size_t N() const;

        std::vector<bool> frozenBits() const;

        virtual void work() = 0;

    protected:
        std::unique_ptr<aff3ct::module::Decoder> _polarDecoderUPtr;

        // Not accessible through AFF3CT
        std::vector<bool> _frozenBits;

        void workSIHO();
};

//
// ASCL
//

template <typename BitType, typename RealType>
class PolarDecoderASCL: public PolarDecoder<BitType, RealType>
{
    using Class = PolarDecoderASCL<BitType, RealType>;

    public:
        PolarDecoderASCL(size_t K, size_t N, size_t L, const std::vector<bool>& frozenBits, size_t dimension);
        virtual ~PolarDecoderASCL() = default;

        size_t maxNumPaths() const;

        void work() override;

    private:
        aff3ct::module::CRC<BitType> _crc;

        // Not accessible through AFF3CT
        size_t _L;
};

//
// SC
//

template <typename BitType, typename RealType>
class PolarDecoderSC: public PolarDecoder<BitType, RealType>
{
    using Class = PolarDecoderSC<BitType, RealType>;

    public:
        PolarDecoderSC(size_t K, size_t N, const std::vector<bool>& frozenBits, size_t dimension);
        virtual ~PolarDecoderSC() = default;

        size_t maxNumPaths() const;

        void work() override;
};

//
// SCAN
//

template <typename BitType, typename RealType>
class PolarDecoderSCAN: public PolarDecoder<BitType, RealType>
{
    using Class = PolarDecoderSCAN<BitType, RealType>;

    public:
        PolarDecoderSCAN(size_t K, size_t N, size_t maxIters, const std::vector<bool>& frozenBits, size_t dimension);
        virtual ~PolarDecoderSCAN() = default;

        size_t maxIterations() const;

        void work() override;

    private:
        size_t _maxIters;
};

/**************************************************************************
 * Implementations
 **************************************************************************/

//
// Base
//

template <typename BitType, typename RealType>
PolarDecoder<BitType, RealType>::PolarDecoder(const std::vector<bool>& frozenBits, size_t dimension):
    Pothos::Block(),
    _frozenBits(frozenBits)
{
    this->setupInput(0, Pothos::DType(typeid(RealType), dimension));
    this->setupOutput(0, Pothos::DType(typeid(BitType), dimension));

    this->registerCall(this, POTHOS_FCN_TUPLE(Class, K));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, N));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, frozenBits));

    this->registerProbe("K");
    this->registerProbe("N");
    this->registerProbe("frozenBits");
}

template <typename BitType, typename RealType>
size_t PolarDecoder<BitType, RealType>::K() const
{
    return static_cast<size_t>(_polarDecoderUPtr->get_K());
}

template <typename BitType, typename RealType>
size_t PolarDecoder<BitType, RealType>::N() const
{
    return static_cast<size_t>(_polarDecoderUPtr->get_N());
}

template <typename BitType, typename RealType>
std::vector<bool> PolarDecoder<BitType, RealType>::frozenBits() const
{
    return _frozenBits;
}

template <typename BitType, typename RealType>
void PolarDecoder<BitType, RealType>::workSIHO()
{
    using DecoderSIHO = aff3ct::module::Decoder_SIHO<BitType, RealType>;

    const auto elems = this->workInfo().minElements;
    if(0 == elems) return;

    auto input = this->input(0);
    auto output = this->output(0);

    const auto inputLen = this->K();
    const auto outputLen = this->N();

    const auto maxInputFrames = elems / inputLen;
    const auto maxOutputFrames = elems / outputLen;
    const auto numFrames = std::min(maxInputFrames, maxOutputFrames);

    const RealType* buffIn = input->buffer();
    BitType* buffOut = output->buffer();

    for(size_t frameIndex = 0; frameIndex < numFrames; ++frameIndex)
    {
        dynamic_cast<DecoderSIHO*>(_polarDecoderUPtr.get())->decode_siho(buffIn, buffOut);

        buffIn += inputLen;
        buffOut += outputLen;
    }

    input->consume(numFrames * inputLen);
    output->produce(numFrames * outputLen);
}

//
// ASCL
//

template <typename BitType, typename RealType>
PolarDecoderASCL<BitType, RealType>::PolarDecoderASCL(
    size_t K,
    size_t N,
    size_t L,
    const std::vector<bool>& frozenBits,
    size_t dimension
):
    PolarDecoder<BitType, RealType>(frozenBits, dimension),
    _crc(K, 0 /*TODO: size logic*/),
    _L(L)
{
    // TODO: input validation

    this->_polarDecoderUPtr.reset(new aff3ct::module::Decoder_polar_ASCL_fast_CA_sys<BitType, RealType>(
                                          static_cast<int>(K),
                                          static_cast<int>(N),
                                          static_cast<int>(L),
                                          this->_frozenBits,
                                          _crc));

    this->registerCall(this, POTHOS_FCN_TUPLE(Class, maxNumPaths));
    this->registerProbe("maxNumPaths");
}

template <typename BitType, typename RealType>
size_t PolarDecoderASCL<BitType, RealType>::maxNumPaths() const
{
    return _L;
}

template <typename BitType, typename RealType>
void PolarDecoderASCL<BitType, RealType>::work()
{
    this->workSIHO();
}

//
// SC
//

template <typename BitType, typename RealType>
PolarDecoderSC<BitType, RealType>::PolarDecoderSC(
    size_t K,
    size_t N,
    const std::vector<bool>& frozenBits,
    size_t dimension
):
    PolarDecoder<BitType, RealType>(frozenBits, dimension)
{
    // TODO: input validation

    this->_polarDecoderUPtr.reset(new aff3ct::module::Decoder_polar_SC_fast_sys<BitType, RealType>(
                                          static_cast<int>(K),
                                          static_cast<int>(N),
                                          this->_frozenBits));
}

template <typename BitType, typename RealType>
void PolarDecoderSC<BitType, RealType>::work()
{
    this->workSIHO();
}

//
// SCAN
//

template <typename BitType, typename RealType>
PolarDecoderSCAN<BitType, RealType>::PolarDecoderSCAN(
    size_t K,
    size_t N,
    size_t maxIters,
    const std::vector<bool>& frozenBits,
    size_t dimension
):
    PolarDecoder<BitType, RealType>(frozenBits, dimension),
    _maxIters(maxIters)
{
    // TODO: input validation

    this->_polarDecoderUPtr.reset(new aff3ct::module::Decoder_polar_SCAN_naive_sys<BitType, RealType>(
                                          static_cast<int>(K),
                                          static_cast<int>(N),
                                          static_cast<int>(maxIters),
                                          this->_frozenBits));

    this->registerCall(this, POTHOS_FCN_TUPLE(Class, maxIterations));
    this->registerProbe("maxIterations");
}

template <typename BitType, typename RealType>
size_t PolarDecoderSCAN<BitType, RealType>::maxIterations() const
{
    return _maxIters;
}

template <typename BitType, typename RealType>
void PolarDecoderSCAN<BitType, RealType>::work()
{
    this->workSIHO();
}

/**************************************************************************
 * Factories
 **************************************************************************/

static Pothos::Block* makePolarDecoderASCL(
    const Pothos::DType& bitDType,
    const Pothos::DType& realDType,
    size_t K,
    size_t N,
    size_t L,
    const std::vector<bool>& frozenBits)
{
    if(bitDType.dimension() != realDType.dimension())
    {
        throw Pothos::InvalidArgumentException("Bit and real DTypes must have same dimension");
    }

    #define IfTypesThenReturnASCL(BT,RT) \
        if((Pothos::DType::fromDType(bitDType, 1) == Pothos::DType(typeid(BT)))) \
            if((Pothos::DType::fromDType(realDType, 1) == Pothos::DType(typeid(RT)))) \
                return new PolarDecoderASCL<BT,RT>(K, N, L, frozenBits, bitDType.dimension());

#ifdef AFF3CT_MULTI_PREC
    IfTypesThenReturnASCL(B_32,R_32)
    IfTypesThenReturnASCL(B_64,R_64)
#else
    IfTypesThenReturnASCL(B,R)
#endif

    throw Pothos::InvalidArgumentException("Invalid types: bit="+bitDType.toString()+", real="+realDType.toString());
}

static Pothos::Block* makePolarDecoderSC(
    const Pothos::DType& bitDType,
    const Pothos::DType& realDType,
    size_t K,
    size_t N,
    const std::vector<bool>& frozenBits)
{
    if(bitDType.dimension() != realDType.dimension())
    {
        throw Pothos::InvalidArgumentException("Bit and real DTypes must have same dimension");
    }

    #define IfTypesThenReturnSC(BT,RT) \
        if((Pothos::DType::fromDType(bitDType, 1) == Pothos::DType(typeid(BT)))) \
            if((Pothos::DType::fromDType(realDType, 1) == Pothos::DType(typeid(RT)))) \
                return new PolarDecoderSC<BT,RT>(K, N, frozenBits, bitDType.dimension());

#ifdef AFF3CT_MULTI_PREC
    IfTypesThenReturnSC(B_32,R_32)
    IfTypesThenReturnSC(B_64,R_64)
#else
    IfTypesThenReturnSC(B,R)
#endif

    throw Pothos::InvalidArgumentException("Invalid types: bit="+bitDType.toString()+", real="+realDType.toString());
}

static Pothos::Block* makePolarDecoderSCAN(
    const Pothos::DType& bitDType,
    const Pothos::DType& realDType,
    size_t K,
    size_t N,
    size_t maxIterations,
    const std::vector<bool>& frozenBits)
{
    if(bitDType.dimension() != realDType.dimension())
    {
        throw Pothos::InvalidArgumentException("Bit and real DTypes must have same dimension");
    }

    #define IfTypesThenReturnSCAN(BT,RT) \
        if((Pothos::DType::fromDType(bitDType, 1) == Pothos::DType(typeid(BT)))) \
            if((Pothos::DType::fromDType(realDType, 1) == Pothos::DType(typeid(RT)))) \
                return new PolarDecoderSCAN<BT,RT>(K, N, maxIterations, frozenBits, bitDType.dimension());

#ifdef AFF3CT_MULTI_PREC
    IfTypesThenReturnSCAN(B_32,R_32)
    IfTypesThenReturnSCAN(B_64,R_64)
#else
    IfTypesThenReturnSCAN(B,R)
#endif

    throw Pothos::InvalidArgumentException("Invalid types: bit="+bitDType.toString()+", real="+realDType.toString());
}

/**************************************************************************
 * Registrations
 **************************************************************************/

static Pothos::BlockRegistry registerPolarDecoderASCL(
    "/fec/polar_decoder_ascl",
    Pothos::Callable(&makePolarDecoderASCL));

static Pothos::BlockRegistry registerPolarDecoderSC(
    "/fec/polar_decoder_sc",
    Pothos::Callable(&makePolarDecoderSC));

static Pothos::BlockRegistry registerPolarDecoderSCAN(
    "/fec/polar_decoder_scan",
    Pothos::Callable(&makePolarDecoderSCAN));
