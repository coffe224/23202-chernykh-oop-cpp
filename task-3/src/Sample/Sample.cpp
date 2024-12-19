#include "Sample.h"
#include <iostream>

Sample::Sample()
{
    is_empty = false;
    value = 0;
}

bool Sample::isEmpty() { return is_empty; }

void Sample::setEmpty() { is_empty = true; }

std::int16_t Sample::getValue()
{
    if (isEmpty()) {
        std::cerr << "Can't get value of empty sample\n";
        throw;
    }
    return value;
}

void Sample::setValue(std::int16_t new_value)
{
    if (isEmpty()) {
        std::cerr << "Can't set value of empty sample\n";
        throw;
    }
    value = new_value;
}
