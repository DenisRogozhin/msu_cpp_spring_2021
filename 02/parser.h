#pragma once

#include <iostream>
#include <cassert> 
#include <functional>
#include <list>

using SimpleCallback = std::function<void ()>;
using WordCallback = std::function<void (const std::string & token)>;
using DigitCallback = std::function<void (uint64_t & digit)>;

class TokenParser   {
 public:
     TokenParser();
     void SetStartCallback(SimpleCallback func);
     void SetEndCallback(SimpleCallback func);
     void SetDigitTokenCallback(DigitCallback func );
     void SetWordTokenCallback(WordCallback func);
     void parse(const std::string & text);
     bool check_digit(const std::string & text);
 private:
    SimpleCallback start_callback, end_callback;
    WordCallback word_callback;
    DigitCallback digit_callback;
    
};
