#include "BasicFileReader.h"
#include <iostream>

void BasicFileReader::open(const std::string& input_filename)
{
    if (!isOpen()) {
        try {
            file.open(input_filename);
        } catch (...) {
            std::cerr << "Unable to open file '" << input_filename << "'.\n";
        }
        filename = input_filename;
    }
}

void BasicFileReader::close()
{
    if (isOpen()) {
        file.close();
    }
}

bool BasicFileReader::isOpen() const { return file.is_open(); }

bool BasicFileReader::isEOF()
{
    if (file.is_open()) {
        return file.peek() == EOF;
    } else {
        return true;
    }
}