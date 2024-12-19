#include <string>
#include <fstream>
#include <vector>

class FileWriter
{
    private:
        std::ofstream file;
    public:
        bool isOpen();
        void open(std::string output_filename);
        void close();
        void writeLine(std::string string);
        void write(std::vector<std::pair<int, int>> vector_of_pairs);
};