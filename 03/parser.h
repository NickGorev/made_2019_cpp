#ifndef PARSER_H_
#define PARSER_H_

#include <functional>

class Parser {
    public:
        using Callback = std::function<void (const std::string&)>;
        Parser(Callback beforeCallback = nullptr,
               Callback afterCallback = nullptr,
               Callback stringCallback = nullptr,
               Callback numberCallback = nullptr)
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
        void setNumberCallback(Callback numberCallback) {
            this->numberCallback = numberCallback;
        }

        void parse(const std::string&);

    private:
        Callback beforeCallback;
        Callback afterCallback;
        Callback stringCallback;
        Callback numberCallback;
};

#endif /* PARSER_H_ */

