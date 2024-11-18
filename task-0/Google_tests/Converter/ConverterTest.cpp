#include <gtest/gtest.h>

#include "../../src/Converter/Converter.h"

TEST(ConverterTestSuite, EmptyString) {
    Converter converter;
    std::string word = "";
    std::tuple<std::string, int, double> tuple{word, 0, 0};
    ASSERT_EQ(converter.convertTupleToString(tuple, ";"), ";0;0.000000");
}

TEST(ConverterTestSuite, NotEmptyString) {
    Converter converter;
    std::string word = "word";
    std::tuple<std::string, int, double> tuple{word, 0, 0};
    ASSERT_EQ(converter.convertTupleToString(tuple, ";"), "word;0;0.000000");
}

TEST(ConverterTestSuite, EmptyDelimeter) {
    Converter converter;
    std::string word = "word";
    std::tuple<std::string, int, double> tuple{word, 0, 0};
    ASSERT_EQ(converter.convertTupleToString(tuple, ""), "word00.000000");
}

TEST(ConverterTestSuite, NumbersTest) {
    Converter converter;
    std::string word = "9999";
    std::tuple<std::string, int, double> tuple{word, 849384, 12.1};
    std::string doub = std::to_string(12.1);
    ASSERT_EQ(converter.convertTupleToString(tuple, ";"), "9999;849384;" + doub);
}