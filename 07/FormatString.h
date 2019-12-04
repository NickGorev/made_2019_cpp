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

    std::vector<std::string> strs;
};

// Функция проверяет фигурные скобки
bool check_brackets(const std::string& format_string) {
    int balance = 0;
    for (const auto & c : format_string) {
        if (c == '{') {
            balance++;
        }
        if (c == '}') {
            balance--;
        }
        if (balance < 0 || balance > 1) return false;
    }
    return balance == 0;
}


// Функция преобразует номер в виде строки в число
size_t str2num(const std::string& number_string) {
    // Сначала проверяем что строка имеет вид:
    // пробел, пробел, ..., цифра, цифра, ..., пробел, пробел, ...
    size_t index = 0;
    while (std::isspace(number_string[index])) index++;
    while (std::isdigit(number_string[index])) index++;
    while (std::isspace(number_string[index])) index++;
    if (index != number_string.size()) {
        throw std::runtime_error("Error argument number");
    }

    // Преобразуем строку в число
    size_t arg_number = 0;
    try {
        arg_number = std::stoi(number_string);
    } catch (const std::exception& error) {
        throw std::runtime_error("Error argument number");
    }

    return arg_number;
}

// Функция форматирования
template<class ... Args>
std::string format(const std::string& format_string, Args&&... args) {
    if (!check_brackets(format_string)) {
        throw std::runtime_error("Error brackets");
    }

    args2strings args_strings(std::forward<Args>(args)...);

    std::string rez;
    std::string::size_type search_pos = 0;
    while(true) {
        std::string::size_type open_bracket_pos = format_string.find("{", search_pos);
        std::string::size_type close_bracket_pos = format_string.find("}", search_pos);

        rez += format_string.substr(search_pos, open_bracket_pos - search_pos);

        if ((open_bracket_pos == format_string.npos)) break;

        auto arg_number_string = format_string.substr(
                open_bracket_pos + 1, close_bracket_pos - open_bracket_pos - 1);
        size_t arg_number = str2num(arg_number_string);

        if (arg_number >= args_strings.strs.size()) {
            throw std::runtime_error("Error argument number");
        }

        rez += args_strings.strs[arg_number];

        search_pos = close_bracket_pos + 1;
    }

    return rez;
}

#endif /* FORMATSTRING_H_ */
