#pragma once

#include <iostream>
#include <cassert> 
#include <sstream>

enum class Error {
    NoError,
    CorruptedArchive,
    WrongType
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
	std::ostream& out_;	

	template <class T>
	Error process(T arg) {
	    if (std::is_same<T, bool>::value) {
		if (arg)
		    out_ << "true";
		else
		    out_ << "false"; 
	    }
	    else 
		if (std::is_same<T, uint64_t>::value) 
		    out_ << arg;
	        else
                    return Error::WrongType;
	    return Error::NoError; 
	}


	template <class T, class ...ArgsT>
	Error process(T arg, ArgsT ... args) {
	    if (std::is_same<T, bool>::value) {
		if (arg)
		    out_ << "true" << separator;
		else
		    out_ << "false" << separator; 
	    }
	    else 
		if (std::is_same<T, uint64_t>::value) 
		    out_ << arg << separator;
	    else 
                return Error::WrongType; 
	return process(args...);
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
		if (std::is_same<T, uint64_t>::value) 
		    *arg = std::stoull(data);
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



