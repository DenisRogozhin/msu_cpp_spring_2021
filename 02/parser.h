#pragma once

#include <iostream>
#include <cassert> 
#include <functional>

using SimpleCallback = std::function<void ()>;
using TokenCallback = std::function<void (const std::string & token)>;

class TokenParser   {
 public:
     TokenParser();
     void SetStartCallback(SimpleCallback func);
     void SetEndCallback(SimpleCallback func);
     void SetDigitTokenCallback(TokenCallback func );
     void SetWordTokenCallback(TokenCallback func);
     void parse(const std::string & text);
     bool check_digit(const std::string & text);
 private:
    SimpleCallback start_callback, end_callback;
    TokenCallback digit_callback, word_callback;
    
};
