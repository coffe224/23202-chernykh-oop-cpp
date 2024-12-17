#include "Controller.h"
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

void Controller::gameLoop()
{
    view.printUniverse(model);

    while (true) {
        view.readyForInput();
        Command command = commandListener.listenForCommand();

        if (command.name == "exit") {
            break;
        } else if (command.name == "help") {
            view.sendHelpMessage();
        } else if (command.name == "tick" || command.name == "t") {
            if (command.num_of_args == 0) {
                model->iterate();
                view.printUniverse(model);
            } else if (command.num_of_args == 1) {
                try {
                    model->iterate(std::stoi(command.args[0]));
                    view.printUniverse(model);
                } catch (std::exception& e) {
                    view.sendHelpMessage("Wrong iterations number. See help:");
                }
            } else {
                view.sendHelpMessage(
                    "Too many arguments for iterations number. See help:");
            }

        } else if (command.name == "dump") {
            if (command.num_of_args == 0) {
                view.sendHelpMessage("No output file name. See help:");
            } else if (command.num_of_args > 1) {
                view.sendHelpMessage(
                    "Too many arguments for file name. See help:");
            } else {
                try {
                    view.dumpUniverse(model, command.args[0]);
                } catch (std::exception& e) {
                    view.sendHelpMessage("Wrong file name. See help:");
                }
            }
        } else if (command.name == "auto") {
            int iterations = 0;
            if (command.num_of_args != 1) {
                view.sendHelpMessage(
                    "Wrong format for this command. See help:");
            }
            try {
                iterations = std::stoi(command.args[0]);
            } catch (std::exception& e) {
                view.sendHelpMessage("Wrong iterations number. See help:");
            }

            for (int i = 0; i < iterations; i++) {
                model->iterate();
                view.printUniverse(model);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        } else {
            view.sendHelpMessage("Wrong name command '" + command.name +
                                 "'. See help:");
        }
    }
}

void Controller::start()
{
    mode = Default;
    model = universeParser.createUniverse();
    gameLoop();
}

void Controller::start(std::string input_filename)
{
    mode = InputFile;
    model = universeParser.parse(input_filename);
    gameLoop();
}

void Controller::start(std::string input_filename, std::string output_filename,
                       int iterations)
{
    mode = Offline;
    model = universeParser.parse(input_filename);

    model->iterate(iterations);
    view.dumpUniverse(model, output_filename);
}
