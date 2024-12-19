#include <string>
#include <fstream>


class FileReader
{
    private:
        std::ifstream file;

    public:
        bool isOpen() const;
        bool isEOF();
        void open(const std::string& input_filename);
        void close();
        std::string getLine();
};