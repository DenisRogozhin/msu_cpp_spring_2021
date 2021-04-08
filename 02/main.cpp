#include "parser.h"

static std::list <std::string> words ; 
static std::list <uint64_t> digits; 

void start() {
    std::cout<<"Start parsing"<<std::endl;
    return;
}

void finish() {
    std::cout<<"Finish parsing"<<std::endl;
    return;
}

void word_func(const std::string & token) {
    words.push_back(token);
    std::cout<<"catch word "<<token<<std::endl;
    return;
}

void digit_func(uint64_t & digit) {
    digits.push_back(digit);
    return;
}

void all_callbacks_test() {
    words.clear();
    digits.clear();
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    Pars.SetDigitTokenCallback(digit_func);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("dsfd 123 12e /2 1w2 1337	fdgd");
    std::list <std::string> words_1;
    words_1.push_back("dsfd");
    words_1.push_back("12e");
    words_1.push_back("/2");
    words_1.push_back("1w2");
    words_1.push_back("fdgd");
    std::list <uint64_t> digits_1; 
    digits_1.push_back(123);
    digits_1.push_back(1337);
    assert((digits_1 == digits) && (words_1 == words));
}

void no_start_and_fin_callback_test() {
    words.clear();
    digits.clear();
    TokenParser Pars;
    Pars.SetDigitTokenCallback(digit_func);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("       144 \n 		  d1111  44	 ");
    std::list <std::string> words_1;
    words_1.push_back("d1111");
    std::list <uint64_t> digits_1; 
    digits_1.push_back(144);
    digits_1.push_back(44);
    assert((digits_1 == digits) && (words_1 == words));
}


void no_tokens_callback_test() {
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    //Pars.SetDigitTokenCallback(digit_func);
    //Pars.SetWordTokenCallback(word_func);
    Pars.parse("56345e1 f 	e\ng\n");
    //assert((digit_count == 0) && (word_count == 4));
}



void big_number_test() {
    words.clear();
    digits.clear();
    TokenParser Pars;
    Pars.SetDigitTokenCallback(digit_func);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("  18446744073709551615	 18446744073709551616 ");
    std::list <std::string> words_1;
    words_1.push_back("18446744073709551616");
    std::list <uint64_t> digits_1; 
    digits_1.push_back(18446744073709551615);
    assert((digits_1 == digits) && (words_1 == words));
}

void nullptr_callback_test() {
    words.clear();
    digits.clear();
    TokenParser Pars;
    Pars.SetStartCallback(nullptr);
    Pars.SetEndCallback(finish);
    Pars.SetDigitTokenCallback(digit_func);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("dsfd 123 12e /2 1w2 1337	4 fdgd");
    std::list <std::string> words_1;
    words_1.push_back("dsfd");
    words_1.push_back("12e");
    words_1.push_back("/2");
    words_1.push_back("1w2");
    words_1.push_back("fdgd");
    std::list <uint64_t> digits_1; 
    digits_1.push_back(123);
    digits_1.push_back(1337);
    digits_1.push_back(4);
    assert((digits_1 == digits) && (words_1 == words));
}


void empty_string_test() {
    words.clear();
    digits.clear();
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("");
    std::list <std::string> words_1;
    std::list <uint64_t> digits_1; 
    assert((digits_1 == digits) && (words_1 == words));
}

void space_string_test() {
    words.clear();
    digits.clear();
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("	  \n 	 	 \n\n\n\t	 ");
    std::list <std::string> words_1;
    std::list <uint64_t> digits_1; 
    assert((digits_1 == digits) && (words_1 == words));
}

void one_digit_test() {
    words.clear();
    digits.clear();
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    Pars.SetDigitTokenCallback(digit_func);
    Pars.parse("1");
    std::list <std::string> words_1;
    std::list <uint64_t> digits_1; 
    digits_1.push_back(1);
    assert((digits_1 == digits) && (words_1 == words));
}

void one_word_test() {
    words.clear();
    digits.clear();
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("e");
    std::list <std::string> words_1;
    words_1.push_back("e");
    std::list <uint64_t> digits_1; 
    assert((digits_1 == digits) && (words_1 == words));
}

int main() {
    all_callbacks_test();
    no_start_and_fin_callback_test();
    no_tokens_callback_test();
    big_number_test();
    nullptr_callback_test();
    empty_string_test(); 
    space_string_test();
    one_digit_test();
    one_word_test();
    return 0;
}





