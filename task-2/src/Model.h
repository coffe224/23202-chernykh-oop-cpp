#pragma once

#include "Universe.h"

class Model
{
    public:
        Model();

        void iterate(int iterations = 1);
        void initializeUniverse(std::string universe_name, std::string rules,
                                int width_of_field, int height_of_field,
                                std::vector<std::pair<int, int>> points);
        
        std::string getName();
        std::string getRules();
        std::pair<int, int> getSize();
        std::vector<std::pair<int, int>> getAliveCells();
        std::vector<std::vector<bool>> getCurrentField();
        int getIteration();

    private:
        Universe universe;

        void setRules(std::string rules);
};