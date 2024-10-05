#include "../include/Statistics.h"
#include <iostream>
#include <algorithm>

Statistics::Statistics() {
    wordsTotal = 0;
}

void Statistics::countWord(std::string& word) {
    if (wordsMap.find(word) == wordsMap.end()) {
        wordsMap[word] = 1;
    } else {
        wordsMap[word] += 1;
    }
    wordsTotal++;
}

void Statistics::countList(std::list<std::string>& words_list) {
    std::list<std::string>::iterator it;
    for (it = words_list.begin(); it != words_list.end(); it++) {
        countWord(*it);
    }
}

void Statistics::printMap() {
    std::map<std::string, int>::iterator it;
    for (it = wordsMap.begin(); it != wordsMap.end(); it++) {
        std::cout << it->first << " : " << it->second << '\n';
    }
}

std::vector<std::tuple<std::string, int, double>> Statistics::returnStatistics() {
    int unique_words = wordsMap.size();
    
    std::vector<std::tuple<std::string, int, double>> statistics_vector(unique_words);
    auto vec_it = statistics_vector.begin();

    std::map<std::string, int>::iterator it;
    for (it = wordsMap.begin(); it != wordsMap.end(); it++, vec_it++) {
        int word_count = it->second;
        double word_percent = (100 * it->second) / static_cast<double>(wordsTotal);

        auto word_info = std::make_tuple(it->first, word_count, word_percent);
        *vec_it = word_info;
    }

    SortStatistics(statistics_vector);
    return statistics_vector;
}

void Statistics::SortStatistics(std::vector<std::tuple<std::string, int, double>> &stat_vec) {
    std::sort(stat_vec.begin(), stat_vec.end(), CompareTuples);
}

bool Statistics::CompareTuples(const std::tuple<std::string, int, double>& t1, const std::tuple<std::string, int, double>& t2) {
    return std::get<1>(t1) > std::get<1>(t2);
}