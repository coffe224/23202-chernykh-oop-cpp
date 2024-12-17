#include "Model.h"
#include <iostream>
#include <sstream>

Model::Model(std::string universe_name, std::string rules, std::string sizes,
             std::vector<std::string> string_points)
{
    universe.setName(universe_name);

    try {
        setRules(rules);
    } catch (...) {
        std::cerr << "Error: bad rules\n";
        throw;
    }

    try {
        setSize(sizes);
    } catch (...) {
        std::cerr << "Error: bad sizes\n";
        throw;
    }

    try {
        setPoints(string_points);
    } catch (...) {
        std::cerr << "Error: bad points\n";
        throw;
    }
}

void Model::setRules(std::string rules)
{
    if (rules.size() < 5 || rules.size() > 21) {
        throw;
    }

    std::size_t pos_b = rules.find('B');
    std::size_t pos_del = rules.find('/');
    std::size_t pos_s = rules.find('S');

    if (pos_b != 0 || pos_del == -1 || pos_s == -1 || pos_s != pos_del + 1) {
        throw;
    }

    std::string birth_nums = rules.substr(pos_b + 1, pos_del - 1);
    std::string survival_nums = rules.substr(pos_s + 1);

    std::array<bool, 9> birth_vals;
    birth_vals.fill(false);
    for (char& c : birth_nums) {
        if (c < '0' || c > '8') {
            throw;
        }
        int num = c - '0';
        if (birth_vals[num]) {
            throw;
        } else {
            birth_vals[num] = true;
        }
    }

    std::array<bool, 9> survival_vals;
    survival_vals.fill(false);
    for (char& c : survival_nums) {
        if (c < '0' || c > '8') {
            throw;
        }
        int num = c - '0';
        if (survival_vals[num]) {
            throw;
        } else {
            survival_vals[num] = true;
        }
    }
    universe.setRules(birth_vals, survival_vals);
}

std::string Model::getName() { return universe.getName(); }

std::string Model::getRules()
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

void Model::setSize(std::string string_sizes)
{
    std::pair<std::size_t, std::size_t> sizes = convert(string_sizes);
    universe.setSize(sizes.first, sizes.second);
}

void Model::setPoints(std::vector<std::string>& string_points)
{
    std::vector<std::pair<std::size_t, std::size_t>> alive_points;
    for (auto string_point : string_points) {
        alive_points.push_back(convert(string_point));
    }
    universe.setAliveCells(alive_points);
}

std::pair<std::size_t, std::size_t> Model::convert(std::string string_pair)
{
    std::stringstream ss(string_pair);
    std::pair<std::size_t, std::size_t> pair;
    ss >> pair.first;
    ss >> pair.second;
    return pair;
}

std::pair<std::size_t, std::size_t> Model::getSize()
{
    return {universe.getWidth(), universe.getHeight()};
}

int Model::getIteration() { return universe.getIteration(); }

std::vector<std::pair<std::size_t, std::size_t>> Model::getAliveCells()
{
    return universe.getAliveCells();
}

std::vector<std::vector<bool>> Model::getCurrentField()
{
    return universe.getCurrentField();
}

void Model::iterate(int iterations)
{
    if (iterations < 0) {
        throw;
    }

    for (int i = 0; i < iterations; i++) {
        universe.nextIteration();
    }
}
