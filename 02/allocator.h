#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <cstdlib>

class LinearAllocator {
    public:
        LinearAllocator(size_t maxSize);
        ~LinearAllocator();
        char* alloc(size_t size);
        void reset();
    private:
        char* storage;
        char* storageEnd;
        char* head;
};

#endif /* ALLOCATOR_H_ */
