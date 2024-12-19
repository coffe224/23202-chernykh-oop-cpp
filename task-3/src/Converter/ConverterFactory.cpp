#include "ConverterFactory.h"

Converter* SilencerFactory::create(std::vector<int> params) {
    return new Silencer;
}

Converter* MixerFactory::create(std::vector<int> params) {
    return new Mixer;
}

Converter* FaderFactory::create(std::vector<int> params) {
    return new Fader(params[0]);
}