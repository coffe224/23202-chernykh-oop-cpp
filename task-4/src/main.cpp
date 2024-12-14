#include <iostream>

#include "TuplePrinter.h"

int main() {
    std::tuple<int, std::string, float> a = {3, "fkdlkf", 2.5};
    std::cout << a << "\n";
    return 0;
}