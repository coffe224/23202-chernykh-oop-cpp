#include "Controller.h"

void Controller::CountWords(std::string& input_filename, std::string& output_filename) {
    fileReader.openFile(input_filename);

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

    for (auto word_info : words_statistics) {
        std::string csv_line = converter.convertTupleToString(word_info, ";");
        fileWriter.writeLine(csv_line);
    }
    fileWriter.closeFile();
}