#include "Universe.h"
#include <vector>
#include <iostream>

Universe::Field::Field() {
    width = 0;
    height = 0;
}

Universe::Field::~Field() {
    clear();
}

void Universe::Field::clear() {
    cells.clear();
    width = 0;
    height = 0;
}

void Universe::Field::swap(Field field) {
    std::swap(width, field.width);
    std::swap(height, field.height);
    std::swap(cells, field.cells);
}

Universe::Field::Field(std::size_t width, std::size_t height) {
    Field();
    setSize(width, height);
}

void Universe::Field::setSize(std::size_t width_arg, std::size_t height_arg) {
    clear();
    cells.resize(height_arg, std::vector<bool>(width_arg, false));

    width = width_arg;
    height = height_arg;
}

bool Universe::Field::getCell(std::size_t x, std::size_t y) {
    return cells[y][x];
}

void Universe::Field::setCell(std::size_t x, std::size_t y, bool value) {
    cells[y][x] = value;
}

std::size_t Universe::Field::getCellNeighbours(std::size_t x, std::size_t y) {
    int counter = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            std::size_t n_x = x;
            if (i < 0 && n_x == 0) {
                n_x = width - 1;
            } else if (i > 0 && n_x + 1 == width) {
                n_x = 0;
            } else {
                n_x += i;
            }

            std::size_t n_y = y;
            if (j < 0 && n_y == 0) {
                n_y = height - 1;
            } else if (j > 0 && n_y + 1 == height) {
                n_y = 0;
            } else {
                n_y += j;
            }

            if (getCell(n_x, n_y)) {
                if (n_y != y || n_x != x) {
                    counter++;
                }
            }
        }
    }
    return counter;
}

std::vector<std::vector<bool>> Universe::Field::getField() {
    return cells;
}

Universe::Universe() {
    setSize(0, 0);
    curIteration = 0;
}

void Universe::setAliveCells(std::vector<std::pair<std::size_t, std::size_t>>& active_cells) {
    for (auto coords : active_cells) {
        if (coords.first > widthOfField || coords.second > heightOfField) {
            throw std::invalid_argument("Wrong coordinates");
        }
        field.setCell(coords.first, coords.second);
    }
}

std::vector<std::pair<std::size_t, std::size_t>> Universe::getAliveCells() {
    std::vector<std::pair<std::size_t, std::size_t>> alive_cells;
    for (int y = 0; y < heightOfField; y++) {
        for (int x = 0; x < widthOfField; x++) {
            if (field.getCell(x, y)) {
                alive_cells.push_back({x, y});
            }
        }
    }
    return alive_cells;
}

std::vector<std::vector<bool>> Universe::getCurrentField() {
    return field.getField();
}

void Universe::nextIteration() {
    for (int y = 0; y < heightOfField; y++) {
        for (int x = 0; x < widthOfField; x++) {
            bool isAlive = field.getCell(x, y);
            int neighbours = field.getCellNeighbours(x, y);

            bool new_status;
            if (isAlive) {
                new_status = survivalValues[neighbours];
            } else {
                new_status = birthValues[neighbours];
            }
            buffer_field.setCell(x, y, new_status);
        }
    }

    field.swap(buffer_field);
    curIteration++;
}

void Universe::setName(std::string universe_name) {
    universeName = universe_name;
}

std::string Universe::getName() {
    return universeName;
}

void Universe::setRules(std::array<bool, 9> birthArray, std::array<bool, 9> survivalArray) {
    birthValues = birthArray;
    survivalValues = survivalArray;
}

std::array<bool, 9> Universe::getSurvRules() {
    return survivalValues;
}

std::array<bool, 9> Universe::getBirthRules() {
    return birthValues;
}

std::size_t Universe::getWidth() {
    return widthOfField;
}

std::size_t Universe::getHeight() {
    return heightOfField;
}

std::size_t Universe::getIteration() {
    return curIteration;
}

void Universe::setSize(std::size_t width, std::size_t height) {
    widthOfField = width;
    heightOfField = height;

    field.setSize(widthOfField, heightOfField);
    buffer_field.setSize(widthOfField, heightOfField);
}

