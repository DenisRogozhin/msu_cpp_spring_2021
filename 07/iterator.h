#pragma once

#include <iostream>
#include <cassert> 
#include <sstream>

template<class T>
class iterator {
	T* data;
        uint32_t index;
    public:

        iterator(T* ptr, uint32_t start_index) {
	    data = ptr;
	    index = start_index;
        }

        iterator<T> operator--() {
    	    --index; 
    	    return *this;
	}


	iterator<T> operator++() {
    	    ++index; 
    	    return *this;
        }


	T& operator*() const {
    	    return data[index];
	}


	bool operator==(const iterator<T>& other) {
    	    return (data == other.data) && (index == other.index);
	}


	bool operator!=(const iterator<T>& other) {
    	    return (data != other.data) || (index != other.index);
	}

};


template<class T>
class reverse_iterator {
	T* data;
        uint32_t index;
    public:

        reverse_iterator(T* ptr, uint32_t start_index) {
	    data = ptr;
	    index = start_index;
        }


        reverse_iterator<T> operator--() {
    	    ++index; 
    	    return *this;
	}


	reverse_iterator<T> operator++() {
    	    --index; 
    	    return *this;
        }


	T& operator*() const {
    	    return data[index];
	}


	bool operator==(const reverse_iterator<T>& other) {
    	    return (data == other.data) && (index == other.index);
	}


	bool operator!=(const reverse_iterator<T>& other) {
    	    return (data != other.data) || (index != other.index);
	}

};
