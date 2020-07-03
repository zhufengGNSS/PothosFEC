// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "libpopcnt.h"

#include <Pothos/Exception.hpp>
#include <Pothos/Framework.hpp>
#include <Pothos/Object.hpp>
#include <Pothos/Plugin.hpp>

#include <cstdint>
#include <limits>
#include <type_traits>

//
// Utility
//

template <typename T>
struct PunctureTraits
{
    using UIntType = T;
};

template <>
struct PunctureTraits<float>
{
    using UIntType = std::uint32_t;
};

template <>
struct PunctureTraits<double>
{
    using UIntType = std::uint64_t;
};

template <typename T>
static typename PunctureTraits<T>::UIntType generateMask(size_t punctureSize)
{
    typename PunctureTraits<T>::UIntType mask = 0;
    for(size_t i = 0; i < punctureSize; ++i) mask |= (1 << i);

    return mask;
}

//
// Block implementation
//

template <typename T>
class Puncture: public Pothos::Block
{
    public:
        using Class = Puncture<T>;
        using UIntType = typename PunctureTraits<T>::UIntType;
        static constexpr size_t TSizeBytes = sizeof(T);
        static constexpr size_t TSizeBits = TSizeBytes*8;

        Puncture(size_t dtypeDimension, size_t punctureSize, UIntType puncturePattern, size_t delay);
        virtual ~Puncture();

        size_t punctureSize() const {return _punctureSize;};
        Puncture<T>::UIntType puncturePattern() const {return _puncturePattern;};
        size_t delay() const {return _delay;};
        size_t numPunctureHoles() const {return _numPunctureHoles;};

        void setPunctureSize(size_t punctureSize);
        void setPuncturePattern(UIntType puncturePattern);
        void setDelay(size_t delay);

        void work() override;

    private:
        size_t _punctureSize;
        UIntType _puncturePattern;
        size_t _delay;
        size_t _numPunctureHoles;

        void _work(const Pothos::BufferChunk& bufferChunkIn, const Pothos::BufferChunk& bufferChunkOut);
        void _msgWork();
        void _recalculatePunctureVars();

        inline double outputMultiplier() const {return static_cast<double>(_punctureSize - _numPunctureHoles);}
};

template <typename T>
Puncture<T>::Puncture(size_t dtypeDimension, size_t punctureSize, Puncture<T>::UIntType puncturePattern, size_t delay):
    Pothos::Block(),
    _punctureSize(0),
    _puncturePattern(0),
    _delay(0),
    _numPunctureHoles(0)
{
    this->setPunctureSize(punctureSize);
    this->setPuncturePattern(puncturePattern);
    this->setDelay(delay);

    this->setupInput(0, Pothos::DType(typeid(T), dtypeDimension));
    this->setupOutput(0, Pothos::DType(typeid(T), dtypeDimension));

    this->registerCall(this, POTHOS_FCN_TUPLE(Class, punctureSize));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, puncturePattern));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, delay));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, numPunctureHoles));

    this->registerCall(this, POTHOS_FCN_TUPLE(Class, setPunctureSize));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, setPuncturePattern));
    this->registerCall(this, POTHOS_FCN_TUPLE(Class, setDelay));

    this->registerSignal("punctureSizeChanged");
    this->registerSignal("puncturePatternChanged");
    this->registerSignal("delayChanged");
    this->registerSignal("numPunctureHolesChanged");

    this->registerProbe("punctureSize");
    this->registerProbe("puncturePattern");
    this->registerProbe("delay");
    this->registerProbe("numPunctureHoles");
}

template <typename T>
Puncture<T>::~Puncture(){}

template <typename T>
void Puncture<T>::setPunctureSize(size_t punctureSize)
{
    if(punctureSize > Puncture<T>::TSizeBits)
    {
        throw Pothos::InvalidArgumentException("Puncture size cannot be larger than block type size");
    }

    _punctureSize = punctureSize;
    this->_recalculatePunctureVars();
    this->emitSignal("punctureSizeChanged", _punctureSize);
}

template <typename T>
void Puncture<T>::setPuncturePattern(Puncture<T>::UIntType puncturePattern)
{
    _puncturePattern = puncturePattern;
    this->_recalculatePunctureVars();
    this->emitSignal("puncturePatternChanged", _puncturePattern);
}

