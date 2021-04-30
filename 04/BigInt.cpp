#include "BigInt.h"

BigInt::BigInt(const std::string & s) {
    std::string str ;
    int k ;
    if (s[0] == '-') {
	k = 1;
	minus = true;
    }
    else {
	k = 0;
	minus = false;
    }
    while (s[k] == '0')
	k++;
    str = s.substr(k, s.length() - k);
    int len = str.length();
    if (len % 9 == 0)
    	size = len / 9 ;
    else
	size = len / 9 + 1;
    digit = new int32_t[size];
    for (int i = 0 ; i < size ; i++) {
        if (len < 9) {
	    digit[i] = std::stoul(str);
        }
        else {
            std::string sub_str = str.substr(len - 9, 9);
            digit[i] = std::stoul(sub_str);
            for (int j = 0 ; j < 9 ; j ++)
		str.pop_back();
            len -= 9;
        }
    }		   
 }

BigInt::BigInt() {
    minus = false;
    digit = nullptr;
    size = 0;
}

BigInt::BigInt(const BigInt & other) {
    minus = other.minus;
    size = other.size;
    digit = new int32_t[size];
    for (int i = 0 ; i < size ; i++) 
	digit[i] = other.digit[i];
}


BigInt & BigInt::operator=(const BigInt & other) {
    if (this == &other)
	return *this;
    if (digit != nullptr)
	delete[] digit;
    minus = other.minus;
    size = other.size;
    digit = new int32_t[size];
    for (int i = 0 ; i < size ; i++) 
	digit[i] = other.digit[i];
    return *this;
}

BigInt::BigInt (BigInt && other) {
    minus = other.minus;
    size = other.size;
    digit = other.digit;
    other.digit = nullptr; 
    other.size = 0;
    other.minus = false;
}


BigInt & BigInt::operator=(BigInt && other) {
    if (this == &other)
	return *this;
    if (digit != nullptr)
	delete[] digit;
    minus = other.minus;
    size = other.size;
    digit =other.digit;
    other.digit = nullptr; 
    other.size = 0;
    other.minus = false;
    return *this;
}

BigInt::~BigInt() {
    if (digit != nullptr) 
	delete [] digit;
}


int get_len(int32_t x) {
    int n = 0;
    if (x == 0)
	return 1;
    while (x > 0) {
	n ++;
	x = x / 10;
    }
    return n;
}

std::ostream & operator <<(std::ostream &out, const BigInt & other) {
    if (other.minus)
	std::cout<<"-";
    for (int i = other.size - 1; i > 0 ; i--) 
	std::cout<<other.digit[i];
    if (other.size > 1) {
        int delta = 9 - get_len(other.digit[0]);
        for (int i = 0; i < delta ; i++) 
	    std::cout<<0;
        std::cout<<other.digit[0];
    }
    else
	std::cout<<other.digit[0];
    std::cout<<std::endl;    
    return out;
}

BigInt operator -(BigInt & other) {
    BigInt a(other);
    a.minus = not a.minus; 
    return a;
}



BigInt BigInt::operator+(const BigInt & other) const {
    BigInt a;
    if (minus && not other.minus) {
	a = *this;
        a.minus = false;
	return (other - a);
	//other - this
    }
    if (not minus && other.minus) {
	//this - other
        a = other;
        a.minus = false;
	return (*this - a);
    } 
    if (not minus && not other.minus) {
        a.minus = false;
        a.size = other.size > size ? other.size : size;
        a.digit = new int32_t[a.size];
	int32_t memory = 0;
	int32_t max = 999999999ul;
	for (int i = 0; i < a.size ; i ++) {
            int32_t x ;
            if (i >= size) 
       		x = other.digit[i] + memory;
            else
		if (i >= other.size) 
		    x = digit[i] + memory; 
                else
	            x = digit[i] + other.digit[i] + memory; 
	    if ( x > max ) {
		memory = 1; 
                a.digit[i] = x - max - 1;
            }
	    else { 
		memory = 0 ;
                a.digit[i] = x ; 
            }	
	}
        if (memory > 0) {
	    BigInt b;
            b.size = a.size + 1;
	    b.minus = a.minus;
	    b.digit = new int32_t [b.size];
	    for (int i = 0; i < a.size ; i ++) 
		b.digit[i] = a.digit[i];
	    b.digit[a.size] = 1; 
            return b;
        }
        return a;
    }
    //-x + -y = - (x + y)
    BigInt d(*this);
    BigInt e(other);
    d.minus = false;
    e.minus = false;
    a = d + e ;
    a.minus = true;
    return a;
}   


