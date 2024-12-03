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

// dump [filename]
// example: dump output.txt

// tick [n=1]
// example: tick 4 | t 78

// help

// exit

// already parsed input

// parseInput?
// std::vector size == 1 == 2 == 0;