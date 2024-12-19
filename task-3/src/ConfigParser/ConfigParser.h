#include "../FileReaders/FileReader.h"
#include "StringParser.h"

class ConfigParser
{
    private:
        FileReader fileReader;
        StringParser stringParser;

    public:
        ConfigParser(std::string filename);
        std::vector<std::string> getCommand();
};