BigInt BigInt::operator-(const BigInt & other) const {
    BigInt a;
    if (minus && not other.minus) {
        BigInt d(*this);
        BigInt e(other);
        d.minus = false;
        e.minus = false;
	a = d + e ;
        a.minus = true;
        return a;
	//- this - other = - (this + other)
    }
    if (not minus && other.minus) {
	//this - (-other) = this + other
        a = other;
        a.minus = false;
	return (*this + a);
    } 
    if (not minus && not other.minus) {
	if (*this < other) {
	    BigInt d = other - *this;
            d.minus = true;
            return d;
        } 		
        a.minus = false;
        a.size = size;
        a.digit = new int32_t[a.size];
	int32_t memory = 0;
	int32_t max = 999999999ul;
	for (int i = 0; i < a.size ; i ++) {
            int32_t x ;
	    if (i >= other.size) 
		x = digit[i] - memory; 
            else
	        x =  digit[i] - other.digit[i] - memory; 
	    if ( x < 0 ) {
	        memory = 1; 
                a.digit[i] = x + max + 1 ;
            }
	    else { 
		memory = 0 ;
                a.digit[i] = x ; 
            }	
	}         if (a.digit[a.size - 1] == 0) {
            BigInt b;
            b.size = a.size - 1;
	    b.minus = a.minus;
	    b.digit = new int32_t [b.size];
	    for (int i = 0; i < b.size ; i ++) 
		b.digit[i] = a.digit[i];
            return b;
        }
        return a;
    }
    //-x - -y = y - x
    a = other;
    a.minus = false;
    BigInt b = *this; 
    b.minus = false;
    return a - b;
}


BigInt BigInt::operator*(const BigInt & other) const {
    BigInt a;
    a.minus = !(minus == other.minus);
    a.size = other.size + size;
    a.digit = new int32_t[a.size];
    for (int i = 0 ; i < a.size; i++)
	a.digit[i] = 0;
    int32_t memory = 0;
    uint64_t offset = std::pow(10, 9);
    int i = 0;
    for (; i < other.size; i++) {
        int j = 0;
        for (; j < size; j++) {
            uint64_t mul_res = (uint64_t) other.digit[i] * digit[j];
            if (!mul_res) {
                   a.digit[j + i] = mul_res;
            }
            uint64_t k = 0; 
            for (; mul_res; k++) {
                a.digit[i + j + k] += (mul_res % uint32_t(offset) + (memory ? 1: 0));
                mul_res /= offset;
                memory = 0;
                if (a.digit[i + j + k] >= offset) {
                    a.digit[i + j + k] -= offset;
                    memory = 1;
                }
            }
            if (memory) {
                a.digit[j + i + k] ++;
                memory = 0;
            }
        }
    }
    int zero = 0;
    bool stop = false;
    for (int l = a.size - 1 ; (!stop) && (l >= 0) ; l--) 
	if (a.digit[l] == 0) 
	    zero++;
        else
	    stop = true;
    BigInt b;
    b.minus = a.minus;
    b.size = a.size - zero;
    b.digit = new int32_t[b.size];
    for (int l = 0 ; l < b.size; l++)
	b.digit[l] = a.digit[l];
    return b;
} 


bool BigInt::operator>(const BigInt & other) const {
    if (minus && not other.minus)
	return false;
    if (not minus && other.minus)
	return true;
    if (minus && other.minus) {
	if (size < other.size) 
	    return true;
        if (size > other.size)
	    return false;
        for (int i = size - 1 ; i >= 0 ; i--) {
	    if (digit[i] < other.digit[i])
	        return true;
            if (digit[i] > other.digit[i])
	        return false;
        }
        return false;
    }
    if (size > other.size) 
	return true;
    if (size < other.size)
	return false;
    for (int i = size - 1 ; i >= 0 ; i--) {
	if (digit[i] > other.digit[i])
	    return true;
        if (digit[i] < other.digit[i])
	    return false;
    }
    return false;
}


