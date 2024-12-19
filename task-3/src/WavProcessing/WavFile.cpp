#include "WavFile.h"
#include <iostream>

WavFile::WavFile(std::string filename) { fileName = filename; }

WavFile::WavFile(WavFile *wav_file, std::string filename) {
    std::ifstream src(wav_file->fileName, std::ios::binary);
    std::ofstream dst(filename, std::ios::binary);
    dst << src.rdbuf();

    fileName = filename;
    start_position = wav_file->start_position;
    sample_rate = wav_file->sample_rate;
    samples = wav_file->samples;
}

void WavFile::open()
{
    file.open(fileName);
    file.seekg(start_position);
}

bool WavFile::isOpen() { return file.is_open(); }

bool WavFile::isEOF()
{
    if (file.is_open()) {
        return file.peek() == EOF;
    } else {
        return true;
    }
}

void WavFile::close() { file.close(); }

void WavFile::seek(int sample_index)
{
    index = sample_index;
    file.seekp(start_position + 2 * sample_index);
}

int WavFile::tell() { return index; }

void WavFile::next()
{
    index++;
    file.seekp(2, file.cur);
}

Sample WavFile::get()
{
    Sample sample;
    if (isEOF()) {
        sample.setEmpty();
    } else {
        std::int16_t value = getSampleValue();
        sample.setValue(value);
    }
    return sample;
}

void WavFile::set(Sample sample)
{
    if (sample.isEmpty()) {
        throw;
    }
    setSampleValue(sample.getValue());
}

std::int16_t WavFile::getSampleValue() {
    std::int16_t result = 0;
    std::uint8_t *temp_p = reinterpret_cast<std::uint8_t *>(&result);

    int size = sizeof(std::int16_t);
    for (int i = 0; i < size; i++) {
        std::uint8_t raw_byte = file.get();
        temp_p[i] = raw_byte;
    }
    file.seekg(-2, file.cur);

    return result;
}

void WavFile::setSampleValue(std::int16_t value) {
    std::uint8_t *temp_p = reinterpret_cast<std::uint8_t *>(&value);
    int size = sizeof(std::int16_t);
    for (int i = 0; i < size; i++) {
        std::uint8_t raw_byte = temp_p[size - 1 - i];
        file.put(raw_byte);
    }
    file.seekp(-2, file.cur);
}