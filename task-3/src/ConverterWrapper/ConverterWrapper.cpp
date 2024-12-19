#include "ConverterWrapper.h"
#include <iostream>

void MuteWrapper::initialize(Converter *converter_arg,
                                 std::vector<int> arguments)
{
    if (arguments.size() != 2) {
        throw;
    }
    converter = converter_arg;
    beginningTime = arguments[0];
    endTime = arguments[1];
}

std::vector<int> MuteWrapper::requestWavFiles() { return {}; }

void MuteWrapper::convert(WavFile* wav_file,
                              std::vector<WavFile*> additional_wav_files)
{
    wav_file->open();
    if (additional_wav_files.size() != 0) {
        throw;
    }

    wav_file->seek(beginningTime * 44100);
    while (wav_file->tell() != endTime * 44100) {
        Sample sample = wav_file->get();
        if (sample.isEmpty()) {
            break;
        }

        Sample converted_sample = (*converter).convert({sample});

        wav_file->set(converted_sample);
        wav_file->next();
    }
    wav_file->close();
}

void MixWrapper::initialize(Converter *converter_arg,
                              std::vector<int> arguments)
{
    if (arguments.size() != 2) {
        throw;
    }

    indexWavFile = arguments[0];
    beginningTime = arguments[1];
    converter = converter_arg;
}

std::vector<int> MixWrapper::requestWavFiles() { return {indexWavFile}; }

void MixWrapper::convert(WavFile* wav_file,
                           std::vector<WavFile*> additional_wav_files)
{
    if (additional_wav_files.size() != 1) {
        throw;
    }

    wav_file->seek(beginningTime);
    WavFile* mix_wav_file = additional_wav_files[0];
    mix_wav_file->seek(0);

    while (true) {
        Sample sample = wav_file->get();
        Sample mix_sample = mix_wav_file->get();

        if (sample.isEmpty() || mix_sample.isEmpty()) {
            break;
        }

        Sample converted_sample = (*converter).convert({sample, mix_sample});
        wav_file->set(converted_sample);
    }
}

void FadeWrapper::initialize(Converter *converter_arg,
                              std::vector<int> arguments)
{
    if (arguments.size() != 2) {
        throw;
    }
    converter = converter_arg;
    beginningTime = arguments[0];
    endTime = arguments[1];
}

std::vector<int> FadeWrapper::requestWavFiles() { return {}; }

void FadeWrapper::convert(WavFile* wav_file,
                           std::vector<WavFile*> additional_wav_files)
{
    if (additional_wav_files.size() != 0) {
        throw;
    }

    wav_file->seek(beginningTime);
    while (wav_file->tell() != endTime) {
        Sample sample = wav_file->get();
        if (sample.isEmpty()) {
            break;
        }

        Sample converted_sample = (*converter).convert({sample});
        wav_file->set(converted_sample);
        wav_file->next();
    }
}

ConverterWrapper *
MuteWrapperFactory::create(std::vector<std::string> config)
{
    if (config.size() != 3) {
        throw;
    }

    if (config[0] != "mute") {
        throw;
    }

    int beginning_seconds = std::stoi(config[1]);
    int end_seconds = std::stoi(config[2]);

    ConverterWrapper *converter_wrapper = new MuteWrapper;

    SilencerFactory factory;
    Converter *converter = factory.create();

    converter_wrapper->initialize(converter, {beginning_seconds, end_seconds});
    return converter_wrapper;
}

ConverterWrapper *MixWrapperFactory::create(std::vector<std::string> config)
{
    if (config.size() < 2 || config.size() > 3) {
        throw;
    }

    if (config[0] != "mix") {
        throw;
    }

    int index = config[1][1] - '1';

    int beginning_seconds = 0;
    if (config.size() == 3) {
        beginning_seconds = std::stoi(config[2]);
    }

    ConverterWrapper *converter_wrapper = new MixWrapper;

    MixerFactory factory;
    Converter *converter = factory.create();

    converter_wrapper->initialize(converter, {index, beginning_seconds});
    return converter_wrapper;
}

ConverterWrapper *FadeWrapperFactory::create(std::vector<std::string> config)
{
    if (config.size() != 3) {
        throw;
    }

    if (config[0] != "fade") {
        throw;
    }

    int beginning_seconds = std::stoi(config[1]);
    int end_seconds = std::stoi(config[2]);

    ConverterWrapper *converter_wrapper = new FadeWrapper;

    FaderFactory factory;
    Converter *converter = factory.create({(end_seconds - beginning_seconds)});

    converter_wrapper->initialize(converter, {beginning_seconds, end_seconds});
    return converter_wrapper;
}