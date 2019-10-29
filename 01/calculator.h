#ifndef CALCULATOR_H_
#define CALCULATOR_H_

class Calculator {
    public:
        explicit Calculator(const char* input) :
                input(input) {
        }
        int getNumber();
        char getOperator();
        int getMonomial();
        int calculate();

        const char* input;
};

#endif /* CALCULATOR_H_ */
