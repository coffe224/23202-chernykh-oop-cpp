#pragma once

#include "Sample.h"
#include <string>
#include <vector>


class Converter
{
    public:
        virtual Sample convert(std::vector<Sample> samples) = 0;
        // virtual ~Converter(); // надо вообще?
};

class Silencer : public Converter
{
    public:
        Sample convert(std::vector<Sample> samples);
};

class Mixer : public Converter
{
    public:
        Sample convert(std::vector<Sample> samples);
};

class Fader : public Converter
{
    public:
        Fader(int fade_length);
        Sample convert(std::vector<Sample> samples);

    private:
        int fadeCounter;
        int fadeLength;
};


class ConverterFactory
{
        public:
            virtual Converter* create(std::vector<int> params = {}) = 0;
};

class SilencerFactory : public ConverterFactory
{
        public:
            Converter* create(std::vector<int> params = {});
};

class MixerFactory : public ConverterFactory
{
        public:
            Converter* create(std::vector<int> params = {});
};

class FaderFactory : public ConverterFactory
{
        public:
            Converter* create(std::vector<int> params = {});
};

// напиши деструкторы