#include "Controller/Controller.h"

#include <cassert>
#include <iostream>

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        std::cout << "Wrong number of arguments" << '\n';
        return 0;
    }
    
    std::string input_filename = argv[1];
    std::string output_filename = argv[2];

    Controller controller;
    controller.CountWords(input_filename, output_filename);

    return 0;
}
