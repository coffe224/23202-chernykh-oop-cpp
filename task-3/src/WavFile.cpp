#include "WavFile.h"
#include <iostream>

WavFile::WavFile(std::string file_name) { fileName = file_name; }

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
    file.seekg(start_position + 2 * sample_index);
}

int WavFile::tell() { return 0; }

void WavFile::next()
{
    file.seekg(2, file.cur);
    file.seekp(2, file.cur);
}

Sample WavFile::get()
{
    Sample sample;
    if (isEOF()) {
        sample.setEmpty();
    } else {
        std::uint16_t value = getSampleValue();
        sample.setValue(value);
    }
    return sample;
}

void WavFile::set(Sample sample)
{
    if (sample.isEmpty()) {
        std::cerr << "Can't write empty sample to file.\n";
        throw;
    }
    setSampleValue(sample.getValue());
}

std::uint16_t WavFile::getSampleValue() {
    std::uint16_t result = 0;
    std::uint8_t *temp_p = reinterpret_cast<std::uint8_t *>(&result);

    int size = sizeof(std::uint16_t);
    for (int i = 0; i < size; i++) {
        std::uint8_t raw_byte = file.get();
        temp_p[i] = raw_byte;
    }
    file.seekg(-2, file.cur);
    return result;
}

void WavFile::setSampleValue(std::uint16_t value) {
    std::uint8_t *temp_p = reinterpret_cast<std::uint8_t *>(&value);
    int size = sizeof(std::uint16_t);
    for (int i = size - 1; i >= 0; i--) {
        std::uint8_t raw_byte = temp_p[i];
        file.put(raw_byte);
    }
    file.seekp(-2, file.cur);
}