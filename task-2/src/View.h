#include "FileWriter.h"
#include "Model.h"
#include "Printer.h"

class View
{
    public:
        void sendHelpMessage(std::string message = "");
        void readyForInput();
        void dumpUniverse(Model model, std::string output_filename);
        void printUniverse(Model model);

    private:
        std::string helpMessage =
            "Possible commands:\n"
            "\thelp - print this message\n"
            "\texit - exit program\n"
            "\tdump <input_filename> - dump universe to file\n"
            "\ttick <n=1> | t <n=1> - iterate universe n times and prints it\n";

        FileWriter fileWriter;
        Printer printer;
};