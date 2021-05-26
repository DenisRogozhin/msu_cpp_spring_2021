#include "vector.h"


void create_vector_test() {
    Vector<int> v;
    v.push_back(1);
    v.emplace_back(2, 3, 4);
    v.pop_back();
    v[1] = 5;
    assert(v.get_size() == 3);
    assert(v[0] == 1);
    assert(v[1] == 5);
    assert(v[2] == 3);
 }


void reserve_test() {
    Vector<int> v;
    v.emplace_back(1, 2, 3, 4);
    v.reserve(500);
    assert(v.get_size() == 4);
    assert(v.get_capacity() == 500);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(v[3] == 4);
 }

void copy_test() {
    Vector<int> v;
    v.emplace_back(1, 2, 3, 4);
    Vector e(v);
    assert(e.get_size() == 4);
    assert(v.get_size() == 4);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(v[3] == 4);
    assert(e[0] == 1);
    assert(e[1] == 2);
    assert(e[2] == 3);
    assert(e[3] == 4);
}

void move_test() {
    Vector<int> v;
    v.emplace_back(1, 2, 3, 4);
    Vector e(std::move(v));
    assert(e.get_size() == 4);
    assert(v.get_size() == 0);
    assert(e[0] == 1);
    assert(e[1] == 2);
    assert(e[2] == 3);
    assert(e[3] == 4);
}

void operator_pr1_test() {
    Vector<int> v;
    v.emplace_back(1, 2, 3, 4);
    Vector<int> e;
    e = v;
    assert(e.get_size() == 4);
    assert(v.get_size() == 4);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(v[3] == 4);
    assert(e[0] == 1);
    assert(e[1] == 2);
    assert(e[2] == 3);
    assert(e[3] == 4);
}

void operator_pr2_test() {
    Vector<int> v;
    v.emplace_back(1, 2, 3, 4);
    Vector<int> e;
    e = std::move(v);
    assert(e.get_size() == 4);
    assert(v.get_size() == 0);
    assert(e[0] == 1);
    assert(e[1] == 2);
    assert(e[2] == 3);
    assert(e[3] == 4);
}

void pop_from_empty_test() {
    Vector<int> v;
    assert(v.empty());
    v.pop_back();
}


void clear_test() {
    Vector<int> v;
    v.emplace_back(1, 2, 3, 4);
    v.clear();
    assert(v.get_size() == 0);
    bool t = false;
    try {
	int x = v[0];
    }
    catch(std::out_of_range & c) {
	t = true;
    }
    assert(t);
}

void out_of_range() {
    Vector<int> v;
    bool t1 = false;
    try {
	int x = v[0];
    }
    catch(std::out_of_range & c) {
	t1 = true;
    }
    assert(t1);
    bool t2 = false;
    try {
	v[0] = 5;
    }
    catch(std::out_of_range & c) {
	t2 = true;
    }
    assert(t2);
}

void resize_test() {
    Vector<int> e;
    e.emplace_back(1, 2, 3, 4);
    e.resize(2);
    assert(e.get_size() == 2);
    assert(e[0] == 1);
    assert(e[1] == 2);
    Vector<int> v;
    v.emplace_back(1, 2, 3, 4);
    v.resize(6);
    v[4] = 5;
    v[5] = 6;
    assert(v.get_size() == 6);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(v[3] == 4);
    assert(v[4] == 5);
    assert(v[5] == 6);
}

void iterator_test() {
    int a[4];
    Vector<int> e;
    e.emplace_back(1, 2, 3, 4);
    auto iter = e.begin();
    int i = 0;
    while (iter != e.end()) {
	a[i] = *iter;
        i++;
        ++iter;
    }
    assert(a[0] == 1);
    assert(a[1] == 2);
    assert(a[2] == 3);
    assert(a[3] == 4);
    auto iter1 = e.end();
    --iter1;
    i = 0;
    while (iter1 != e.begin()) {
	a[i] = *iter1;
        i++;
        --iter1;
    }
    a[i] = *iter1;
    assert(a[0] == 4);
    assert(a[1] == 3);
    assert(a[2] == 2);
    assert(a[3] == 1);

}

void reverse_iterator_test() {
    int a[4];
    Vector<int> e;
    e.emplace_back(1, 2, 3, 4);
    auto iter = e.rbegin();
    int i = 0;
    while (iter != e.rend()) {
	a[i] = *iter;
        i++;
        ++iter;
    }
    assert(a[0] == 4);
    assert(a[1] == 3);
    assert(a[2] == 2);
    assert(a[3] == 1);
    auto iter1 = e.rend();
    --iter1;
    i = 0;
    while (iter1 != e.rbegin()) {
	a[i] = *iter1;
        i++;
        --iter1;
    }
    a[i] = *iter1;
    assert(a[0] == 1);
    assert(a[1] == 2);
    assert(a[2] == 3);
    assert(a[3] == 4);

}


int main() {  
    create_vector_test();
    reserve_test();
    copy_test();
    move_test();
    operator_pr1_test();
    operator_pr2_test();
    pop_from_empty_test();
    clear_test();
    out_of_range();
    resize_test();
    iterator_test();
    reverse_iterator_test();
    return 0;
}





