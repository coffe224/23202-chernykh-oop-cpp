#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>

#include "StreamParser/StreamParser.h"

template <typename... Args> class ParserIterator;

template <typename... Args> class CSVParser
{
    public:
        CSVParser(std::ifstream& stream, std::size_t lines_to_skip)
            : startLine(lines_to_skip), streamParser(stream, sizeof...(Args))
        {
        }

        void setSpecial(char escape_symb, char column_delim, char row_delim)
        {
            streamParser.setSpecialSymbols(escape_symb, column_delim,
                                           row_delim);
        }

        ParserIterator<Args...> begin()
        {
            return ParserIterator<Args...>(streamParser, startLine);
        }

        ParserIterator<Args...> end()
        {
            return ParserIterator<Args...>(streamParser);
        }

    private:
        StreamParser streamParser;
        std::size_t startLine;
};

template <typename... Args> class ParserIterator
{
    public:
        ParserIterator(StreamParser& streamParser, std::size_t start_line)
            : streamParser(streamParser), isBegIt(true)
        {
            streamParser.reset();
            while (!isEndIt && (iCurRow < start_line)) {
                ++(*this);
            }
            getRow();
        }

        ParserIterator(StreamParser& streamParser)
            : streamParser(streamParser), isEndIt(true)
        {
        }

        ParserIterator<Args...>& operator++()
        {
            getRow();
            iCurRow++;
            return *this;
        }

        bool operator==(const ParserIterator<Args...>& second_it)
        {
            if (isEndIt && second_it.isEndIt) {
                return true;
            }
            return false;
        }

        bool operator!=(const ParserIterator<Args...>& second_it)
        {
            return !(*this == second_it);
        }

        ParserIterator<Args...>
        operator=(const ParserIterator<Args...>& second_it)
        {
            ParserIterator<Args...> new_it(this);
            return new_it;
        }

        std::tuple<Args...> operator*()
        {
            fillTuple<0, Args...>();
            return resultTuple;
        }

    private:
        std::size_t num_args = sizeof...(Args);

        StreamParser& streamParser;

        std::size_t iCurRow = 0;
        std::size_t iCurCol = 0;
        bool isEndIt = false;
        bool isBegIt = false;

        std::vector<std::string> curRow;
        std::tuple<Args...> resultTuple;

        void getRow()
        {
            isEndIt = streamParser.isEOF();

            if (!isEndIt) {
                try {
                    curRow = streamParser.getRow();
                } catch (std::length_error& e) {
                    std::cerr
                        << "ERROR: invalid number of columns in row number "
                        << iCurRow + 1 << ": " << e.what() << "\n";
                    throw e;
                }
            }
        }

        template <std::size_t M, typename First, typename... Rest>
        void fillTuple()
        {
            std::get<M>(resultTuple) = getCell<First>();
            return fillTuple<M + 1, Rest...>();
        }

        template <std::size_t M> void fillTuple()
        {
            iCurCol = 0;
            return;
        }

        template <typename T>
        typename std::enable_if_t<std::is_same<T, std::string>::value,
                                  std::string>
        getCell()
        {
            std::string result = curRow[iCurCol];
            iCurCol++;
            return result;
        }

        template <typename T>
        typename std::enable_if_t<!std::is_same<T, std::string>::value, T>
        getCell()
        {
            T result;
            std::stringstream ss(curRow[iCurCol]);
            ss >> result;

            if (ss.tellg() != -1) {
                std::cerr << "ERROR: row " << iCurRow + 1 << ", column "
                          << iCurCol + 1 << "\n";
                throw std::invalid_argument("Invalid file");
            }

            iCurCol++;
            return result;
        }
};