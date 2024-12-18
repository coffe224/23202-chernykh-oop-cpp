#include <fstream>
#include <iostream>

#include "CSVParser.h"
#include "TuplePrinter.h"

int main()
{
    std::ifstream file("../test_files/test.csv");
    std::cout << "Parse file test.csv:\n";
    CSVParser<int, std::string, float> parser(file, 0);

    for (auto rs : parser) {
        std::cout << rs << std::endl;
    }

    std::ifstream file1("../test_files/test1.csv");
    std::cout << "\nParse file test1.csv:\n";
    CSVParser<std::string, int> parser1(file1, 0);

    try {
        for (auto rs : parser1) {
            std::cout << rs << std::endl;
        }
    } catch (...) {
        std::cout << "\nNow with another special chars:\n";
    }

    parser1.setSpecial('|', ',', '\n');
    for (auto rs : parser1) {
            std::cout << rs << std::endl;
    }

    std::ifstream file2("../test_files/test2.csv");
    std::cout << "\nParse file test2.csv:\n";
    CSVParser<double, double> parser2(file2, 0);

    try {
        for (auto rs : parser2) {
            std::cout << rs << std::endl;
        }
    } catch (...) {
        std::cout << "Error was caught\n";
    }
    
    return 0;
}
