#include "FileWriter.h"
#include "../Universe/UniverseWrapper.h"
#include "Printer.h"

class OutputHandler
{
    public:
        void sendHelpMessage(std::string message = "");
        void readyForInput();
        void dumpUniverse(UniverseWrapper* model, std::string output_filename);
        void printUniverse(UniverseWrapper* model);

    private:
        std::string helpMessage =
            "Possible commands:\n"
            "\thelp - print this message\n"
            "\texit - exit program\n"
            "\tdump <input_filename> - dump universe to file\n"
            "\ttick <n=1> | t <n=1> - iterate universe n times and prints it\n"
            "\tauto <n> - automatically iterate universe n times and prints it every iteration\n";


        FileWriter fileWriter;
        Printer printer;
};