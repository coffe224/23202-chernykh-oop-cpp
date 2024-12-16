#include <iostream>
#include <fstream>

#include "CSVParser.h"
#include "TuplePrinter.h"


int main()
{
    std::ifstream file("test.csv");
    CSVParser<std::string, int> parser(file, 0);
    
    for (auto rs : parser) {
        std::cout << rs << std::endl;
    }
    return 0;
}
