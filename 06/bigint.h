#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>

enum OpSgn { PLUS, MINUS };

class BigInt {
    public:
        BigInt() = default;
        BigInt(const BigInt& n);
        BigInt(BigInt&& n);
        BigInt(long long int n);

        // деструктор
        ~BigInt() { delete[] data_; }

        // оператор присваивания
        BigInt & operator = (const BigInt & n);
        BigInt & operator = (BigInt && s);

        // оператор вывода в поток
        friend std::ostream& operator<< (std::ostream &out, const BigInt &n);

        // операторы сравнения
        bool operator <(const BigInt &other) const;
        bool operator >(const BigInt &other) const;
        bool operator ==(const BigInt &other) const;
        bool operator !=(const BigInt &other) const;
        bool operator >=(const BigInt &other) const;
        bool operator <=(const BigInt &other) const;

        // унарный минус, перегружен для lvalue и rvalue
        BigInt operator-() const &;
        BigInt operator-() &&;

        // операторы сложения и вычитания
        friend BigInt operator+(const BigInt & a, const BigInt & b);
        friend BigInt operator-(const BigInt & a, const BigInt & b);

    private:
        // data_ - массив десятичных цифр:
        // data_[0] содержит единицы,
        // data_[1] содержит десятки и т. д.
        char* data_ = nullptr;

        // size_ количество цифр в числе
        size_t size_ = 0;

        // neg_signum - отрицательный знак числа:
        // false - число положительное
        // true - число отрицательное
        bool neg_signum = false;

        // вспомогательная функция для сравнения модулей чисел
        bool abs_lower(const BigInt & other) const;

        // вспомогательная функция для сложения/вычитания модулей чисел
        BigInt abs_add_sub(const BigInt & other, OpSgn sign) const;
};

#endif /* BIGINT_H_ */
