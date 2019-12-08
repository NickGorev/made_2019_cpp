#pragma once
#include "allocator.hpp"
#include "iterator.hpp"

template<class T, class Alloc = Allocator<T>>
class Vector {
    public:
        using size_type = size_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = const T&;
        using allocator_type = Alloc;

        using iterator = Iterator<T>;
        using reverse_iterator = std::reverse_iterator<iterator>;

        Vector()
            : size_(0)
            , capacity_(8)
            , data_(alloc_.allocate(capacity_)) {}

        explicit Vector(size_type count)
            : size_(count)
            , capacity_(count)
            , data_(alloc_.allocate(count)) {
            for (size_type i = 0; i < size_; i++) {
              new (data_ + i) value_type;
            }
        }

        Vector(size_type count, const value_type& defaultValue)
            : size_(count)
            , capacity_(count)
            , data_(alloc_.allocate(count)) {
            for (size_type i = 0; i < size_; i++) {
              new (data_ + i) value_type(defaultValue);
            }
        }

        Vector(std::initializer_list<value_type> init)
            : size_(init.size())
            , capacity_(size_)
            , data_(alloc_.allocate(size_)) {
            size_t i = 0;
            auto current = init.begin();
            const auto end = init.end();
            while (current != end) {
                data_[i++] = *current++;
            }
        }

        ~Vector() {
            for (size_type i = 0; i < size_; i++) {
              data_[i].~value_type();
            }
            alloc_.deallocate(data_, capacity_);
        }

        iterator begin() noexcept {
            return iterator(data_);
        }
        reverse_iterator rbegin() noexcept {
            return reverse_iterator(this->end());
        }

        iterator end() noexcept {
            return iterator(data_ + size_);
        }
        reverse_iterator rend() noexcept {
            return reverse_iterator(this->begin());
        }

        void push_back(value_type&& value) {
            if (size_ == capacity_) reserve(capacity_ * 2);
            std::swap(value, data_[size_++]);
        }
        void push_back(const value_type& value) {
            if (size_ == capacity_) reserve(capacity_ * 2);
            new (data_ + size_) value_type(value);
            size_++;
        }

        void pop_back() {
            data_[--size_].~value_type();
        }

        bool empty() const noexcept {
            return size_ == 0;
        }

        size_type size() const noexcept {
            return size_;
        }

        void reserve(size_type count) {
            if (capacity_ < count) {
                pointer newData = alloc_.allocate(count);
                for (size_type i = 0; i < size_; i++) {
                    newData[i] = data_[i];
                }
                capacity_ = count;
                alloc_.deallocate(data_, capacity_);
                data_ = newData;
                return;
            }
        }

        size_type capacity() const noexcept {
            return capacity_;
        }

        void resize(size_type newSize) {
            if (newSize == size_) return;

            if (newSize < size_) {
                for (size_t i = newSize; i < size_; ++i) {
                    data_[i].~value_type();
                }
                size_ = newSize;
                return;
            }

            if (newSize > capacity_) {
                reserve(newSize);
            }

            for (size_t i = size_; i < newSize; ++i) {
                new (data_ + i) value_type();
            }
            size_ = newSize;
        }

        void resize(size_type newSize, const value_type& defaultValue) {
            size_type oldSize = size_;
            resize(newSize);
            if (oldSize < newSize) {
                for (size_t i = oldSize; i < newSize; ++i) {
                    data_[i] = defaultValue;
                }
            }
        }

        void clear() {
            for (size_t i = 0; i < size_; ++i) {
                data_[i].~value_type();
            }
            size_ = 0;
        }

        reference operator[](size_type pos) {
            return data_[pos];
        }

        const_reference operator[](size_type pos) const {
            return data_[pos];
        }

    private:
        Alloc alloc_;

        size_type size_;
        size_type capacity_;
        pointer data_;

};

