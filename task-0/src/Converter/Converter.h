#include <string>

class Converter
{
    public:
        std::string convertTupleToString(
            const std::tuple<std::string, int, double>& input_tuple,
            const std::string& delim);
};