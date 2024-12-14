#include "ConfigFileParser.h"
#include <iostream>

std::vector<ConverterWrapper*> ConfigFileParser::parse(std::string config_filename)
{
    std::vector<ConverterWrapper*> converters;
    fileReader.open(config_filename);
    while (!fileReader.isEOF())
    {
        std::string str = fileReader.getLine();
        std::vector<std::string> words = stringParser.getWords(str);

        if (words.size() == 0) {
            std::cerr << "Empty line in config file\n"; 
            throw;
        }

        if (words[0][0] == '#') {
            continue;
        }

        ConverterWrapperFactory* factory = converterManager.getConverter(words[0]);
        ConverterWrapper* converter = factory->create(words);
        converters.push_back(converter);
    }
    return converters;
}