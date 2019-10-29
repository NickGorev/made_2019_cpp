#include <cctype>
#include <string>
#include <stdexcept>
#include "calculator.h"

int Calculator::getNumber() {
    while (std::isspace(*input))
        ++input;

    // унарный минус
    int signum = 1;
    if (*input == '-') {
        signum = -1;
        input++;
        while (std::isspace(*input))
            ++input;
    }

    // набор цифр
    if (std::isdigit(*input)) {
        std::string snumber;
        while (std::isdigit(*input))
            snumber.push_back(*input++);
        int nunber = 0;
        try {
            nunber = std::stoi(snumber);
        } catch (std::out_of_range&) {
            throw std::runtime_error("Number is too large");
        }
        return signum * nunber;
    } else {
        throw std::runtime_error("Incorrect expression");
    }

    return 0;
}

char Calculator::getOperator() {
    while (std::isspace(*input))
        ++input;

    char tokens[] = { '+', '-', '*', '/' };
    for (char t : tokens) {
        if (t == *input) {
            input++;
            return t;
        }
    }
    if (*input) {
        throw std::runtime_error("Incorrect expression");
    }
    return ' ';
}

int Calculator::getMonomial() {
    int res = getNumber();
    while (std::isspace(*input))
        ++input;

    while (*input) {
        char token = getOperator();
        if (token == '*') {
            res *= getNumber();
        }
        if (token == '/') {
            int divider = getNumber();
            if (divider != 0) {
                res /= divider;
            } else {
                throw std::runtime_error("Division by zero");
            }
        }
        if (token == '+' or token == '-') {
            input--;
            break;
        }
    }

    return res;
}

int Calculator::calculate() {
    int res = getMonomial();
    while (std::isspace(*input))
        ++input;

    while (*input) {
        char token = getOperator();
        if (token == '+') {
            res += getMonomial();
        }
        if (token == '-') {
            res -= getMonomial();
        }
    }

    return res;
}

