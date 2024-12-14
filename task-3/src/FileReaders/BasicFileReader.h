#pragma once

#include <string>
#include <fstream>

class BasicFileReader
{
    protected:
        std::ifstream file;
        std::string filename;

    public:
        void open(const std::string& input_filename);
        void close();

        bool isOpen() const;
        bool isEOF();
};