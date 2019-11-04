#ifndef PARSER_H_
#define PARSER_H_

#include <functional>

class Parser {
    public:
        /* колбек-обработчик перед началом парсинга beforeCallback
         * должен иметь возможность модифицировать строку, поэтому
         * в него передается ссылка, в остальные колбеки передается
         * значение
         */
        using mutatingCallback = std::function<void (std::string&)>;
        using Callback = std::function<void (std::string)>;
        Parser(mutatingCallback beforeCallback = nullptr,
                Callback afterCallback = nullptr,
                Callback stringCallback = nullptr,
                Callback numberCallback = nullptr)
                : beforeCallback(beforeCallback)
                , afterCallback(afterCallback)
                , stringCallback(stringCallback)
                , numberCallback(numberCallback) {}

        void setBeforeCallback(mutatingCallback beforeCallback) {
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

        void parse(std::string);

    private:
        mutatingCallback beforeCallback;
        Callback afterCallback;
        Callback stringCallback;
        Callback numberCallback;
};

#endif /* PARSER_H_ */
