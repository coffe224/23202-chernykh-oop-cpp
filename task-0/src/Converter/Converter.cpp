#include "Converter.h"

std::string Converter::convertTupleToString(const std::tuple<std::string, int, double>& input_tuple, const std::string& delim) {
    std::string el0 = std::get<0>(input_tuple);
    std::string el1 = std::to_string(std::get<1>(input_tuple));
    std::string el2 = std::to_string(std::get<2>(input_tuple));
    
    std::string line = el0 + delim + el1 + delim + el2;
    return line;
}