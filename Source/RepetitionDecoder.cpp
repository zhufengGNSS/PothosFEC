// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "GRGenericDecoder.hpp"

#include <Pothos/Framework.hpp>
#include <Pothos/Plugin.hpp>

#include <gnuradio/fec/repetition_decoder.h>

#include <cstdint>
#include <vector>

class RepetitionDecoder: public GRGenericDecoder
{
    public:
        static Pothos::Block* make(size_t frameSize, size_t numRepetitions, float apProb);

        RepetitionDecoder(size_t frameSize, size_t numRepetitions, float apProb);
        virtual ~RepetitionDecoder();

        float apProbability() const;

        void setFrameSize(size_t frameSize);

    private:
        float _apProb;
};

Pothos::Block* RepetitionDecoder::make(size_t frameSize, size_t numRepetitions, float apProb)
{
    return new RepetitionDecoder(frameSize, numRepetitions, apProb);
}

RepetitionDecoder::RepetitionDecoder(size_t frameSize, size_t numRepetitions, float apProb):
    GRGenericDecoder(gr::fec::code::repetition_decoder::make(
                         static_cast<int>(frameSize),
                         static_cast<int>(numRepetitions),
                         apProb)),
    _apProb(apProb)
{
    this->setupInput(0, Pothos::DType("float32"));
    this->setupOutput(0, Pothos::DType("uint8"));

    this->registerCall(this, POTHOS_FCN_TUPLE(RepetitionDecoder, setFrameSize));
    this->registerCall(this, POTHOS_FCN_TUPLE(RepetitionDecoder, apProbability));

    this->registerProbe("apProbability");
}

RepetitionDecoder::~RepetitionDecoder(){}

float RepetitionDecoder::apProbability() const
{
    return _apProb;
}

void RepetitionDecoder::setFrameSize(size_t frameSize)
{
    (void)_genericDecoderSPtr->set_frame_size(frameSize);
}

//
// Registration
//

/*
 * |PothosDoc Repetition Decoder
 *
 * |category /FEC/Repetition
 * |keywords coder
 * |factory /fec/repetition_decoder(frameSize,numRepetitions,apProb)
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
 *
 * |param apProb[A Priori Probability]
 * |widget DoubleSpinBox(minimum=0.1,maximum=1.0,step=0.01)
 * |default 0.5
 * |preview enable
 */
static Pothos::BlockRegistry registerRepetitionDecoder(
    "/fec/repetition_decoder",
    Pothos::Callable(&RepetitionDecoder::make));
