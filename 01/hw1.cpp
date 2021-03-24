#include "hw1.h"

void Allocator::makeAllocator(size_t maxSize)  {
    if (memory != nullptr)
        delete [] memory;
    all_size = maxSize; 
    free_size = maxSize;
    try  {
        memory = new char [maxSize];
        offset = memory; 
    }
    catch(std::bad_alloc) {
        free_size = 0;
        all_size = 0;
        offset = nullptr;
        memory = nullptr;
    }        
    return;
}


char* Allocator::alloc(size_t size) {
    if ((size > free_size) || (size < 0)) 
        return nullptr;
    free_size = free_size - size;
    char * res = offset;
    offset += size * sizeof(char);
    return res;
}

void Allocator::reset()  {
    free_size = all_size;
    offset = memory;      
}


Allocator::Allocator()  {
    free_size = 0;
    all_size = 0;
    offset = nullptr;
    memory = nullptr;
}

Allocator::~Allocator()  {
    if (memory != nullptr )
        delete [] memory;
}





