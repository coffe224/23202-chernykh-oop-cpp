#include "FileWriter.h"

void FileWriter::openFile(std::string filename) {
    if (!isOpen()) {
        file.open(filename);
    }
}

bool FileWriter::isOpen() {
    return file.is_open();
}

void FileWriter::closeFile() {
    if (isOpen()) {
        file.close();
    }
}

void FileWriter::writeLine(std::string line) {
    file << line << '\n';
}