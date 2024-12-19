#include "FileWriter.h"

bool FileWriter::isOpen() {
    return file.is_open();
}

void FileWriter::open(std::string output_filename) {
    if (isOpen()) {
        throw;
    }

    file.open(output_filename);

    if (!isOpen()) {
        throw;
    }
}

void FileWriter::close() {
    if (isOpen()) {
        file.close();
    }
}

void FileWriter::writeLine(std::string string) {
    if (isOpen()) {
        file << string << "\n";
    }
}

void FileWriter::write(std::vector<std::pair<int, int>> vector_of_pairs) {
    for (auto & coordinates : vector_of_pairs) {
        std::string x = std::to_string(coordinates.first);
        std::string y = std::to_string(coordinates.second);
        writeLine(x + " " + y);
    }
}