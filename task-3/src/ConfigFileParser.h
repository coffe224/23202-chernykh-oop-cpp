#include "StringParser.h"
#include "FileReaders/FileReader.h"
#include "ConverterWrapper.h"

class ConfigFileParser {
    private:
        FileReader fileReader;
        StringParser stringParser;
        ConverterManager converterManager;
    public:
        std::vector<ConverterWrapper*> parse(std::string config_filename);
};