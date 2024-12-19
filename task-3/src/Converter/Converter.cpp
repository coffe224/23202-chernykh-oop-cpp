#include "Converter.h"
#include <iostream>

Sample Silencer::convert(std::vector<Sample> samples) {
    if (samples.size() != 1) {
        throw;
    }
    Sample sample = samples[0];
    if (!sample.isEmpty()) {
        sample.setValue(0);
    }
    return sample;
}

Sample Mixer::convert(std::vector<Sample> samples) {
    if (samples.size() != 2) {
        throw;
    }
    Sample first_sample = samples[0];
    Sample second_sample = samples[1];

    if (!first_sample.isEmpty() && !second_sample.isEmpty()) {
        std::int16_t first_value = first_sample.getValue();
        std::int16_t second_value = second_sample.getValue();
        first_sample.setValue(first_value + second_value);
    }
    return first_sample;
}

Fader::Fader(int fade_length) {
    fadeLength = fade_length;
    fadeCounter = 0;
}

Sample Fader::convert(std::vector<Sample> samples) {
    if (samples.size() != 2) {
        throw;
    }
    Sample sample = samples[0];

    if (!sample.isEmpty() && fadeLength > fadeCounter) {
        float fade_coef = fadeCounter / fadeLength;
        std::int16_t new_value = sample.getValue() * fade_coef;

        sample.setValue(new_value);
        fadeCounter++;
    }
    return sample;
}

