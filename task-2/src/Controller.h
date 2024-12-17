#include "CommandListener.h"
#include "UniverseParser.h"

#include "Model.h"
#include "View.h"

class Controller
{
    private:
        enum Mode {Default, Offline, InputFile};
        Mode mode = Default;

        CommandListener commandListener;
        UniverseParser universeParser;

        Model* model = nullptr;
        View view;
        
        void gameLoop();
    public:
        void start();
        void start(std::string input_filename);
        void start(std::string input_filename, std::string output_filename, int iterations);
};
