#pragma once

#include <iostream>

class Allocator   {
    public:
        void makeAllocator(size_t maxSize);
        char* alloc(size_t size);
        void reset();
        Allocator() ;
        ~Allocator() ;
    private: 
        size_t free_size;
        size_t all_size; 
        char * offset;
        char *memory;   
};
