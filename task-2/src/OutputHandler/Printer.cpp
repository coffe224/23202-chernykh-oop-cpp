#include "Printer.h"
#include <iostream>

void Printer::print(std::string string) 
{
    std::cout << string << "\n"; 
}

void Printer::print(std::string string, int num)
{
    std::string string_to_print;
    for (int i = 0; i < num; i++) {
        string_to_print += string;
    }
    print(string_to_print);
}
