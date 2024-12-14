#include <iostream>

#include "ArgParser.h"
#include "Controller.h"

int main(int argc, char const *argv[])
{
    ArgParser arg_parser;

    arg_parser.addOption('h', "help", 0);
    arg_parser.addOption('c', "config", 1);
    arg_parser.addPosOption("output_wav", 1);
    arg_parser.addPosOption("input_wav", 1);
    arg_parser.addPosOption("add_input_wavs", 10);

    arg_parser.parseArguments(argc, argv);

    if (arg_parser.hasOpt("help")) {
        if (arg_parser.getOptArgs("help") != "") {
            throw;
        }
        std::cout << "help message" << "\n";
        return 0;
    }

    if (!arg_parser.hasOpt("config")) {
        throw;
    }
    std::string config_filename = arg_parser.getOptArgs("config");

    if (!arg_parser.hasPosOpt("output_wav")) {
        throw;
    }
    std::string output_wav = arg_parser.getPosOptArgs("output_wav")[0];

    if (!arg_parser.hasPosOpt("input_wav")) {
        throw;
    }
    std::string input_wav = arg_parser.getPosOptArgs("input_wav")[0];

    std::vector<std::string> add_input_wavs =
        arg_parser.getPosOptArgs("add_input_wavs");

    std::cout << "config file: " << config_filename << "\n";
    std::cout << "input wav: " << input_wav << "\n";
    std::cout << "output wav: " << output_wav << "\n";
    std::cout << "other input wavs: ";

    for (auto file : add_input_wavs) {
        std::cout << file << " ";
    }
    std::cout << "\n";


    return 0;
}
