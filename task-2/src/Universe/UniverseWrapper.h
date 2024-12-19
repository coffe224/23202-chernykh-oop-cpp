#pragma once

#include "Universe.h"

class UniverseWrapper
{
    public:
        UniverseWrapper(std::string universe_name, std::string rules, std::string sizes,
              std::vector<std::string> points);

        void iterate(int iterations = 1);

        std::string getName();
        std::string getRules();
        std::pair<std::size_t, std::size_t> getSize();
        std::vector<std::pair<std::size_t, std::size_t>> getAliveCells();
        std::vector<std::vector<bool>> getCurrentField();
        int getIteration();

    private:
        Universe universe;
        void setRules(std::string rules);
        void setPoints(std::vector<std::string>& string_points);
        void setSize(std::string sizes);

        std::pair<std::size_t, std::size_t> convert(std::string string_pair);
};