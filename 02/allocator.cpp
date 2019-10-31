#include "allocator.h"

LinearAllocator::LinearAllocator(size_t maxSize) {
    storage = (char*) malloc(maxSize);
    storageEnd = storage;
    if (storage != nullptr) {
        storageEnd += maxSize;
    }
    head = storage;
}

LinearAllocator::~LinearAllocator() {
    free(storage);
}

char* LinearAllocator::alloc(size_t size) {
    if(head + size <= storageEnd) {
        char* retValue = head;
        head += size;
        return retValue;
    } else {
        return nullptr;
    }
}

void LinearAllocator::reset() {
    head = storage;
}
