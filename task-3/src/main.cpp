#include <iostream>

#include "ArgParser/ArgParser.h"
#include "Controller/Controller.h"

int main(int argc, char const *argv[])
{
    ArgParser arg_parser;
    Controller controller;

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
        controller.help();
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

    std::vector<std::string> extra_wavs =
        arg_parser.getPosOptArgs("extra_wavs");

    controller.start(config_filename, output_wav, {input_wav});

    return 0;
}
