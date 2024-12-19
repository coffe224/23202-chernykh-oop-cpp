#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

#include "Controller.h"

void Controller::start()
{
    model = universeParser.createUniverse();
    gameLoop();
}

void Controller::start(std::string input_filename)
{
    model = universeParser.parse(input_filename);
    gameLoop();
}

void Controller::start(std::string input_filename, std::string output_filename,
                       int iterations)
{
    model = universeParser.parse(input_filename);

    model->iterate(iterations);
    outputHandler.dumpUniverse(model, output_filename);
}

void Controller::gameLoop()
{
    outputHandler.printUniverse(model);

    while (true) {
        outputHandler.readyForInput();
        Command command = commandListener.listenForCommand();

        if (command.name == "exit") {
            break;
        } else if (command.name == "help") {
            outputHandler.sendHelpMessage();
        } else if (command.name == "tick" || command.name == "t") {
            if (command.num_of_args == 0) {
                model->iterate();
                outputHandler.printUniverse(model);
            } else if (command.num_of_args == 1) {
                try {
                    model->iterate(std::stoi(command.args[0]));
                    outputHandler.printUniverse(model);
                } catch (std::exception& e) {
                    outputHandler.sendHelpMessage("Wrong iterations number. See help:");
                }
            } else {
                outputHandler.sendHelpMessage(
                    "Too many arguments for iterations number. See help:");
            }

        } else if (command.name == "dump") {
            if (command.num_of_args == 0) {
                outputHandler.sendHelpMessage("No output file name. See help:");
            } else if (command.num_of_args > 1) {
                outputHandler.sendHelpMessage(
                    "Too many arguments for file name. See help:");
            } else {
                try {
                    outputHandler.dumpUniverse(model, command.args[0]);
                } catch (std::exception& e) {
                    outputHandler.sendHelpMessage("Wrong file name. See help:");
                }
            }
        } else if (command.name == "auto") {
            int iterations = 0;
            if (command.num_of_args != 1) {
                outputHandler.sendHelpMessage(
                    "Wrong format for this command. See help:");
            }
            try {
                iterations = std::stoi(command.args[0]);
            } catch (std::exception& e) {
                outputHandler.sendHelpMessage("Wrong iterations number. See help:");
            }

            for (int i = 0; i < iterations; i++) {
                model->iterate();
                outputHandler.printUniverse(model);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        } else {
            outputHandler.sendHelpMessage("Wrong name command '" + command.name +
                                 "'. See help:");
        }
    }
}
