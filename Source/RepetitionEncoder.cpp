// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericEncoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/repetition_encoder.h>

#include <cstdint>
#include <vector>

class RepetitionEncoder: public GRGenericEncoder
{
    public:
        static Pothos::Block* make(size_t frameSize, size_t numRepetitions);

        RepetitionEncoder(size_t frameSize, size_t numRepetitions);
        virtual ~RepetitionEncoder();

        // TODO: move to base class?
        void setFrameSize(size_t frameSize);
};

Pothos::Block* RepetitionEncoder::make(size_t frameSize, size_t numRepetitions)
{
    return new RepetitionEncoder(frameSize, numRepetitions);
}

RepetitionEncoder::RepetitionEncoder(size_t frameSize, size_t numRepetitions):
    GRGenericEncoder(gr::fec::code::repetition_encoder::make(
                         static_cast<int>(frameSize),
                         static_cast<int>(numRepetitions)))
{
    this->setupInput(0, Pothos::DType("uint8"));
    this->setupOutput(0, Pothos::DType("uint8"));

    this->registerCall(this, POTHOS_FCN_TUPLE(RepetitionEncoder, setFrameSize));
}

RepetitionEncoder::~RepetitionEncoder(){}

void RepetitionEncoder::setFrameSize(size_t frameSize)
{
    (void)_genericEncoderSPtr->set_frame_size(frameSize);
}

//
// Registration
//

/*
 * |PothosDoc Repetition Encoder
 *
 * |category /FEC/Repetition
 * |keywords coder
 * |factory /fec/repetition_encoder(frameSize,numRepetitions)
 * |setter setFrameSize(frameSize)
 *
 * |param frameSize[Frame Size]
 * |widget SpinBox(minimum=0)
 * |default 1
 * |preview enable
 *
 * |param numRepetitions[Num Repetitions]
 * |widget SpinBox(minimum=1)
 * |default 1
 * |preview enable
 */
static Pothos::BlockRegistry registerRepetitionEncoder(
    "/fec/repetition_encoder",
    Pothos::Callable(&RepetitionEncoder::make));
