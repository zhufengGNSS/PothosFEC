// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <Poco/RandomStream.h>

#include <string>

namespace FECTests
{

static constexpr float defaultSNR = 8.0f;
static constexpr float defaultAmp = 32.0f;

template <typename T = std::uint8_t>
Pothos::BufferChunk getRandomInput(size_t numElems)
{
    Pothos::BufferChunk bufferChunk(typeid(T), numElems);

    Poco::RandomBuf randomBuf;
    randomBuf.readFromDevice(
        bufferChunk,
        bufferChunk.length);
    for(size_t elem = 0; elem < numElems; ++elem)
    {
        bufferChunk.as<T*>()[elem] %= 2;
    }

    return bufferChunk;
}

// Note: Pothos::Object::operator== checks that the objects' data is the same,
// not just the value.
void testLabelsEqual(const Pothos::Label& label0, const Pothos::Label& label1);

/*
 * Generate and add noise using Box-Muller method to transform two uniformly
 * distributed random values into normal distributed random values.
 */
Pothos::BufferChunk addNoiseAndGetError(
    const Pothos::BufferChunk& bufferChunk,
    float snr,
    float amp,
    int* errorOut);

template <typename ReturnType, typename... ArgsType>
ReturnType getAndCallPlugin(
    const std::string& proxyPath,
    ArgsType&&... args)
{
    auto plugin = Pothos::PluginRegistry::get(proxyPath);
    auto getter = plugin.getObject().extract<Pothos::Callable>();

    return getter.call<ReturnType>(args...);
}

}
