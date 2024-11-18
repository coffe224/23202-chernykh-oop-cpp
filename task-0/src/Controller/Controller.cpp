#include "Controller.h"
#include <iostream>

void Controller::CountWords(const std::string& input_filename,
                            const std::string& output_filename)
{
    fileReader.openFile(input_filename);
    if (!fileReader.isOpen()) {
        std::cout << "Wrong input filename" << '\n';
        return;
    }

    while (!fileReader.isEOF()) {
        lineOfFile = fileReader.getLine();
        wordsList = parser.getWords(lineOfFile);
        statistics.put(wordsList);
    }
    fileReader.closeFile();

    std::vector<std::tuple<std::string, int, double>> words_statistics =
        statistics.getStats();

    fileWriter.openFile(output_filename);
    if (!fileWriter.isOpen()) {
        std::cout << "Wrong output filename" << '\n';
        return;
    }

    for (std::tuple<std::string, int, double> word_info : words_statistics) {
        std::string csv_line = converter.convertTupleToString(word_info, ";");
        fileWriter.writeLine(csv_line);
    }
    fileWriter.closeFile();
}