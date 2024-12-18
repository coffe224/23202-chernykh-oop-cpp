#include "StreamParser.h"

StreamParser::StreamParser(std::ifstream& fileStream,
                           std::size_t num_of_columns)
    : fileStream(fileStream), numOfColumns(num_of_columns)
{
}

std::vector<std::string> StreamParser::getRow()
{
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
        std::string error_message = "expected " + std::to_string(numOfColumns) +
                                    " columns, got " +
                                    std::to_string(current_line.size());
        throw std::length_error(error_message);
    }

    return current_line;
}

void StreamParser::reset()
{
    fileStream.clear();
    fileStream.seekg(0);
}

bool StreamParser::isEOF() { return fileStream.peek() == EOF; }

void StreamParser::setSpecialSymbols(char escape_symb, char column_delim,
                                     char row_delim)
{
    if (escape_symb == column_delim) {
        std::cerr
            << "Can't have the same escape character and column delimeter\n";
        throw;
    }

    if (escape_symb == row_delim) {
        std::cerr << "Can't have the same escape character and row delimeter\n";
        throw;
    }

    if (column_delim == row_delim) {
        std::cerr << "Can't have the same row delimeter and column delimeter\n";
        throw;
    }

    escapeSymb = escape_symb;
    columnDelim = column_delim;
    rowDelim = row_delim;
}