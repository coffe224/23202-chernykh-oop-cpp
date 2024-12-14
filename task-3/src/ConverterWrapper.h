#pragma once

#include "Converter.h"
#include "WavReader.h"
#include <vector>
#include <map>

class ConverterWrapper
{
    private:
        Converter *converter;

    public:
        virtual void initialize(Converter *converter_arg,
                                std::vector<int> arguments = {}) = 0;
        virtual std::vector<int> requestWavFiles() = 0;
        virtual void convert(WavFile wav_file,
                             std::vector<WavFile> additional_wav_files) = 0;
};

class SilencerWrapper : public ConverterWrapper
{
    private:
        Converter *converter;
        int beginningTime;
        int endTime;

    public:
        void initialize(Converter *converter_arg,
                        std::vector<int> arguments = {});
        std::vector<int> requestWavFiles();
        void convert(WavFile wav_file,
                     std::vector<WavFile> additional_wav_files);
};

class MixerWrapper : public ConverterWrapper
{
    private:
        Converter *converter;
        int beginningTime;
        int indexWavFile;

    public:
        void initialize(Converter *converter_arg,
                        std::vector<int> arguments = {});
        std::vector<int> requestWavFiles();
        void convert(WavFile wav_file,
                     std::vector<WavFile> additional_wav_files);
};

class FaderWrapper : public ConverterWrapper
{
    private:
        Converter *converter;
        int beginningTime;
        int endTime;

    public:
        void initialize(Converter *converter_arg,
                        std::vector<int> arguments = {});
        std::vector<int> requestWavFiles();
        void convert(WavFile wav_file,
                     std::vector<WavFile> additional_wav_files);
};

class ConverterWrapperFactory
{
    public:
        virtual ConverterWrapper* create(std::vector<std::string> config) = 0;
};

class SilencerWrapperFactory : public ConverterWrapperFactory
{
    public:
        ConverterWrapper* create(std::vector<std::string> config);
};

class MixerWrapperFactory : public ConverterWrapperFactory
{
    public:
        ConverterWrapper* create(std::vector<std::string> config);
};

class FaderWrapperFactory : public ConverterWrapperFactory
{
    public:
        ConverterWrapper* create(std::vector<std::string> config);
};

class ConverterManager
{
    public:
        ConverterManager();
        ConverterWrapperFactory *getConverter(std::string config_command);

    private:
        std::map<std::string, ConverterWrapperFactory *> factory_map;
};