#include <fstream>
#include <string>

class FileReader {
    public:
        void openFile(std::string& input_filename);
        bool isOpen() const;
        bool isEOF();
        void closeFile();
        void getLine(std::string& line);

    private:
        std::ifstream file;
};
