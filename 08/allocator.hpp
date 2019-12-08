#pragma once

#include <cstddef>
#include <limits>

template <class T>
class Allocator
{
    public:
        using value_type = T;
        using pointer = T*;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;

        pointer allocate(size_type count){
            return static_cast<pointer>(
                    operator new[] (count * sizeof(value_type)));
        }

        void deallocate(pointer ptr, size_type count) {
            operator delete[] (ptr);
        }

        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }
};
