#include "InputListener.h"
#include <iostream>

std::vector<std::string> InputListener::getInput() 
{
    std::string input_string;
    std::getline(std::cin, input_string);

    return stringParser.getWords(input_string);
}