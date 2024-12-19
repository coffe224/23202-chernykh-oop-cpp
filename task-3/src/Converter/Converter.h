#pragma once

#include "../Sample/Sample.h"
#include <string>
#include <vector>


class Converter
{
    public:
        virtual Sample convert(std::vector<Sample> samples) = 0;
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