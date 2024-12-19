#include "CommandListener/CommandListener.h"

#include "../UniverseParser/UniverseParser.h"
#include "../OutputHandler/OutputHandler.h"

class Controller
{
    private:
        CommandListener commandListener;
        UniverseParser universeParser;

        UniverseWrapper* model = nullptr;
        OutputHandler outputHandler;
        
        void gameLoop();
    public:
        void start();
        void start(std::string input_filename);
        void start(std::string input_filename, std::string output_filename, int iterations);
        
        void help(std::string message = "");
};
