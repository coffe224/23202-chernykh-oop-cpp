#include <fstream>
#include <string>

class FileReader
{
    public:
        void openFile(const std::string& input_filename);
        bool isOpen() const;
        bool isEOF();
        void closeFile();
        std::string getLine();

    private:
        std::ifstream file;
};
