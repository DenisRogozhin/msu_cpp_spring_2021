#pragma once

#include <iostream>
#include <cassert> 
#include <sstream>

enum class Error {
    NoError,
    CorruptedArchive,
    WrongType,
    NotEnoughData,
    Bad_uint64
};


class Serializer { 
    public:
        explicit Serializer(std::ostream& out) : out_(out)  {  }

        template <class T>
        Error save(T& object)  {
            return object.serialize(*this);
        }

        template <class... ArgsT>
        Error operator()(ArgsT... args) {
            return process(args...);
        }

    private:
	static constexpr char separator = ' ';
        bool need_separator = false;
	std::ostream& out_;	

	Error process(bool arg) {
	    if (arg == true)
                out_ << "true";
	    else
		out_ << "false";  
            if (need_separator)
		out_ << separator;
            need_separator = false;
	    return Error::NoError; 
	}

	Error process(uint64_t arg) {
	    out_ << arg;
            if (need_separator)
		out_ << separator;
            need_separator = false;
	    return Error::NoError; 
	}


        template <class T>
	Error process(T arg) {
            return Error::WrongType;
	}



	template <class T, class ...ArgsT>
	Error process(T arg, ArgsT ... args) {
            need_separator = true;
	    Error e1 = process(arg);
            if (e1 == Error::NoError)
		return process(args...);
	    else
		return e1;
	}
};


class Deserializer {
    public:
        explicit Deserializer(std::istream& in) : in_(in)  {  }

        template <class T>
        Error load(T& object)  {
            return object.deserialize(*this);
        }

        template <class... ArgsT>
        Error operator()(ArgsT... args) {
            return process(args...);
        }

    private:
	static constexpr char separator = ' ';
	std::istream& in_;	

	template <class T>
	Error process(T * arg) {
	    std::string data ;
	    in_ >> data ;
            if (data.length() == 0) {
	    	return Error::NotEnoughData;
	    }
	    if (std::is_same<T, bool>::value) {
		if (data == "true")
		    *arg = true;
		else 
		    if (data == "false")
		        *arg = false;
		    else
			return Error::CorruptedArchive;
	    }
	    else 
		if (std::is_same<T, uint64_t>::value) {
		    try {
		        *arg = std::stoull(data);
                    }
		    catch(...) {
			return Error::Bad_uint64;
		    }
                }
	        else 
                    return Error::WrongType; 
	    return Error::NoError; 
	}


	template <class T, class ...ArgsT>
	Error process(T * arg, ArgsT ... args) {
	    Error err = process(arg);
	    if (err != Error::NoError)
		return err;
	    return process(args...);
	}
 
};



