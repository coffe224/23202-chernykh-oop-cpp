#include <iostream>

#include "ByteReader.h"

ByteReader::ByteReader() { fileSize = 0; }

void ByteReader::open(const std::string& input_filename)
{
    this->BasicFileReader::open(input_filename);

    file.seekg(0, file.end);
    fileSize = file.tellg();
    file.seekg(0, file.beg);
}

std::size_t ByteReader::getFileSize() { return fileSize; }

std::uint8_t ByteReader::getByte()
{
    if (isEOF()) {
        throw;
    }
    return file.get();
}

std::uint16_t ByteReader::getU16LE()
{
    std::uint16_t result = 0;
    std::uint8_t *temp_p = reinterpret_cast<std::uint8_t *>(&result);

    int size = sizeof(std::uint16_t);
    for (int i = 0; i < size; i++) {
        std::uint8_t raw_byte = getByte();
        temp_p[i] = raw_byte;
    }
    return result;
}

std::uint32_t ByteReader::getU32LE()
{
    std::uint32_t result = 0;
    std::uint8_t *temp_p = reinterpret_cast<std::uint8_t *>(&result);

    int size = sizeof(std::uint32_t);
    for (int i = 0; i < size; i++) {
        std::uint8_t raw_byte = getByte();
        temp_p[i] = raw_byte;
    }
    return result;
}

std::string ByteReader::getRawString(int length_of_string)
{
    std::string raw_string(length_of_string, ' ');
    for (int i = 0; i < length_of_string; i++) {
        raw_string[i] = getByte();
    }
    return raw_string;
}