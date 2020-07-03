// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "libpopcnt.h"

#include <Pothos/Framework.hpp>

#include <cstdint>

class Puncture: public Pothos::Block
{
    public:
        Puncture(std::uint32_t punctureSize, std::uint32_t puncturePattern, size_t delay);
        virtual ~Puncture();

        void work() override;

    private:
        std::uint32_t _punctureSize;
        std::uint32_t _puncturePattern;
        size_t _delay;
        std::uint32_t _numPunctureHoles;
};

Puncture::Puncture(std::uint32_t punctureSize, std::uint32_t puncturePattern, size_t delay):
    Pothos::Block(),
    _punctureSize(punctureSize),
    _puncturePattern(puncturePattern),
    _delay(delay)
{

}

Puncture::~Puncture(){}

void Puncture::work()
{
}
