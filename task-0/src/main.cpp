#include "../include/FileReader.h"
#include "../include/Parser.h"
#include "../include/Statistics.h"
#include "../include/FileWriter.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    std::string input_filename = argv[1];
    std::string output_filename = argv[2];

    FileReader file_reader;
    file_reader.openFile(input_filename);

    Parser parser;
    std::list<std::string> words_list;

    Statistics statistics;

    std::string line;
    while (!file_reader.isEOF()) {
        file_reader.getLine(line);
        std::cout << line << '\n';
        parser.parseLine(line, words_list);
        std::cout << "line was parsed!" << '\n';

        statistics.countList(words_list);

        words_list.clear();
        line.clear();
    }
    file_reader.closeFile(); 

    statistics.printMap();
    
    auto words_statistics = statistics.returnStatistics();

    FileWriter file_writer;
    file_writer.openFile(output_filename);

    for (auto word_info : words_statistics) {
        std::string csv_line;
        
        std::string el0 = std::get<0>(word_info);
        std::string el1 = std::to_string(std::get<1>(word_info));
        std::string el2 = std::to_string(std::get<2>(word_info));

        csv_line = el0 + ';' + el1 + ';' + el2;
        file_writer.writeLine(csv_line);
    }

    file_reader.closeFile();
    
    std::cout << "done!" << '\n';

    return 0;
}
