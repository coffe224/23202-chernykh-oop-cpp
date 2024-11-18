#include <fstream>

class FileWriter
{
    public:
        void openFile(const std::string& filename);
        bool isOpen();
        void closeFile();
        void writeLine(const std::string& line);

    private:
        std::ofstream file;
};