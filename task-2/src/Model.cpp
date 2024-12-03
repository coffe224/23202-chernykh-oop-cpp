#include "Model.h"
#include <iostream>

Model::Model() {std::cout << "get to model" << "\n";}

void Model::initializeUniverse(std::string universe_name, std::string rules,
                        int width_of_field, int height_of_field,
                        std::vector<std::pair<int, int>> points)
{
    std::cout << "setting size" << "\n";
    universe.setSize(width_of_field, height_of_field);

    std::cout << "setting rules" << "\n";
    setRules(rules);
    std::cout << "rules: " << getRules() << "\n";


    std::cout << "setting name" << "\n";
    universe.setName(universe_name);

    std::cout << "setting points" << "\n";
    universe.setAliveCells(points);
}

void Model::setRules(std::string rules) {
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
    for(char& c : birth_nums) {
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
    for(char& c : survival_nums) {
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

std::string Model::getName() {
    return universe.getName();
}

std::string Model::getRules() {
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

std::pair<int, int> Model::getSize() {
    return {universe.getWidth(), universe.getHeight()};
}

int Model::getIteration() {
    return universe.getIteration();
}

std::vector<std::pair<int, int>> Model::getAliveCells() {
    return universe.getAliveCells();
}

std::vector<std::vector<bool>> Model::getCurrentField() {
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
