#include "parser.h"

static int digit_count = 0;
static int digit_sum = 0;
static int word_count = 0;
static int word_sum_len = 0;

void start() {
    std::cout<<"Start parsing"<<std::endl;
    return;
}

void finish() {
    std::cout<<"Finish parsing"<<std::endl;
    return;
}

void word_func(const std::string & token) {
    word_count++;
    std::cout<<"catch word "<<token<<std::endl;
    return;
}

void digit_func(const std::string & token) {
    digit_count++;
    std::cout<<"catch digit "<<token<<std::endl;
    return;
}

void all_callbacks_test() {
    digit_count = 0;
    word_count = 0;
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    Pars.SetDigitTokenCallback(digit_func);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("dsfd 123 12e /2 1w2 1337	fdgd");
    assert((digit_count == 2) && (word_count == 5));
}

void no_start_and_fin_callback_test() {
    digit_count = 0;
    word_count = 0;
    TokenParser Pars;
    Pars.SetDigitTokenCallback(digit_func);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("       144 \n 		  d1111  44	 ");
    assert((digit_count == 2) && (word_count == 1));
}


void no_tokens_callback_test() {
    digit_count = 0;
    word_count = 0;
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    //Pars.SetDigitTokenCallback(digit_func);
    //Pars.SetWordTokenCallback(word_func);
    Pars.parse("56345e1 f 	e\ng\n");
    //assert((digit_count == 0) && (word_count == 4));
}

void sum(const std::string & token) {
    digit_sum += std::stoi(token);
}

void digit_test() {
    digit_sum = 0;
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    Pars.SetDigitTokenCallback(sum);
    Pars.parse("dsfd 123 12e /2 1w2 1337	4 fdgd");
    assert(digit_sum == 1464);
}

void len(const std::string & token) {
    word_sum_len += token.length();
}

void word_test() {
    word_sum_len = 0;
    TokenParser Pars;
    Pars.SetStartCallback(start);
    Pars.SetEndCallback(finish);
    Pars.SetWordTokenCallback(len);
    Pars.parse("dsfd 123 12e /2 1w2 1337	4 fdgd");
    assert(word_sum_len == 16);
}

void big_number_test() {
    digit_count = 0;
    word_count = 0;
    TokenParser Pars;
    Pars.SetDigitTokenCallback(digit_func);
    Pars.SetWordTokenCallback(word_func);
    Pars.parse("  18446744073709551615	 18446744073709551616 ");
    assert((digit_count == 1) && (word_count == 1));
}


int main() {
    all_callbacks_test();
    no_start_and_fin_callback_test();
    no_tokens_callback_test();
    digit_test();
    big_number_test();
    return 0;
}





