#pragma once

#include "iterator.h"
#include "allocator.h"
#include <utility>
#include <stdexcept>

template <class T>
class Vector {
        T * data;
	int size;
	int capacity;
	allocator<T> all;
       

    public:

	Vector<T>() {
	    data = nullptr;
	    size = 0;
	    capacity = 0;
	    all = allocator<T>();
	}


	Vector<T>(const Vector & other) {
	    size = other.size;
	    capacity = other.capacity;
	    data = all.allocate(size);
	    for (int i = 0; i < size ; i++)
	        all.construct(data + i , other.data[i]);
	}


	Vector<T>(Vector && other) {
	    capacity = other.capacity;
    	    size = other.size;
    	    all = other.all;
            data = other.data;
            other.capacity = 0;
            other.size = 0;
            other.all = allocator<T>();
            other.data = nullptr; 
	}



	Vector<T> & operator = (const Vector & other) {
	    if (&other == this)
		return *this;
	    size = other.size;
	    capacity = other.capacity;
	    if (data != nullptr)
		all.deallocate(data);
	    data = all.allocate(size);
	    for (int i = 0; i < size ; i++)
	        all.construct(data + i , other.data[i]);
	    return *this;
	}


	Vector<T> & operator = (Vector && other) {
	    if (&other == this)
		return *this;
	    if (data != nullptr)
		all.deallocate(data);
	    capacity = other.capacity;
    	    size = other.size;
    	    all = other.all;
            data = other.data;
            other.capacity = 0;
            other.size = 0;
            other.all = allocator<T>();
            other.data = nullptr; 
	    return *this;
	}


	~Vector<T>() {
    	    for (int i = 0; i < size; i++)
        	all.destroy(data + i);
    	    if (data != nullptr)
        	all.deallocate(data);
	}


	T& operator[] (uint32_t index) {
    	    if (index >= size)
        	throw std::out_of_range("ERROR: index must be less than size");
    	    return data[index];
	}


	const T& operator[] (uint32_t index) const {
    	    if (index >= size)
        	throw std::out_of_range("ERROR: index must be less than size");;
    	    return data[index];
	}


	void reserve(uint32_t new_capacity) {
            if (capacity < new_capacity) {
                T* buffer = all.allocate(new_capacity);
                for (int i = 0; i < size; i++) {
                    all.construct(buffer + i, std::move(data[i])); 
                    all.destroy(data + i);
                }
                all.deallocate(data); 
                capacity = new_capacity;
                data = buffer;
            }        
        }
  


	void push_back(const T& value) {
            if (size == capacity)
                reserve(capacity + 16);
            all.construct(data + size, value);
            size ++;
        }


        void push_back(T && value) {
            if (size == capacity)
                reserve(capacity + 16);
            all.construct(data + size, value);
            size ++;
        }



        void pop_back() {
            if (size > 0) {
                all.destroy(data + size);
                --size;
	    }
        }

	void emplace_back(T&& arg) {
    	     push_back(std::forward<T>(arg));
        }


        template < class... Args >
	void emplace_back(T&& arg, Args&&... args) {
    	    push_back(std::forward<T>(arg));
    	    emplace_back(std::forward<Args>(args)...);
        }


	bool empty() const {
    	    return size == 0;
	}


	uint32_t get_size() const {
    	    return size;
	}


	uint32_t get_capacity() const {
    	    return capacity;
	}


	void clear() {
    	    for (int i = size - 1; i >= 0; i--)
        	all.destroy(data + i );
    	    all.deallocate(data); 
            data = nullptr;
            size = 0;
        }


	void resize(uint32_t new_size) {
    	    if (new_size < size) {
        	for (int i = size - 1; i >= new_size ; i--)
            	    all.destroy(data + i);
    	    }
            else {
        	reserve(new_size);
                for (int i = size; i < new_size; i++)
            	    all.construct(data + i, T());
    	     }
    	     size = new_size;
	}

        

	iterator<T> begin() {
    	    return iterator<T>(data, 0);
	}


	iterator<T> end()  {
    	    return iterator<T>(data, size);
        }


	reverse_iterator<T> rbegin()  {
    	    return reverse_iterator<T>(data, size - 1);
        }


	reverse_iterator<T> rend()  {
    	    return reverse_iterator<T>(data, -1);
	}

};


