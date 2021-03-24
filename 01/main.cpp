#include "hw1.h"


void ok_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr1 = a.alloc(20);
    char* ptr2 = a.alloc(10);
    if ((ptr1 != nullptr) && (ptr2 != nullptr))
        std::cout<<"OK_test passed"<<std::endl;
    else
        std::cout<<"OK_test failed"<<std::endl;
}

void big_alloc_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr1 = a.alloc(20);
    char* ptr2 = a.alloc(11);
    if ((ptr1 != nullptr) && (ptr2 == nullptr))
       std::cout<<"BIG_alloc_test passed"<<std::endl;
    else
        std::cout<<"BIG_alloc_test failed"<<std::endl;
}


void reset_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr1 = a.alloc(20);
    a.reset();
    char* ptr2 = a.alloc(25);
    if (ptr2 != nullptr) 
       std::cout<<"reset_test passed"<<std::endl;
    else
        std::cout<<"reset_test failed"<<std::endl;
}

void negative_alloc_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr = a.alloc(-1);
    if (ptr == nullptr) 
       std::cout<<"negative_alloc_test passed"<<std::endl;
    else
        std::cout<<"negative_alloc_test failed"<<std::endl;
}


void double_makeallocator_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr1 = a.alloc(25);
    a.makeAllocator(40);
    char* ptr2 = a.alloc(35);
    if (ptr2 != nullptr) 
       std::cout<<"double_makeallocator_test passed"<<std::endl;
    else
        std::cout<<"double_makeallocator_test failed"<<std::endl;
}

void negative_makeallocator_test() {
    Allocator a;
    a.makeAllocator(-1);
    char* ptr = a.alloc(25);
    if (ptr == nullptr) 
        std::cout<<"negative_makeallocator_test passed"<<std::endl;
    else
        std::cout<<"negative_makeallocator_test failed"<<std::endl; 
}

int main() {
    ok_test();
    big_alloc_test();
    reset_test();
    negative_alloc_test();
    double_makeallocator_test();
    negative_makeallocator_test();
    return 0;
}

