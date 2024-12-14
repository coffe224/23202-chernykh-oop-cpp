#pragma once

#include "BasicFileReader.h"

class FileReader : public BasicFileReader
{
    public:
        std::string getLine();
};