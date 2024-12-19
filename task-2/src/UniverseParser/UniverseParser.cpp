#include <iostream>

#include "UniverseParser.h"

UniverseWrapper* UniverseParser::createUniverse()
{
    return new UniverseWrapper(universeName, universeRules, universeSizes, universePoints);
}

UniverseWrapper* UniverseParser::parse(std::string input_filename) { 
    fileReader.open(input_filename);

    if (getParam("#Life ") != "1.06") {
        std::cerr << "Error: wrong format\n";
        throw std::exception();
    }

    std::string name_param = getParam("#N ");
    if (name_param == "") {
        std::cerr << "Warning: no universe name, using default\n";
    } else {
        universeName = name_param;
    }

    std::string rules_param = getParam("#R ");
    if (rules_param == "") {
        std::cerr << "Warning: no universe rules, using default\n";
    } else {
        universeRules = rules_param;
    }

    std::string size_param = getParam("#S ");
    if (size_param == "") {
        std::cerr << "Error: no universe sizes\n";
        throw std::exception();
    } else {
        universeSizes = size_param;
    }

    universePoints.clear();
    while (!fileReader.isEOF()) {
        universePoints.push_back(getParam());
    }

    return createUniverse();
}

std::string UniverseParser::getParam(std::string what_param)
{
    if (!hasLine) {
        fileLine = fileReader.getLine();
        hasLine = true;
    }

    if (fileLine.find(what_param) == 0) {
        hasLine = false;
        return std::string(fileLine, what_param.size());
    }
    
    return std::string();
}