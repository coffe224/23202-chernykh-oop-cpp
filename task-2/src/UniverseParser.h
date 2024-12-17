#include <string>
#include <vector>

#include "FileReader.h"
#include "Model.h"
#include "StringParser.h"

class UniverseParser
{
    public:
        Model* parse(std::string input_filename);
        Model* createUniverse();

    private:
        std::string getParam(std::string what_param = "");

        std::string universeName = "Default Name";
        std::string universeRules = "B3/S23";
        std::string universeSizes = "30 30";
        std::vector<std::string> universePoints = {"3 3", "4 2", "4 4", "6 2",
                                                   "7 4", "7 5", "6 5", "8 5"};

        FileReader fileReader;
        StringParser stringParser;

        bool hasLine;
        std::string fileLine;
};