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
        fileReader.getLine(lineOfFile);
        parser.parseLine(lineOfFile, wordsList);
        statistics.countList(wordsList);

        wordsList.clear();
        lineOfFile.clear();
    }
    fileReader.closeFile();

    auto words_statistics = statistics.returnStatistics();

    fileWriter.openFile(output_filename);
    if (!fileWriter.isOpen()) {
        std::cout << "Wrong output filename" << '\n';
        return;
    }

    for (auto word_info : words_statistics) {
        std::string csv_line = converter.convertTupleToString(word_info, ";");
        fileWriter.writeLine(csv_line);
    }
    fileWriter.closeFile();
}