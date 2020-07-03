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

    static constexpr UIntType Mask = std::numeric_limits<UIntType>::max();
};

template <>
struct PunctureTraits<float>
{
    using UIntType = std::uint32_t;

    static constexpr UIntType Mask = std::numeric_limits<UIntType>::max();
};

template <>
struct PunctureTraits<double>
{
    using UIntType = std::uint64_t;

    static constexpr UIntType Mask = std::numeric_limits<UIntType>::max();
};

//
// Block implementation
//

template <typename T>
class Puncture: public Pothos::Block
{
    public:
        using Class = Puncture<T>;
        using UIntType = typename PunctureTraits<T>::UIntType;
        static constexpr UIntType Mask = PunctureTraits<T>::Mask;
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

        void _msgWork();
        void _updateNumPunctureHoles();
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
    this->emitSignal("punctureSizeChanged", _punctureSize);

    this->_updateNumPunctureHoles();
}

template <typename T>
void Puncture<T>::setPuncturePattern(Puncture<T>::UIntType puncturePattern)
{
    _puncturePattern = puncturePattern;
    this->emitSignal("puncturePatternChanged", _puncturePattern);

    this->_updateNumPunctureHoles();
}

template <typename T>
void Puncture<T>::setDelay(size_t delay)
{
    if(delay > Puncture<T>::TSizeBits)
    {
        throw Pothos::InvalidArgumentException("Delay cannot be larger than block type size");
    }

    _delay = delay;
    this->emitSignal("delayChanged", _delay);

    this->_updateNumPunctureHoles();
}

template <typename T>
void Puncture<T>::work()
{
}

template <typename T>
void Puncture<T>::_msgWork()
{

}

template <typename T>
void Puncture<T>::_updateNumPunctureHoles()
{
    UIntType mask = Puncture<T>::Mask;

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
