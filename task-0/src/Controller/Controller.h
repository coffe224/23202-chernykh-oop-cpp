#include "../FileReader/FileReader.h"
#include "../Parser/Parser.h"
#include "../Statistics/Statistics.h"
#include "../FileWriter/FileWriter.h"
#include "../Converter/Converter.h"

class Controller {
    public:
        void CountWords(std::string& input_filename, std::string& output_filename);

    private:
        FileReader fileReader;
        FileWriter fileWriter;
        Statistics statistics;
        Converter converter;
        Parser parser;

        std::list<std::string> wordsList;
        std::string lineOfFile;
};