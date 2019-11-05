#include "parser.h"

void Parser::parse(const std::string& inputString) {
    if (beforeCallback) {
        beforeCallback(inputString);
    }

    auto inputIt = inputString.begin();
    while (inputIt != inputString.end() && std::isspace(*inputIt)) {
        ++inputIt;
    }

    std::string token;
    while (inputIt != inputString.end()) {
        token.clear();
        bool isNumberToken = true;
        char symbol = *inputIt;
        while (inputIt != inputString.end() && !std::isspace(symbol)) {
            if (!std::isdigit(symbol)) {
                isNumberToken = false;
            }
            token.push_back(symbol);
            symbol = *(++inputIt);
        }

        if (isNumberToken) {
            if (numberCallback) {
                numberCallback(token);
            }
        } else {
            if (stringCallback) {
                stringCallback(token);
            }
        }

        while (inputIt != inputString.end() && std::isspace(*inputIt)) {
            ++inputIt;
        }
    }

    if (afterCallback) {
        afterCallback(inputString);
    }
}

