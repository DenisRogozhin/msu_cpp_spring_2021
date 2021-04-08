#include "parser.h"

void TokenParser::SetStartCallback(SimpleCallback func) {
    start_callback = func ;
}


void TokenParser::SetEndCallback(SimpleCallback func) {
    end_callback = func ;
}

void TokenParser::SetDigitTokenCallback(DigitCallback func) { 
    digit_callback = func;
}
     

void TokenParser::SetWordTokenCallback(WordCallback func) {
    word_callback = func;
}


bool TokenParser::check_digit(const std::string & token) {
    int n = token.length();
    uint64_t  sum = 0;
    uint64_t  max_value = 18446744073709551615;
    for (int i=0 ; i<n ; i++) 
        if ((token[i] > '9') || (token[i] < '0'))
            return false;
        else 
	    if ((max_value - 10 * sum) < (token[i] - '0')) 
                return false;
            else
                sum = sum * 10 + token[i] - '0' ; 
    return true;
}

uint64_t convert(const std::string & token){
    uint64_t  sum = 0;
    int n = token.length();
    for (int i=0 ; i<n ; i++) 
        sum = sum * 10 + token[i] - '0' ;
    return sum;
    
}

void TokenParser::parse(const std::string & text) {
    if (start_callback != nullptr)
        start_callback();
    int n = text.length();
    int start_pos = 0 , i = 0;
    while (start_pos < n) {
        while ((i < n) && ((text[i] == ' ') || (text[i] == '\t') || (text[i] == '\n')))
            i++;
        start_pos = i;
        while ((i < n) && (text[i] != ' ') && (text[i] != '\t') && (text[i] != '\n'))
            i++;
        if (i != start_pos) {
            std::string token = text.substr(start_pos, i - start_pos);
            if (check_digit(token)) {
                if (digit_callback != nullptr) {
		    uint64_t k = convert(token);
                    digit_callback(k);
                }
           }
            else
                if (word_callback != nullptr)
                    word_callback(token);
        }
        start_pos = i;
    }
    if (end_callback != nullptr)
        end_callback();
    return ; 
}


TokenParser::TokenParser()  {
    start_callback = [] {};
    end_callback = [] {};
    digit_callback = [](uint64_t &) {};
    word_callback = [](const std::string&) {};
}







