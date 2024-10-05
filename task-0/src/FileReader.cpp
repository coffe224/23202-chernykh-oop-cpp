#include "../include/FileReader.h"

void FileReader::openFile(std::string& input_filename) {
    if (!isOpen()) {
        file.open(input_filename);
    }
}

void FileReader::closeFile() {
    if (isOpen()) {
        file.close();
    }
}

bool FileReader::isOpen() const {
    return file.is_open();
}

bool FileReader::isEOF() {
    return file.peek() == EOF;
}

void FileReader::getLine(std::string& line) {
    if (!isEOF()) {
        std::getline(file, line);
    }
}
