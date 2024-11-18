#include "FileWriter.h"

void FileWriter::openFile(const std::string& filename)
{
    if (!isOpen() && filename != "") {
        file.open(filename);
    }
}

bool FileWriter::isOpen() { return file.is_open(); }

void FileWriter::closeFile()
{
    if (isOpen()) {
        file.close();
    }
}

void FileWriter::writeLine(const std::string& line)
{
    if (isOpen()) {
        file << line << '\n';
    }
}