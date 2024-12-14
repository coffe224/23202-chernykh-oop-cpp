#include <iostream>

#include "CSVParser.h"
#include "TuplePrinter.h"

int main()
{
    std::ifstream file("test.csv");
    // CSVParser<int, std::string> parser(file, 0 /*skip first lines count*/);
    for (auto rs : parser) {
        std::cout << rs << std::endl;
    }
}