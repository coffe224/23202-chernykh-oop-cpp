#include "InputListener.h"

struct Command {
    std::string name;
    int num_of_args;
    std::vector<std::string> args;
};

class CommandListener {
    public:
        Command listenForCommand();
    private:
        InputListener inputListener;
};

