#pragma once

#include <iostream>
#include <cassert> 
#include <sstream>
#include <exception>


class Error : public std::logic_error {
        std::string message;
        int position;
    public:
	Error(const std::string & text, int pos): std::logic_error(text) {
		message = text;
		position = pos;
	}

	void info() {
	    std::cout << "Error at position: " << position << "."<< message <<std::endl;
	}
};

class Bad_index : public Error {
    public:
        Bad_index(const std::string& text, int pos) : Error(text, pos) {};
};

class Bad_bracket : public Error {
    public:
        Bad_bracket(const std::string& text, int pos) : Error(text, pos) {};
};


class Too_much_args : public Error {
    public:
        Too_much_args(const std::string& text, int pos) : Error(text, pos) {};
};

class Big_index : public Error {
    public:
        Big_index(const std::string& text, int pos) : Error(text, pos) {};
};

template <class T>
std::stringstream get_arg(int ind, T first) {
    std::stringstream result;
    result << first;
    return result;
}

std::stringstream get_arg(int ind) {
    std::stringstream result;
    result << "";
    return result;
}

template <class T, class ...Args>
std::stringstream get_arg(int ind, T first, Args ...args) {
    if (ind == 0) {
	std::stringstream result;
        result << first;
        return result;
    }
    else
	return get_arg(ind - 1, args...);

}


template <class ...Args>
std::string format(const std::string & text, Args ... args) {
    std::string result;
    std::string::const_iterator p = text.begin();
    int max_ind = -1;
    int num_of_arg = sizeof...(Args);
    int max_num = 2147483647;
    while ( p != text.end()) {
	if (*p != '{') {
	    if ( *p == '}')
		throw Bad_bracket("unexpected } before {.", p - text.begin() + 1);
	    else {
		result += *p;
		p ++;
	    }
	}
	//встретили {
	else {
	    p++;
            if ((p == text.end()) || (*p < '0') || (*p > '9')) 
		throw Bad_index("after { expected digit", p - text.begin() + 1) ;
	    int ind = 0;
	    while ((*p >= '0') && (*p <= '9')) {
                int diff = max_num - 10 * ind - (*p - '0');
                if (diff < 0) 
		    throw Big_index("index is very big",  p - text.begin() + 1) ;
		ind = ind * 10 + (*p - '0');
		p++;
	    }
            if (ind >= num_of_arg)
		throw Bad_index("index is very big!", p - text.begin() + 1) ;
            if (ind > max_ind)
		max_ind = ind;
	    if ((p == text.end()) || (*p != '}'))
		throw Bad_bracket("expected } after index", p - text.begin() + 1) ;
	    else
		p++;
	    std::stringstream arg = get_arg(ind, args...);
            result += arg.str();    
	}
    }
    if (max_ind < num_of_arg - 1)
	throw Too_much_args("unused_args", p - text.begin() + 1) ;
    return result;    
} 


