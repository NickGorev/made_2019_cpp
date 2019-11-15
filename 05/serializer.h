#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <type_traits>
#include <ostream>
#include "errors.h"

class Serializer {
        static constexpr char Separator = ' ';
    public:
        explicit Serializer(std::ostream& out)
            : out_(out) {}

        template<class T>
        Error save(T& object) {
            return object.serialize(*this);
        }

        template<class ... ArgsT>
        Error operator()(ArgsT&& ... args) {
            return process(std::forward<ArgsT>(args)...);
        }

    private:
        std::ostream& out_;

        template<class T>
        Error process(T&& val) {
            output(val);
            return out_ ? Error::NoError : Error::ErrorSerialize;
        }

        template<class T, class ... Args>
        Error process(T&& val, Args&&... args) {
            output(val);
            out_ << Separator;
            return process(std::forward<Args>(args)...);
        }

        void output(bool& val) {
            out_ << (val ? "true" : "false");
        }

        void output(uint64_t& val) {
            out_ << val;
        }
};

#endif /* SERIALIZER_H_ */
