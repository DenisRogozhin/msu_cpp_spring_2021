#pragma once

#include <iostream>
#include <cassert> 
#include <sstream>

#define MAX_PTRS 16 

template <class T>
class allocator {

        T* ptrs[MAX_PTRS];
        uint32_t ptrs_count;

    public:

        allocator() {
            ptrs_count = 0;
	    for (int i = 0 ; i < MAX_PTRS; i++) 
		ptrs[i] = nullptr;
	}


        allocator(const allocator<T>& other) {
	    for (int i = 0 ; i < MAX_PTRS; i++) 
		if (ptrs[i] != nullptr)
		    delete []ptrs[i];
	    ptrs_count = other.ptrs_count;
	    for (int i = 0 ; i < MAX_PTRS; i++) 
		ptrs[i] = other.ptrs[i];       
	}


        ~allocator() {
	    for (int i = 0 ; i < MAX_PTRS; i++) 
		if (ptrs[i] != nullptr) {
		    delete []ptrs[i];
		    ptrs[i] = nullptr;
		}
	}
    

        T* allocate(uint32_t size) {
	    if (ptrs_count == MAX_PTRS)
		throw std::bad_alloc();
	    int i = 0;
	    while (ptrs[i] != nullptr)
		i++;
	    ptrs[i] = new T[size];
	    ptrs_count++;
	    return ptrs[i];

	}


        void deallocate(T* ptr) {
	    for (int i = 0 ; i < MAX_PTRS; i++) 
		if (ptrs[i] == ptr) {
		    delete [] ptrs[i];
		    ptrs[i] = nullptr;
		    ptrs_count --;
		    break;
                }
	}


	void construct(T* ptr, const T& value) {
    	    new((void*)ptr) T(value);
	}


	void destroy(T* ptr) {
    	    ((T*)ptr)->~T();
	}
};


