#include "StreamParser.h"

StreamParser::StreamParser(std::ifstream& fileStream,
                           std::size_t num_of_columns)
    : fileStream(fileStream), numOfColumns(num_of_columns)
{
}

std::vector<std::string> StreamParser::getRow()
{
    std::cerr << "getRow\n";
    std::vector<std::string> current_line = {};

    enum Mode { Inside, Default };
    Mode mode = Default;

    bool is_end_of_row = false;
    bool is_end_of_word = false;

    std::string word = "";

    char c;
    while (fileStream.get(c)) {
        if (mode == Default) {
            if (c == escapeSymb) {
                mode = Inside;
            } else if (c == columnDelim) {
                is_end_of_word = true;
            } else if (c == rowDelim) {
                is_end_of_row = true;
            } else {
                word.push_back(c);
            }
        } else {
            if (c == escapeSymb) {
                mode = Default;
            } else {
                word.push_back(c);
            }
        }

        if (is_end_of_word) {
            current_line.push_back(word);
            word = "";
            is_end_of_word = false;
        }

        if (is_end_of_row) {
            break;
        }
    }
    current_line.push_back(word);

    if (numOfColumns != current_line.size()) {
        // std::cerr << "On line " << line_index + 1 << " there are "
        //           << current_line.size() << " columns instead of " <<
        //           numOfColumns
        //           << "\n";
        std::cerr << "I want to die " << current_line.size() <<  " | " << numOfColumns << "\n";
        throw;
    }

    return current_line;
}

bool StreamParser::isEOF() { return fileStream.peek() == EOF; }

void StreamParser::setSpecialSymbols(char escape_symb, char column_delim, char row_delim)
{
    if (escape_symb == column_delim) {
        std::cerr << "A";
        throw;
    }

    if (escape_symb == row_delim) {
        std::cerr << "B";
        throw;
    }

    if (column_delim == row_delim) {
        std::cerr << "C";
        throw;
    }
}

StreamParser::StreamParser(const StreamParser& second_sp)
    : StreamParser(second_sp.fileStream, second_sp.numOfColumns)
{
    this->escapeSymb = second_sp.escapeSymb;
    this->rowDelim = second_sp.rowDelim;
    this->columnDelim = second_sp.columnDelim;
}
