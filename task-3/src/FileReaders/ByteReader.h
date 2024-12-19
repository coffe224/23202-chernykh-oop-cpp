#include <cstdint>
#include <fstream>
#include <string>

#include "BasicFileReader.h"

class ByteReader : public BasicFileReader
{
    private:
        int fileSize;
    public:
        ByteReader();
        void open(const std::string& input_filename);

        std::size_t getFileSize();
        unsigned char getByte();

        std::uint16_t getU16LE();
        std::uint32_t getU32LE();
        std::string getRawString(int length_of_string);
};