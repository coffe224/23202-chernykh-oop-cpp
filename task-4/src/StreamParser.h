#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class StreamParser
{
    public:
        StreamParser(std::ifstream& fileStream, std::size_t num_of_columns);
        void setSpecialSymbols(char escape_symb, char column_delim, char row_delim);

        std::vector<std::string> getRow();
        bool isEOF();

        StreamParser(const StreamParser& second_sp);

    private:
        std::ifstream& fileStream;
        std::size_t numOfColumns;

        char escapeSymb = '"';
        char columnDelim = ',';
        char rowDelim = '\n'; 
};