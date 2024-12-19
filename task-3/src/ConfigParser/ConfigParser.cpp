#include "ConfigParser.h"
#include <iostream>

ConfigParser::ConfigParser(std::string filename)
{
    fileReader.open(filename);
}

std::vector<std::string> ConfigParser::getCommand()
{
    std::vector<std::string> words = {}; 
    while (!fileReader.isEOF())
    {
        words = stringParser.getWords(fileReader.getLine());

        if (words.size() == 0) {
            std::cerr << "Empty line in config file\n"; 
            throw;
        }

        if (words[0][0] == '#') {
            continue;
        }

        break;
    }
    return words;
}