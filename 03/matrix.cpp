#include "matrix.h"

int Matrix::get_rows() const {
    return rows;
}

int Matrix::get_cols() const {
    return cols;
}


Matrix::Matrix (size_t n, size_t m) {
    if ((n < 1) || (m < 1))
        throw std::invalid_argument("");
    rows = n;
    cols = m;
    matr = new int *[n];
    for (int i = 0; i < n ; i++)
        matr[i]=new int[m];
    for (int i = 0; i < n ; i++)
        for (int j = 0; j < m ; j++)
            matr[i][j] = 0;  
}


Matrix::~Matrix() {
    for (int i = 0 ; i < rows ; i++)
        delete []matr[i]; 
    delete []matr; 
}


Matrix & Matrix::operator=(const Matrix & B) {
    if (this == &B)
        return *this;  
    for (int i = 0 ; i < rows ; i++)
        delete []matr[i]; 
    delete []matr; 
    rows = B.rows; 
    cols = B.cols;
    matr = new int*[rows];
    for (int i = 0; i < rows ; i++) 
        matr[rows] = new int[cols];
    for (int i = 0 ; i < rows ; i++)
        for (int j = 0 ; j < cols ; j++)
            matr[i][j] = B.matr[i][j]; 
    return *this; 
} 


Matrix & Matrix::operator *=(int x) {
    for (int i = 0; i < rows ; i++)
        for (int j = 0 ; j < cols; j++)
            matr[i][j] *= x;
    return *this;
}


Matrix Matrix::operator +(const Matrix &B) const {
    if ((rows != B.rows) || (cols != B.cols)) 
        throw std::invalid_argument("");
    Matrix A(rows,cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols ; j++)
            A.matr[i][j] = matr[i][j] + B.matr[i][j];
    return A;
}


bool Matrix::operator ==(const Matrix &B) const { 
    if ((rows!=B.rows)||(cols!=B.cols))
        return false;
    for (int i = 0; i < rows ; i++)
        for (int j = 0; j < cols ; j++)
            if (matr[i][j] != B.matr[i][j])
                return false;
    return true; 
}

bool Matrix::operator !=(const Matrix &B) const { 
    if ((rows!=B.rows)||(cols!=B.cols))
        return true;
    for (int i = 0; i < rows ; i++)
        for (int j = 0; j < cols ; j++)
            if (matr[i][j] != B.matr[i][j])
                return true;
    return false; 
}


ProxyRow::ProxyRow(int * row , size_t m) {
    data = row ;
    cols = m;
}

int & ProxyRow::operator[](size_t j) {
    if (j < cols)
        return data[j];
    else 
        throw std::out_of_range("");
}

ProxyRow Matrix::operator [](size_t i)  {
    if (i < rows) 
        return ProxyRow(matr[i],cols);
    else 
        throw std::out_of_range("");
}


     
std::ostream & operator <<(std::ostream &out, const Matrix & A) {
    std::cout<<std::endl;
    for (int i = 0; i < A.rows ; i++) {
        for (int j = 0; j < A.cols ; j++)
            std::cout<<A.matr[i][j]<<" ";
        std::cout<<std::endl;
    } 
    return out; 
} 





