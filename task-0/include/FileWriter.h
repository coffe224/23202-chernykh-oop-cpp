#include <fstream>

class FileWriter {
    public:
        void openFile(std::string filename);
        bool isOpen();
        void closeFile();
        void writeLine(std::string line);

    private:
        std::ofstream file;
};