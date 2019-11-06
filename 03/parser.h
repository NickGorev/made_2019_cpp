#ifndef PARSER_H_
#define PARSER_H_

#include <functional>

class Parser {
    public:
        using Callback = std::function<void (const std::string&)>;
        using NumberCallback = std::function<void (int)>;
        Parser(const Callback& beforeCallback = nullptr,
               const Callback& afterCallback = nullptr,
               const Callback& stringCallback = nullptr,
               const NumberCallback& numberCallback = nullptr)
                : beforeCallback(beforeCallback)
                , afterCallback(afterCallback)
                , stringCallback(stringCallback)
                , numberCallback(numberCallback) {}

        void setBeforeCallback(Callback beforeCallback) {
            this->beforeCallback = beforeCallback;
        }
        void setAfterCallback(Callback afterCallback) {
            this->afterCallback = afterCallback;
        }
        void setStringCallback(Callback stringCallback) {
            this->stringCallback = stringCallback;
        }
        void setNumberCallback(NumberCallback numberCallback) {
            this->numberCallback = numberCallback;
        }

        void parse(const std::string&);

    private:
        Callback beforeCallback;
        Callback afterCallback;
        Callback stringCallback;
        NumberCallback numberCallback;
};

#endif /* PARSER_H_ */

