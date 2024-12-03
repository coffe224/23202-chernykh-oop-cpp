#include "FileReader.h"

void FileReader::open(const std::string& input_filename)
{
    if (!isOpen()) {
        file.open(input_filename);
    }
}

void FileReader::close()
{
    if (isOpen()) {
        file.close();
    }
}

bool FileReader::isOpen() const { return file.is_open(); }

bool FileReader::isEOF()
{
    if (file.is_open()) {
        return file.peek() == EOF;
    } else {
        return true;
    }
}

std::string FileReader::getLine()
{
    std::string line;
    if (!isEOF()) {
        std::getline(file, line);
    }
    return line;
}