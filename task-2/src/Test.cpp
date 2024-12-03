#include <string>
#include <vector>
#include "ArgParser.h"

int main(int argc, char const *argv[])
{
    ArgParser arg_parser;

    arg_parser.addOption('h', "help", 0);
    arg_parser.addOption('o', "output", 1);
    arg_parser.addOption('i', "iterations", 1);
    arg_parser.addPosOption("input_filename", 1);

    arg_parser.parseArguments(argc, argv);

    if (arg_parser.isEmpty()) {
        return 0;
    }

    if (arg_parser.hasOpt("help")) { 
        if (arg_parser.getOptArgs("help") != "") {
            throw;
        }
        std::cout << "help message" << "\n";
        return 0;
    }

    if (arg_parser.hasNoPosOptions()) {
        throw;
    }

    std::string input_filename = arg_parser.getPosOptArgs("input_filename")[0];

    if (arg_parser.hasNoOptions()) {
        return 0;
    } else if (arg_parser.hasOpt("output") && arg_parser.hasOpt("iterations")) {
        std::string output_filename = arg_parser.getOptArgs("output");
        std::string iterations_str = arg_parser.getOptArgs("iterations");
        try {
            int iterations = std::stoi(iterations_str);
        } catch (std::exception& e) {
            return 1;
        }
    } else {
        throw;
    }
}