bool BigInt::operator>=(const BigInt & other) const {
    if (minus && not other.minus)
	return false;
    if (not minus && other.minus)
	return true;
    if (minus && other.minus) {
	if (size < other.size) 
	    return true;
        if (size > other.size)
	    return false;
        for (int i = size - 1 ; i >= 0 ; i--) {
	    if (digit[i] < other.digit[i])
	        return true;
            if (digit[i] > other.digit[i])
	        return false;
        }
        return true;
    }
    if (size > other.size) 
	return true;
     if (size < other.size)
	return false;
    for (int i = size - 1 ; i >= 0 ; i--) {
	if (digit[i] > other.digit[i])
	    return true;
        if (digit[i] < other.digit[i])
	    return false;
    }
    return true;
}

bool BigInt::operator<(const BigInt & other) const {
    if (minus && not other.minus)
	return true;
    if (not minus && other.minus)
	return false;
    if (minus && other.minus) {
	if (size > other.size) 
	    return true;
        if (size < other.size)
	    return false;
        for (int i = size - 1 ; i >= 0 ; i--) {
	    if (digit[i] > other.digit[i])
	        return true;
            if (digit[i] < other.digit[i])
	        return false;
        }
        return false;
    }
    if (size < other.size) 
	return true;
    if (size > other.size) 
	return false;
    for (int i = size - 1 ; i >= 0 ; i--) {
	if (digit[i] < other.digit[i])
	    return true;
        if (digit[i] > other.digit[i])
	    return false;
    }
    return false;
}

bool BigInt::operator<=(const BigInt & other) const {
    if (minus && not other.minus)
	return true;
    if (not minus && other.minus)
	return false;
    if (minus && other.minus) {
	if (size > other.size) 
	    return true;
	if (size < other.size)
	    return false;
        for (int i = size - 1 ; i >= 0 ; i--) {
	    if (digit[i] > other.digit[i])
	        return true;
            if (digit[i] < other.digit[i])
	        return false;
        }
        return true;
    }
    if (size < other.size) 
	return true;
    if (size > other.size) 
	return false;
    for (int i = size - 1 ; i >= 0 ; i--) {
	if (digit[i] < other.digit[i])
	    return true;
        if (digit[i] > other.digit[i])
	    return false;
    }
    return true;
}

bool BigInt::operator==(const BigInt & other) const { 
    if (minus != other.minus)
	return false;
    if (size != other.size) 
	return false;
    for (int i = size - 1 ; i >= 0 ; i--) 
	if (digit[i] != other.digit[i])      
	    return false;
    return true;
}

bool BigInt::operator!=(const BigInt & other) const {
    if (minus != other.minus) 
	return true;
    if (size != other.size) 
	return true;
    for (int i = size - 1 ; i >= 0 ; i--) 
	if (digit[i] != other.digit[i])
	    return true;
    return false;
}

BigInt BigInt::operator+(const uint32_t & other) const {
    BigInt a;
    a.size = 1; 
    a.digit =  new int32_t[a.size];
    if (other < 0) {
	a.minus = true;
	a.digit[0] = - other;
    }
    else {
	a.minus = false;
	a.digit[0] = other;
    }
    return *this + a;
}

BigInt BigInt::operator-(const uint32_t & other) const {
    BigInt a;
    a.size = 1; 
    a.digit =  new int32_t[a.size];
    if (other < 0) {
	a.minus = true;
	a.digit[0] = - other;
    }
    else {
	a.minus = false;
	a.digit[0] = other;
    }
    return *this - a;
}

BigInt BigInt::operator*(const uint32_t & other) const {
    BigInt a;
    a.size = 1; 
    a.digit =  new int32_t[a.size];
    if (other < 0) {
	a.minus = true;
	a.digit[0] = - other;
    }
    else {
	a.minus = false;
	a.digit[0] = other;
    }
    return *this * a;
}