template <typename T>
void Puncture<T>::setDelay(size_t delay)
{
    if(delay > Puncture<T>::TSizeBits)
    {
        throw Pothos::InvalidArgumentException("Delay cannot be larger than block type size");
    }

    _delay = delay;
    this->_recalculatePunctureVars();
    this->emitSignal("delayChanged", _delay);
}

template <typename T>
void Puncture<T>::work()
{
    auto input = this->input(0);
    auto output = this->output(0);

    while(input->hasMessage()) this->_msgWork();

    const auto outputElems = this->workInfo().minElements;
    if(outputElems < this->outputMultiplier()) return;

    this->_work(input->buffer(), output->buffer());
    input->consume(outputElems / this->outputMultiplier());
    output->produce(outputElems);
}

template <typename T>
void Puncture<T>::_work(
    const Pothos::BufferChunk& bufferChunkIn,
    const Pothos::BufferChunk& bufferChunkOut)
{
    const auto outputElems = std::min(bufferChunkIn.elements(), bufferChunkOut.elements());

    const Puncture<T>::UIntType* buffIn = bufferChunkIn;
    Puncture<T>::UIntType* buffOut = bufferChunkOut;

    for(size_t i = 0, k = 0; i < outputElems; ++i)
    {
        for(size_t j = 0; j < _punctureSize; ++j)
        {
            if((_puncturePattern >> (_punctureSize - 1 - j)) & 1)
            {
                buffOut[k++] = buffIn[i * _punctureSize + j];
            }
        }
    }
}

template <typename T>
void Puncture<T>::_msgWork()
{
    auto input = this->input(0);
    auto output = this->output(0);

    for(size_t msgIndex = 0; msgIndex < input->totalMessages(); ++msgIndex)
    {
        auto msg = input->popMessage();
        if(msg.type() == typeid(Pothos::Packet))
        {
            const auto payload = msg.convert<Pothos::Packet>().payload;
            Pothos::BufferChunk outputPayload(payload.dtype, payload.elements() * this->outputMultiplier());

            this->_work(payload, outputPayload);

            Pothos::Packet outputPkt;
            outputPkt.payload = outputPayload;
            output->postMessage(std::move(outputPkt));
        }
    }
}

template <typename T>
void Puncture<T>::_recalculatePunctureVars()
{
    auto mask = generateMask<T>(_punctureSize);

    for(size_t i = 0; i < _delay; ++i)
    {
        _puncturePattern = ((_puncturePattern & 1) << (_punctureSize - 1)) + (_puncturePattern + 1);
    }
    _puncturePattern &= mask;

    const auto maskPopCnt = popcnt(&mask, Puncture<T>::TSizeBytes);
    const auto puncPatPopCnt = popcnt(&_puncturePattern, Puncture<T>::TSizeBytes);
    _numPunctureHoles = maskPopCnt - puncPatPopCnt;

    this->emitSignal("numPunctureHolesChanged", _numPunctureHoles);
}

//
// Factory+registration
//

static Pothos::Block* makePuncture(
    const Pothos::DType& dtype,
    size_t punctureSize,
    const Pothos::Object& puncturePattern,
    size_t delay)
{
    #define ifTypeThenPuncture(T) \
        if(Pothos::DType::fromDType(dtype, 1) == Pothos::DType(typeid(T))) \
            return new Puncture<T>(dtype.dimension(), punctureSize, puncturePattern.convert<Puncture<T>::UIntType>(), delay);

    ifTypeThenPuncture(std::int8_t)
    else ifTypeThenPuncture(std::int16_t)
    else ifTypeThenPuncture(std::int32_t)
    else ifTypeThenPuncture(std::int64_t)
    else ifTypeThenPuncture(std::uint8_t)
    else ifTypeThenPuncture(std::uint16_t)
    else ifTypeThenPuncture(std::uint32_t)
    else ifTypeThenPuncture(std::uint64_t)
    else ifTypeThenPuncture(float)
    else ifTypeThenPuncture(double)

    throw Pothos::InvalidArgumentException("Invalid dtype: "+dtype.toString());
}

static Pothos::BlockRegistry registerPuncture(
    "/fec/puncture",
    Pothos::Callable(&makePuncture));
