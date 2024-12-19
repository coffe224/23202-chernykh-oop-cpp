#include <iostream>

#include "OutputHandler.h"

void OutputHandler::sendHelpMessage(std::string message)
{
    std::cerr << "\n";
    if (message != "") {
        std::cerr << message << "\n"; 
    }
    std::cerr << helpMessage << "\n";
}

void OutputHandler::sendHelpMessageArgs(std::string message)
{
    std::cerr << "\n";
    if (message != "") {
        std::cerr << message << "\n"; 
    }
    std::cerr << helpMessageArgs << "\n";
}


void OutputHandler::readyForInput()
{
    std::cerr << "> ";
}

void OutputHandler::dumpUniverse(UniverseWrapper* model, std::string output_filename)
{
    fileWriter.open(output_filename);

    fileWriter.writeLine("#Life 1.06");
    fileWriter.writeLine("#N " + model->getName());
    fileWriter.writeLine("#R " + model->getRules());

    auto sizes = model->getSize();
    fileWriter.writeLine("#S " + std::to_string(sizes.first) + " " +
                         std::to_string(sizes.second));

    for (auto coords : model->getAliveCells()) {
        fileWriter.writeLine(std::to_string(coords.first) + " " +
                             std::to_string(coords.second));
    }

    fileWriter.close();
}

void OutputHandler::printUniverse(UniverseWrapper* model)
{
    int width = model->getSize().first;
    int height = model->getSize().second;

    std::string universe_info_string;
    std::string name = "NAME: " + model->getName();
    std::string rules = "RULES: " + model->getRules();
    std::string iterations = "ITERATION: " + std::to_string(model->getIteration());

    printer.print(name + " | " + rules + " | " + iterations);


    std::vector<std::vector<bool>> field = model->getCurrentField();

    printer.print("▁", 2 * width + 2);
    for (auto row : field) {
        std::string string_row = "▌";
        for (int i = 0; i < width; i++) {
            if (row[i]) {
                string_row += "██";
            } else {
                string_row += "  ";
            }
        }
        string_row += "▐";
        printer.print(string_row);
    }
    printer.print("▔", 2 * width + 2);

}