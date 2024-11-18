#include "../Converter/Converter.h"
#include "../FileReader/FileReader.h"
#include "../FileWriter/FileWriter.h"
#include "../Parser/Parser.h"
#include "../Statistics/Statistics.h"

class Controller
{
    public:
        void CountWords(const std::string& input_filename,
                        const std::string& output_filename);

    private:
        FileReader fileReader;
        FileWriter fileWriter;
        Statistics statistics;
        Converter converter;
        Parser parser;

        std::list<std::string> wordsList;
        std::string lineOfFile;
};