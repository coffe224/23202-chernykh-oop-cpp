#include <string>
#include <vector>

#include "StringParser.h"

class InputListener
{
    private:
        std::vector<std::string> command;
        StringParser stringParser;
    public:
        std::vector<std::string> getInput();
};