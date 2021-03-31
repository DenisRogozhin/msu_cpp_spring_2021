#include "parser.h"

void TokenParser::SetStartCallback(SimpleCallback func) {
    start_callback = func ;
}


void TokenParser::SetEndCallback(SimpleCallback func) {
    end_callback = func ;
}

void TokenParser::SetDigitTokenCallback(TokenCallback func) { 
     digit_callback = func;
}
     

void TokenParser::SetWordTokenCallback(TokenCallback func) {
     word_callback = func;
}


bool TokenParser::check_digit(const std::string & token) {
    int n = token.length();
    for (int i=0 ; i<n ; i++) 
        if ((token[i] > '9') || (token[i] < '0'))
            return false;
    return true;
}

void TokenParser::parse(const std::string & text) {
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
            if (check_digit(token)) 
                digit_callback(token);
            else
                word_callback(token);
        }
        start_pos = i;
    }
    end_callback();
    return ; 
}


TokenParser::TokenParser()  {
    start_callback = [] {};
    end_callback = [] {};
    digit_callback = [](const std::string&) {};
    word_callback = [](const std::string&) {};
}







