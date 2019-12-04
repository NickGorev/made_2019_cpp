#ifndef FORMATSTRING_H_
#define FORMATSTRING_H_

#include <string>
#include <vector>
#include <sstream>

// Вспомогательная структура для преобразования
// списка аргументов неопределенного типа и размера
// в вектор строк
struct args2strings {
    template<class ... Args>
    args2strings(Args&&... args) {
        make_strings(std::forward<Args>(args)...);
    }

    void make_strings() {}

    template<class First, class ... Rest>
    void make_strings(First&& first, Rest&&... args) {
        std::stringstream ss;
        ss << first;
        strs.push_back(ss.str());

        make_strings(std::forward<Rest>(args)...);
    }

    const std::string& operator[](size_t index) const {
        if (index >= strs.size()) {
            throw std::runtime_error("Error argument number");
        }
        return strs[index];
    };

    std::vector<std::string> strs;
};

// Функция преобразует номер в виде строки в число
size_t str2num(const std::string& number_string) {
    size_t arg_number = 0;
    size_t pos = 0;
    try {
        arg_number = std::stoi(number_string, &pos);
    } catch (const std::exception& error) {
        throw std::runtime_error("Error argument number");
    }

    // Проверяем, что в строке после числа нет ничего лишнего
    while (std::isspace(number_string[pos])) pos++;
    if (pos != number_string.size()) {
        throw std::runtime_error("Error argument number");
    }

    return arg_number;
}

// Функция форматирования
template<class ... Args>
std::string format(const std::string& format_string, Args&&... args) {
    args2strings args_strings(std::forward<Args>(args)...);

    std::string rez;
    std::string arg_number_str;
    int balance_brackets = 0;
    for(const auto & c : format_string) {
        if (c == '{') {
            balance_brackets++;
            if (balance_brackets > 1) {
                throw std::runtime_error("Error brackets");
            }
            arg_number_str = "";
        } else if (c == '}') {
            balance_brackets--;
            if (balance_brackets < 0) {
                throw std::runtime_error("Error brackets");
            }
            rez += args_strings[str2num(arg_number_str)];
        } else {
            if (balance_brackets == 0) rez += c;
            if (balance_brackets == 1) arg_number_str += c;
        }
    }

    if (balance_brackets != 0) throw std::runtime_error("Error brackets");

    return rez;
}

#endif /* FORMATSTRING_H_ */
