#pragma once

#include <iostream>
#include <cassert> 
#include <cmath>


class BigInt {
    public:
       
       BigInt();
       BigInt(const std::string & s); 
       BigInt(const BigInt & other); 
       BigInt & operator=(const BigInt & other); 
       BigInt (BigInt && other); 
       BigInt & operator=(BigInt && other); 
       ~BigInt();  

     
       BigInt operator+(const uint32_t & other) const ;
       BigInt operator-(const uint32_t & other) const ;
       BigInt operator*(const uint32_t & other) const ;

       BigInt operator+(const BigInt & other) const ;
       BigInt operator-(const BigInt & other) const ;
       BigInt operator*(const BigInt & other) const;
       
       
       bool operator>(const BigInt & other) const ;
       bool operator>=(const BigInt & other) const;
       bool operator<(const BigInt & other) const;
       bool operator<=(const BigInt & other) const;
       bool operator==(const BigInt & other) const;
       bool operator!=(const BigInt & other) const;
       

       friend std::ostream & operator <<(std::ostream &out, const BigInt & other); 
       friend BigInt operator -(BigInt & other);  
    private:
        int * digit = nullptr; 
        bool minus = false;
	int size;
};

