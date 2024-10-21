#include <gtest/gtest.h>

#include "../../src/Parser/Parser.h"

TEST(ParserTestSuite, EmptyString) {
    Parser parser;

    std::string line = "";
    std::list<std::string> list;

    parser.parseLine(line, list);
    ASSERT_EQ(list.size(), 0);
}

TEST(ParserTestSuite, DelimeterString) {
    Parser parser;

    std::string line = "/.,.   /,/,.,/..,  ..!%@&#% &!@#*!&  @^%[]{}((()))";
    std::list<std::string> list;

    parser.parseLine(line, list);
    ASSERT_EQ(list.size(), 0);
}

TEST(ParserTestSuite, WordString) {
    Parser parser;

    std::string line = "meow.meow...meow  meow!!!!!!!!!meow";
    std::list<std::string> list;

    parser.parseLine(line, list);
    ASSERT_EQ(list.size(), 5);
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(list.back(), "meow");
        list.pop_back();
    }
}

TEST(ParserTestSuite, CaseWordString) {
    Parser parser;

    std::string line = "BIG,big BiG...big";
    std::list<std::string> list;

    parser.parseLine(line, list);
    ASSERT_EQ(list.size(), 4);
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(list.back(), "big");
        list.pop_back();
    }
}

TEST(ParserTestSuite, NumberWordString) {
    Parser parser;

    std::string line = "number1 999 31Number31";
    std::list<std::string> list;

    parser.parseLine(line, list);
    ASSERT_EQ(list.size(), 3);

    ASSERT_EQ(list.back(), "31number31");
    list.pop_back();
    ASSERT_EQ(list.back(), "999");
    list.pop_back();
    ASSERT_EQ(list.back(), "number1");
    list.pop_back();
}