#include <string>

#include "FileReaders/ByteReader.h"
#include "WavFile.h"

class WavReader
{
    private:
        ByteReader byteReader;

    public:
        WavFile read(std::string filename);
};