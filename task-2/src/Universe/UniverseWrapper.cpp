#include "UniverseWrapper.h"
#include <iostream>
#include <sstream>

UniverseWrapper::UniverseWrapper(std::string universe_name, std::string rules, std::string sizes,
             std::vector<std::string> string_points)
{
    universe.setName(universe_name);

    try {
        setRules(rules);
    } catch (std::exception& e){
        std::cerr << "Error: bad rules\n";
        throw e;
    }

    try {
        setSize(sizes);
    } catch (std::invalid_argument& ex) {
        std::cerr << "Error: bad sizes\n";
        throw ex;
    }

    try {
        setPoints(string_points);
    } catch (std::invalid_argument& ex) {
        std::cerr << "Error: bad points\n";
        throw ex;
    }
}

void UniverseWrapper::setRules(std::string rules)
{
    if (rules.size() < 5 || rules.size() > 21) {
        throw std::exception();
    }

    std::size_t pos_b = rules.find('B');
    std::size_t pos_del = rules.find('/');
    std::size_t pos_s = rules.find('S');

    if (pos_b != 0 || pos_del == -1 || pos_s == -1 || pos_s != pos_del + 1) {
        throw std::exception();
    }

    std::string birth_nums = rules.substr(pos_b + 1, pos_del - 1);
    std::string survival_nums = rules.substr(pos_s + 1);

    std::array<bool, 9> birth_vals;
    birth_vals.fill(false);
    for (char& c : birth_nums) {
        if (c < '0' || c > '8') {
            throw std::exception();
        }
        int num = c - '0';
        if (birth_vals[num]) {
            throw std::exception();
        } else {
            birth_vals[num] = true;
        }
    }

    std::array<bool, 9> survival_vals;
    survival_vals.fill(false);
    for (char& c : survival_nums) {
        if (c < '0' || c > '8') {
            throw std::exception();
        }
        int num = c - '0';
        if (survival_vals[num]) {
            throw std::exception();
        } else {
            survival_vals[num] = true;
        }
    }
    universe.setRules(birth_vals, survival_vals);
}

std::string UniverseWrapper::getName() { return universe.getName(); }

std::string UniverseWrapper::getRules()
{
    std::array<bool, 9> survival_rules = universe.getSurvRules();
    std::array<bool, 9> birth_rules = universe.getBirthRules();

    std::string birth_nums;
    std::string surv_nums;

    for (int i = 0; i < birth_rules.size(); i++) {
        if (birth_rules[i]) {
            birth_nums.push_back('0' + i);
        }
        if (survival_rules[i]) {
            surv_nums.push_back('0' + i);
        }
    }

    return "B" + birth_nums + "/S" + surv_nums;
}

void UniverseWrapper::setSize(std::string string_sizes)
{
    std::pair<std::size_t, std::size_t> sizes = convert(string_sizes);
    if (sizes.first > 100 && sizes.second > 100) {
        throw std::invalid_argument("Invalid sizes");
    }
    universe.setSize(sizes.first, sizes.second);
}

void UniverseWrapper::setPoints(std::vector<std::string>& string_points)
{
    std::vector<std::pair<std::size_t, std::size_t>> alive_points;
    for (auto string_point : string_points) {
        alive_points.push_back(convert(string_point));
    }
    universe.setAliveCells(alive_points);
}

std::pair<std::size_t, std::size_t> UniverseWrapper::convert(std::string string_pair)
{
    std::stringstream ss(string_pair);
    std::pair<std::size_t, std::size_t> pair;
    ss >> pair.first;
    ss >> pair.second;
    return pair;
}

std::pair<std::size_t, std::size_t> UniverseWrapper::getSize()
{
    return {universe.getWidth(), universe.getHeight()};
}

int UniverseWrapper::getIteration() { return universe.getIteration(); }

std::vector<std::pair<std::size_t, std::size_t>> UniverseWrapper::getAliveCells()
{
    return universe.getAliveCells();
}

std::vector<std::vector<bool>> UniverseWrapper::getCurrentField()
{
    return universe.getCurrentField();
}

void UniverseWrapper::iterate(int iterations)
{
    if (iterations < 0) {
        throw;
    }

    for (int i = 0; i < iterations; i++) {
        universe.nextIteration();
    }
}
