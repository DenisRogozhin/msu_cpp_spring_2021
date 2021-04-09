#pragma once

#include <iostream>
#include <cassert> 

class ProxyRow  {
    public:
        ProxyRow(int * row , size_t m);
        int & operator[](size_t j);
    private:
        int *data;
 	size_t cols;
};

class Matrix {
    public:
        int get_rows() const;
        int get_cols() const;
        Matrix (size_t n=1, size_t m=1); 
        ~Matrix();
        Matrix & operator=(const Matrix & B);
        Matrix & operator *=(int x) ;
        bool operator ==(const Matrix &B) const ;
        bool operator !=(const Matrix &B) const;
        Matrix operator +(const Matrix &B) const ;
        ProxyRow operator [](size_t i) ;
        friend std::ostream & operator <<(std::ostream &out, const Matrix & A);
    private:
        size_t rows;
        size_t cols;
        int **matr;  
};

