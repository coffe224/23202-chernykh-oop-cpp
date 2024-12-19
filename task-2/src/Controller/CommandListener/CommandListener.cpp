#include "CommandListener.h"
#include <iostream>

Command CommandListener::listenForCommand()
{
    std::vector<std::string> parsed_input = inputListener.getInput();
    
    Command command;
    command.name = parsed_input[0];
    command.num_of_args = parsed_input.size() - 1;
    command.args = {parsed_input.begin() + 1, parsed_input.end()};

    return command;
}