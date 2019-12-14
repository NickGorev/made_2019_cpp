#pragma once

#include <iterator>

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
    public:
        Iterator() = default;
        Iterator(const Iterator&) = default;
        Iterator(Iterator&&) = default;
        Iterator(T* pointer) : pointer_(pointer) {}
        Iterator& operator=(Iterator &&) = default;
        Iterator& operator=(Iterator const &) = default;

        Iterator& operator++() {
            pointer_++; return *this;
        }

        Iterator operator++(int) {
            Iterator temp(pointer_);
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            pointer_--; return *this;
        }

        Iterator operator--(int) {
            Iterator temp(pointer_);
            --(*this);
            return temp;
        }

        Iterator operator+(const std::ptrdiff_t& n) {
            return Iterator(pointer_ + n); }

        template<class U>
        friend Iterator<U> operator+(const std::ptrdiff_t& n,
                const Iterator<U>& a);

        Iterator operator-(const std::ptrdiff_t& n) {
            return Iterator(pointer_ - n); }

        std::ptrdiff_t operator-(const Iterator& other) {
            return pointer_ - other.pointer_; }


        Iterator& operator+=(const std::ptrdiff_t& n) {
            pointer_ += n;
            return *this;
        }

        Iterator& operator-=(const std::ptrdiff_t& n) {
            pointer_ -= n;
            return *this;
        }


        bool operator==(Iterator other) const {
            return pointer_ == other.pointer_;
        }

        bool operator!=(Iterator other) const {
            return !(*this == other);
        }

        bool operator<(Iterator other) const {
            return pointer_ < other.pointer_;
        }

        bool operator>(Iterator other) const {
            return pointer_ > other.pointer_;
        }

        bool operator<=(Iterator other) const {
            return pointer_ <= other.pointer_;
        }

        bool operator>=(Iterator other) const {
            return pointer_ >= other.pointer_;
        }


        T& operator*() {
            return *pointer_;
        }

        T* operator->() {
            return &*pointer_;
        }

        const T& operator*() const {
            return *pointer_;
        }

        const T* operator->() const {
            return &*pointer_;
        }

    private:
        T* pointer_;
};

template<class U>
Iterator<U> operator+(const std::ptrdiff_t& n, const Iterator<U>& a) {
    return Iterator<U>(a.pointer_ + n);
}
