#include "Controller/Controller.h"

#include <iostream>
#include <cassert>

int main(int argc, char const *argv[])
{
    assert(argc == 3 && "Incorrect number of arguments");

    std::string input_filename = argv[1];
    std::string output_filename = argv[2];

    Controller controller;
    controller.CountWords(input_filename, output_filename);
    
    return 0;
}
