#include "FileReader.h"

void FileReader::openFile(const std::string& input_filename)
{
    if (!isOpen()) {
        file.open(input_filename);
    }
}

void FileReader::closeFile()
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

void FileReader::getLine(std::string& line)
{
    if (!isEOF()) {
        std::getline(file, line);
    }
}
