#ifndef DESERIALIZER_H_
#define DESERIALIZER_H_

#include <type_traits>
#include "errors.h"

class Deserializer {
    public:
        explicit Deserializer(std::istream& in)
            : in_(in) {}

        template<class T>
        Error load(T& object) {
            return object.serialize(*this);
        }

        template<class ... ArgsT>
        Error operator()(ArgsT&& ... args) {
            return process(args...);
        }

    private:
        std::istream& in_;

        template<class T>
        Error process(T&& val) {
            Error err = load(val);
            if (!in_ || err == Error::ErrorDeserialize) {
                return Error::ErrorDeserialize;
            }
            return Error::NoError;
        }

        template<class T, class ... Args>
        Error process(T&& val, Args&&... args) {
            Error err = load(val);
            if (!in_ || err == Error::ErrorDeserialize) {
                return Error::ErrorDeserialize;
            }
            return process(std::forward<Args>(args)...);
        }

        Error load(bool& value) {
            std::string text;
            in_ >> text;

            if (text == "true")
                value = true;
            else if (text == "false")
                value = false;
            else
                return Error::ErrorDeserialize;

            return Error::NoError;
        }

        Error load(uint64_t& value) {
            in_ >> value;
            return Error::NoError;
        }
};

#endif /* DESERIALIZER_H_ */
