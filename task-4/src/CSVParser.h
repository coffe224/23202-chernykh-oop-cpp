#include <fstream>
#include <tuple>

class ParserIterator
{
    public:
        ParserIterator(std::ifstream& stream, std::size_t start_line = 0) : stream_(&stream);
        ParserIterator() : stream_(nullptr), line_index(0) {}
        ~ParserIterator();

        ParserIterator& operator++();
        ParserIterator& operator++(int);

        bool operator==(const ParserIterator& second_it);
        bool operator!=(const ParserIterator& second_it);

        ParserIterator operator=(const ParserIterator& second_it);

        std::tuple<int> operator*();
    private:
        std::ifstream* stream_;
        std::size_t line_index;

};

class CSVParser
{
    public:
        CSVParser(std::ifstream& file, std::size_t lines_to_skip)
            : fileStream(file), startLine(lines_to_skip)
        {
        }

        ParserIterator begin()
        {
            std::ifstream begin_file_stream = fileStream;
            begin_file_stream.seekg(0, begin_file_stream.beg);
            return ParserIterator(begin_file_stream, startLine);
        }

        ParserIterator end()
        {
            std::ifstream begin_file_stream = fileStream;
            begin_file_stream.seekg(0, begin_file_stream.end);
            return ParserIterator(begin_file_stream, startLine);
        }

    private:
        std::ifstream& fileStream;
        std::size_t startLine;
};