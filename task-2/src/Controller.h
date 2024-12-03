#include "CommandListener.h"
#include "FileReader.h"
#include "StringParser.h"

#include "Model.h"
#include "View.h"

class Controller
{
    private:
        std::string helpArgumentsOutput;
        std::string helpCommandEvents;

        // аргументы вселенной (дефолтные) (размер, вектор, имя, правила)

        int widthOfField = 30;
        int heightOfField = 30;

        std::vector<std::pair<int, int>> points;

        std::string rules;
        std::string universeName;

        CommandListener commandListener;
        FileReader fileReader;
        StringParser stringParser;

        Model model;
        View view;
        
        void parseUniverse(std::string input_filename);
        void gameLoop();
        // void cleanup();

    public:
        Controller();

        void start();
        void start(std::string input_filename);
        void start(std::string input_filename, std::string output_filename, int iterations);
};

// Добавить функцию для вывода ошибок (вывод справок, варнингов и ошибок сделать через std::cerr)
// Расставить везде в функциях и коде классы FileReader и FileWriter, добавить обработку ошибок.
// cleanup function?

// переделать систему ворнингов на сразу вывод в std::cerr

// убрать контроллер, писать всё в мейне?

// ПЕРЕДЕЛАТЬ В MVC??????? думай думай

