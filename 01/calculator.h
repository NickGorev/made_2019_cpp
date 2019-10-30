#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#include <string>

class Calculator {
    public:
        explicit Calculator(const char* input) :
            expression(input), input(expression.begin()) {}
        int getNumber();
        char getOperator();
        int getMonomial();
        int calculate();

        std::string expression;
        std::string::iterator input;
};

#endif /* CALCULATOR_H_ */
