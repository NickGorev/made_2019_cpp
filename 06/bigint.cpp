#include "bigint.h"

// Копирующий конструктор
BigInt::BigInt(const BigInt& n) {
        size_ = n.size_;
        data_ = new char(size_);
        std::copy(n.data_, n.data_ + size_, data_);
        neg_signum = n.neg_signum;
}

// Конструктор перемещения
BigInt::BigInt(BigInt && n) {
    data_ = n.data_;
    n.data_ = nullptr;
    size_ = n.size_;
    n.size_ = 0;
    neg_signum = n.neg_signum;
}

// Конструктор из стандартного типа long long int
BigInt::BigInt(long long int n) {
    char buffer[20];
    int digits = 0;
    neg_signum = false;
    if (n < 0) {
        n = -n;
        neg_signum = true;
    }
    while (n > 0) {
        buffer[digits] = static_cast<char>(n % 10);
        n /= 10;
        digits++;
    }
    data_ = new char(digits);
    size_ = digits;
    std::copy(buffer, buffer + digits, data_);
}


// Копирующий оператор присваивания
BigInt & BigInt::operator = (const BigInt & copied) {
    if (this == &copied)
            return *this;

    char* ptr = new char[copied.size_];
    delete[] data_;
    data_ = ptr;
    size_ = copied.size_;
    std::copy(copied.data_, copied.data_ + size_, data_);
    neg_signum = copied.neg_signum;
    return *this;
}

// Оператор перемещения
BigInt & BigInt::operator = (BigInt && moved) {
    if (this == &moved)
            return *this;

    data_ = moved.data_;
    moved.data_ = nullptr;
    size_ = moved.size_;
    moved.size_ = 0;
    neg_signum = moved.neg_signum;
    return *this;
}


// Оператор вывода в поток
std::ostream& operator<< (std::ostream &out, const BigInt &n) {
    if (n.size_ == 0) {
        out << '0';
        return out;
    }
    if (n.neg_signum) {
        out << '-';
    }
    for (int i = n.size_ - 1; i >= 0; --i) {
        out << static_cast<char>(n.data_[i] + '0');
    }
    return out;
}


// вспомогательная функция для сравнения абсолютных значений
// abs(*this) < abs(other)
bool BigInt::abs_lower(const BigInt & other) const {
    if (size_ < other.size_) {
        return true;
    }
    if (size_ > other.size_) {
        return false;
    }
    if (size_ == 0) return false;
    for (int i = size_ - 1; i >= 0; --i) {
        int digit1 = static_cast<int>(data_[i]);
        int digit2 = static_cast<int>(other.data_[i]);
        if (digit1 < digit2) return true;
        if (digit1 > digit2) return false;
    }
    return false;
}

// Операторы сравнения
bool BigInt::operator <(const BigInt &other) const {
    if(neg_signum && !other.neg_signum) return true;
    if(!neg_signum && other.neg_signum) return false;
    if(!neg_signum && !other.neg_signum) return abs_lower(other);
    if(neg_signum && other.neg_signum) return other.abs_lower(*this);
    return false;
}

bool BigInt::operator >(const BigInt &other) const {
    return other < *this;
}

bool BigInt::operator ==(const BigInt &other) const {
    if (this->neg_signum != other.neg_signum) return false;
    if (this->size_ != other.size_) return false;
    for(size_t i = 0; i < size_; i++) {
        if (data_[i] != other.data_[i]) return false;
    }
    return true;
}

bool BigInt::operator !=(const BigInt &other) const {
    return !(*this == other);
}

bool BigInt::operator >=(const BigInt &other) const {
    return !(*this < other);
}

bool BigInt::operator <=(const BigInt &other) const {
    return !(*this > other);
}


// унарный минус для lvalue (создает копию с изменением знака)
BigInt BigInt::operator-() const & {
    BigInt tmp(*this);
    tmp.neg_signum = !this->neg_signum;
    return tmp;
}

// унарный минус для rvalue (только меняет знак, цифры не копируются)
BigInt BigInt::operator-() && {
    neg_signum = !neg_signum;
    return *this;
}


// Вспомогательная функция для сложение/вычитание модулей двух чисел
// sign == PLUS:  abs(*this) + abs(other)
// sign == MINUS: abs(*this) - abs(other), при условии abs(*this) > abs(other)
BigInt BigInt::abs_add_sub(const BigInt & other, OpSgn sign) const {
    size_t buffer_size = std::max(size_, other.size_) + 1;
    char* buffer = new char(buffer_size);
    int carry = 0;
    for(size_t i = 0; i < buffer_size; i++) {
        int digit1 = (i < size_) ? data_[i] : 0;
        int digit2 = (i < other.size_) ? other.data_[i] : 0;
        if (sign == PLUS) {
            int rez = digit1 + digit2 + carry;
            buffer[i] = static_cast<char>(rez % 10);
            carry = rez / 10;
        } else {
            int rez = digit1 - digit2 + carry;
            carry = 0;
            if (rez < 0) {
                rez += 10;
                carry = -1;
            }
            buffer[i] = static_cast<char>(rez);
        }
    }

    size_t digits = buffer_size;
    for(; digits > 0; --digits) {
        if (buffer[digits - 1] != 0) break;
    }

    BigInt tmp;
    tmp.size_ = digits;
    tmp.data_ = new char(digits);
    std::copy(buffer, buffer + digits, tmp.data_);

    delete[] buffer;

    return tmp;
}

// Оператор сложения
BigInt operator+(const BigInt & a, const BigInt & b) {
    // оба операнда отрицательные
    if (a.neg_signum && b.neg_signum) {
        BigInt tmp(a.abs_add_sub(b, PLUS));
        tmp.neg_signum = true;
        return tmp;
    }

    // первый отрицательный, второй - положительный
    if (a.neg_signum && !b.neg_signum) {
        if(a.abs_lower(b)) {
            return b.abs_add_sub(a, MINUS);
        } else {
            BigInt tmp(a.abs_add_sub(b, MINUS));
            tmp.neg_signum = true;
            return tmp;
        }

    }

    // первый положительный, второй - отрицательный
    if (!a.neg_signum && b.neg_signum) {
        if(a.abs_lower(b)) {
            BigInt tmp(b.abs_add_sub(a, MINUS));
            tmp.neg_signum = true;
            return tmp;
        } else {
            return a.abs_add_sub(b, MINUS);
        }
    }

    // оба операнда положительные
    return a.abs_add_sub(b, PLUS);
}

// Оператор вычитания
BigInt operator-(const BigInt & a, const BigInt & b) {
    // оба операнда положительные
    if (!a.neg_signum && !b.neg_signum) {
        if(a.abs_lower(b)) {
            BigInt tmp(b.abs_add_sub(a, MINUS));
            tmp.neg_signum = true;
            return tmp;
        } else {
            return a.abs_add_sub(b, MINUS);
        }
    }

    // оба операнда отрицательные
    if (a.neg_signum && b.neg_signum) {
        if(a.abs_lower(b)) {
            return b.abs_add_sub(a, MINUS);
        } else {
            BigInt tmp(a.abs_add_sub(b, MINUS));
            tmp.neg_signum = true;
            return tmp;
        }
    }

    // первый отрицательный, второй - положительный
    if (a.neg_signum && !b.neg_signum) {
        BigInt tmp(a.abs_add_sub(b, PLUS));
        tmp.neg_signum = true;
        return tmp;
    }

    // первый положительный, второй - отрицательный
    return a.abs_add_sub(b, PLUS);
}




