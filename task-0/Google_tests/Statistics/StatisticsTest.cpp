#include <gtest/gtest.h>

#include "../../src/Statistics/Statistics.h"

TEST(StatisticsTestSuite, EmptyList) {
    Statistics statistics;
    std::list<std::string> list;
    statistics.countList(list);
    std::vector<std::tuple<std::string, int, double>> words =
        statistics.returnStatistics();
    ASSERT_EQ(words.size(), 0);
}

TEST(StatisticsTestSuite, EmptyWord) {
    Statistics statistics;
    std::string word;
    statistics.countWord(word);
    std::vector<std::tuple<std::string, int, double>> words =
        statistics.returnStatistics();
    ASSERT_EQ(words.size(), 1);
    ASSERT_EQ(std::get<0>(words[0]), "");
    ASSERT_EQ(std::get<1>(words[0]), 1);
    ASSERT_DOUBLE_EQ(std::get<2>(words[0]), double(100) * double(1)/1);
}

TEST(StatisticsTestSuite, NormalWords) {
    Statistics statistics;
    std::list<std::string> list{"meow", "meow", "weom"};
    statistics.countList(list);
    std::vector<std::tuple<std::string, int, double>> words =
        statistics.returnStatistics();
    ASSERT_EQ(words.size(), 2);

    ASSERT_EQ(std::get<0>(words[0]), "meow");
    ASSERT_EQ(std::get<1>(words[0]), 2);
    ASSERT_DOUBLE_EQ(std::get<2>(words[0]), double(100) * double(2)/3);

    ASSERT_EQ(std::get<0>(words[1]), "weom");
    ASSERT_EQ(std::get<1>(words[1]), 1);
    ASSERT_DOUBLE_EQ(std::get<2>(words[1]), double(100) * double(1)/3);
}