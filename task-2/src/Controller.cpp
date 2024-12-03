#include "Controller.h"
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

Controller::Controller() 
{
    rules = "B3/S23";
    universeName = "Default Universe";

    widthOfField = 30;
    heightOfField = 30;

    points = {{3, 3}, {4, 2}, {4, 4}, {6, 2}, {7, 4}, {7, 5}, {6, 5}, {8, 5}};
}

void Controller::parseUniverse(std::string input_filename)
{
    std::cout << "start parsing" << "\n";
    fileReader.open(input_filename);
    std::string line;
    std::vector<std::string> words;

    std::cout << "get line life" << "\n";
    line = fileReader.getLine();
    words = stringParser.getWords(line);
    if (words.size() != 2) {
        std::cout << "throw 1" << "\n";
        throw;
    }
    if (words[0] != "#Life" || words[1] != "1.06") {
        std::cout << words[0] << " " << words[1] << "\n";
        std::cout << "throw 2" << "\n";
        throw;
    }

    line = fileReader.getLine();
    words = stringParser.getWords(line);
    if (words[0] == "#N") {
        universeName = line.substr(line.find_first_not_of(' ', 2));

        line = fileReader.getLine();
        words = stringParser.getWords(line);
    }

    if (words[0] == "#R") {
        if (words.size() != 2) {
            std::cout << "throw 3" << "\n";
            throw;
        }
        rules = words[1];

        line = fileReader.getLine();
        words = stringParser.getWords(line);
    }

    if (words[0] == "#S") {
        if (words.size() != 3) {
            std::cout << "throw 4" << "\n";
            throw;
        }

        widthOfField = std::stoi(words[1]);
        heightOfField = std::stoi(words[2]);
    } else {
        std::cout << "throw 5" << "\n";
        throw;
    }

    std::cout << "start checking points" << "\n";
    while (!fileReader.isEOF()) {
        std::cout << "check" << "\n";
        line = fileReader.getLine();
        std::cout << line << "\n"; 

        words = stringParser.getWords(line);

        for (auto word : words) {
            std::cout << word << "\n"; 
        }

        if (words.size() != 2) {
            std::cout << "throw 6" << "\n";
            throw;
        }

        try {
            int x = std::stoi(words[0]);
            int y = std::stoi(words[1]);
            points.push_back({x, y});
        } catch (std::exception& e) {
            std::cout << words[0] << " " << words[1] << "\n"; 
            throw;
        }
        std::cout << "done" << "\n";
    }
    std::cout << "parsing is done" << "\n";
}

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
                model.iterate();
                view.printUniverse(model);
            } else if (command.num_of_args == 1) {
                try {
                    model.iterate(std::stoi(command.args[0]));
                    view.printUniverse(model);
                } catch (std::exception& e) {
                    view.sendHelpMessage("Wrong iterations number. See help:");
                }
            } else {
                view.sendHelpMessage("Too many arguments for iterations number. See help:");
            }

            
        } else if (command.name == "dump") {
            if (command.num_of_args == 0) {
                view.sendHelpMessage("No output file name. See help:");
            } else if (command.num_of_args > 1) {
                view.sendHelpMessage("Too many arguments for file name. See help:");
            } else {
                try {
                    view.dumpUniverse(model, command.args[0]);
                } catch (std::exception& e) {
                    view.sendHelpMessage("Wrong file name. See help:");
                }
            }
        } else if (command.name == "auto") {
            while (true) {
                model.iterate();
                view.printUniverse(model);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        } else {
            view.sendHelpMessage("Wrong name command '" + command.name + "'. See help:");
        }
    }
}

void Controller::start()
{
    std::cout << "get to initialization" << "\n";
    model.initializeUniverse(universeName, rules, widthOfField, heightOfField,
                             points);

    std::cout << "get to game loop" << "\n";
    gameLoop();
}

void Controller::start(std::string input_filename)
{
    parseUniverse(input_filename);
    model.initializeUniverse(universeName, rules, widthOfField, heightOfField,
                             points);
    gameLoop();
}

void Controller::start(std::string input_filename, std::string output_filename,
                       int iterations)
{
    parseUniverse(input_filename);
    model.initializeUniverse(universeName, rules, widthOfField, heightOfField,
                             points);

    model.iterate(iterations);
    view.dumpUniverse(model, output_filename);
}
