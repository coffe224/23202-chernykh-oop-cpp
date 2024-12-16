#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>

#include "StreamParser.h"

template <typename... Args> class ParserIterator;

template <typename... Args> class CSVParser
{
    public:
        CSVParser(std::ifstream& stream, std::size_t lines_to_skip)
            : fileStream(stream), startLine(lines_to_skip)
        {
        }

        ParserIterator<Args...> begin()
        {
            std::cout << "Create begin\n";
            return ParserIterator<Args...>(fileStream, startLine);
        }

        ParserIterator<Args...> end()
        {
            std::cout << "Create end\n";
            return ParserIterator<Args...>(fileStream);
        }

    private:
        std::ifstream& fileStream;
        std::size_t startLine;
};

template <typename... Args> class ParserIterator
{
    public:
        ParserIterator(std::ifstream& stream, std::size_t start_line)
            : streamParser(stream, sizeof...(Args)), isBegIt(true)
        {
            while (!isEndIt && (iCurRow < start_line)) {
                ++(*this);
            }
            getRow();
        }

        ParserIterator(std::ifstream& stream)
            : streamParser(stream, sizeof...(Args)), isEndIt(true)
        {
        }

        ParserIterator<Args...>& operator++()
        {
            std::cout << "operator++()\n";
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
            std::cout << "Create parser by operator=\n";
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

        StreamParser streamParser;

        std::size_t iCurRow = 0;
        std::size_t iCurCol = 0;
        bool isEndIt = false;
        bool isBegIt = false;

        std::vector<std::string> curRow;
        std::tuple<Args...> resultTuple;

        ParserIterator(const ParserIterator<Args...>& second_it)
            : streamParser(second_it.streamParser)
        {
            std::cout << "Damn bro how did you get here\n";
            if (!second_it.isBegIt) {
                std::cerr << "Can only create copy of one object";
                throw;
            }

            if (second_it.isEndIt) {
                this->isEndIt = true;
            } else {
                this->iCurRow = second_it.iCurRow;
                getRow();
            }
        }

        void getRow()
        {
            isEndIt = streamParser.isEOF();

            if (!isEndIt) {
                curRow = streamParser.getRow();
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
                throw;
            }

            iCurCol++;
            return result;
        }
};