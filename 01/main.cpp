#include <iostream>
#include "calculator.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << "error: no arithmetic expression" << std::endl;
        return 1;
    }

    try {
        int result = Calculator(argv[1]).calculate();
        std::cout << result << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

