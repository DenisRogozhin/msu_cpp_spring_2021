#include "allocator.h"


void ok_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr1 = a.alloc(20);
    char* ptr2 = a.alloc(10);
    assert((ptr1 != nullptr) && (ptr2 != nullptr));
}

void big_alloc_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr1 = a.alloc(20);
    char* ptr2 = a.alloc(11);
    assert((ptr1 != nullptr) && (ptr2 == nullptr));
}


void reset_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr1 = a.alloc(20);
    a.reset();
    char* ptr2 = a.alloc(25);
    assert(ptr2 != nullptr) ;
}

void negative_alloc_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr = a.alloc(-1);
    assert(ptr == nullptr) ;
}


void double_makeallocator_test() {
    Allocator a;
    a.makeAllocator(30);
    char* ptr1 = a.alloc(25);
    a.makeAllocator(40);
    char* ptr2 = a.alloc(35);
    assert(ptr2 != nullptr) ;
}


void alloc_before_makeallocator() {
    Allocator a;
    char* ptr = a.alloc(25);
    a.makeAllocator(5);
    assert(ptr == nullptr);
}


int main() {
    ok_test();
    big_alloc_test();
    reset_test();
    negative_alloc_test();
    double_makeallocator_test();
    alloc_before_makeallocator();
    return 0;
}

