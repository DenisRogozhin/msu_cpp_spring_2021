#include "matrix.h"

void matrix_create_test() {
    Matrix A(3,2);
    assert((A.get_rows() == 3) && (A.get_cols() == 2));
}

void matrix_sum_test() {
    Matrix A(3,2);
    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = 2;
    A[1][1] = 3;
    A[2][0] = 4;
    A[2][1] = 5;
    Matrix B(3,2);
    B[0][0] = 5;
    B[0][1] = 4;
    B[1][0] = 3;
    B[1][1] = 2;
    B[2][0] = 1;
    B[2][1] = 0;
    Matrix C = B + A;
    assert((C[0][0] == 5) && (C[0][1] == 5) && (C[1][0] == 5) && (C[1][1] == 5) && (C[2][0] == 5) && (C[2][1] == 5));
}

void matrix_mul_test() {
    Matrix A(3,2);
    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = 2;
    A[1][1] = 3;
    A[2][0] = 4;
    A[2][1] = 5;
    A *= 5;
    assert((A[0][0] == 0) && (A[0][1] == 5) && (A[1][0] == 10) && (A[1][1] == 15) && (A[2][0] == 20) && (A[2][1] == 25));
}


void matrix_print_test() {
    Matrix A(3,2);
    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = 2;
    A[1][1] = 3;
    A[2][0] = 4;
    A[2][1] = 5;
    std::cout<<A<<std::endl;
}

void matrix_compare_test() {
    Matrix A(2,2);
    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = 2;
    A[1][1] = 3;
    Matrix B(2,2);
    B[0][0] = 0;
    B[0][1] = 1;
    B[1][0] = 2;
    B[1][1] = 3;
    assert((A == B) && !( A != B));
    B[1][1] = 5;
    assert((A != B) && !( A == B)); 
}

void matrix_get_elem_test() {
    Matrix A(5,2);
    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = 2;
    A[1][1] = 3;
    assert((A[4][0] == 0) && ( A[0][1] == 1)); 
}


void matrix_compare_with_different_size_test() {
    Matrix A(1,2);
    A[0][0] = 0;
    A[0][1] = 1;
    Matrix B(2,1);
    B[0][0] = 0;
    B[1][0] = 2;
    assert((A != B) && !( A == B));
}

void matrix_wrong_index_test() {
    bool t = false;
    try {
        Matrix A(0,2);
    }
    catch (std::invalid_argument &) {
        t = true;
        std::cout<<"exception: invalid_argument"<<std::endl;
    }
    assert(t); 
}

void matrix_sum_with_wrong_index_test() {
    bool t = false;
    Matrix A(1,2);
    Matrix B(2,1);
    try {
        Matrix C = A + B ;
    }
    catch (std::invalid_argument &) {
        t = true;
        std::cout<<"exception: invalid_argument"<<std::endl;
    }
    assert(t); 
}

void matrix_index_out_of_range_test() {
    bool t = false;
    Matrix A(1,2);
    try {
        int y = A[2][3];
    }
    catch (std::out_of_range &) {
        t = true;
        std::cout<<"exception: index_out_of_range_test"<<std::endl;
    }
    assert(t); 
}

int main() {
    matrix_create_test();
    matrix_sum_test();
    matrix_mul_test();
    matrix_print_test();
    matrix_compare_test();
    matrix_get_elem_test();
    matrix_wrong_index_test();
    matrix_compare_with_different_size_test();
    matrix_sum_with_wrong_index_test();
    matrix_index_out_of_range_test();
    return 0;
}





