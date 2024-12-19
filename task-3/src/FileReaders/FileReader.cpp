#include "FileReader.h"
#include <iostream>

std::string FileReader::getLine()
{
    if (!isOpen() || isEOF()) {
        return "";
    }
    std::string line;
    try {
        std::getline(file, line);
    } catch (...) {
        std::cerr << "ERROR: Can't get line from file '" << filename << "'.\n";
        throw;
    }
    return line;
}