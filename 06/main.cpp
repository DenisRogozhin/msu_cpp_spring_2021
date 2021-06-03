#include "format.h"

void ok_work_test() {
    auto text = format("{1}+{1} = {0}. {2}-{1}={0},{3}", 2, "one","3","okay");
    assert(text == "one+one = 2. 3-one=2,okay");
}


void base_class_exception_test() {
     bool t = false;
    try {
        auto text = format("{1}+{1} = 0}", 2, "one");
    }
    catch(std::logic_error& b) {
	t = true;
    } 
    assert(t);

}

void no_open_bracket_test() {
    bool t = false;
    try {
        auto text = format("{1}+{1} = 0}", 2, "one");
    }
    catch(Bad_bracket& b) {
	b.info();
	t = true;
    }
    assert(t);
}


void no_close_bracket_test() {
    bool t = false;
    try {
        auto text = format("{1}+{1 = {0}", 2, "one");
    }
    catch(Bad_bracket& b) {
	b.info();
	t = true;
    }
    assert(t);
}

void single_brackets() {
    bool t = false;
    bool p = false;
    try {
        auto text = format("{", 2, "one");
    }
    catch(Bad_index& b) {
	b.info();
	t = true;
    }
    try {
        auto text = format("}", 2, "one");
    }
    catch(Bad_bracket& b) {
	b.info();
	p = true;
    }
    assert(t && p);
}


void unused_args_test(){
    bool p = false;
    try {
        auto text = format("{1} + {2}", 2, "one","3","okay");
    }
    catch(Too_much_args& b) {
	b.info();
	p = true;
    }
    assert(p);
}

void empty_index() {
    bool t = false;
    try {
        auto text = format("{1}+{} = {0}", 2, "one");
    }
    catch(Bad_index& b) {
	b.info();
	t = true;
    }
    assert(t);
}

void wrong_index() {
    bool t = false;
    try {
        auto text = format("{1}+{a} = {0}", 2, "one");
    }
    catch(Bad_index& b) {
	b.info();
	t = true;
    }
    assert(t);
}

void big_index() {
    bool t = false;
    try {
        auto text = format("{1}+{3} = {0}", 2, "one","aaaaaaaaaaaa");
    }
    catch(Bad_index& b) {
	b.info();
	t = true;
    }
    assert(t);
}

void empty_string() {
    auto text = format("");
    assert(text == "");
}

void one_arg_test() {
    auto text = format("{0}","hello");
    assert(text == "hello");
}

void many_args_test() {
    auto text = format("{1}{1}{1}{1}{1}{1}{1}","a","hello");
    assert(text == "hellohellohellohellohellohellohello");  
    auto text1 = format("{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}{10}{11}{12}","a","b","c","d","e","f","g","h","i","j","k","l","m");
    assert(text1 == "abcdefghijklm");
}

void too_much_open_brackets() {
    bool t = false;
    try {
        auto text = format("{1}+{1} = {{0}", 2, "one");
    }
    catch(Bad_index& b) {
	b.info();
	t = true;
    }
    assert(t);
}


void too_much_close_brackets() {
    bool t = false;
    try {
        auto text = format("{1}+{1}} = {0}", 2, "one");
    }
    catch(Bad_bracket& b) {
	b.info();
	t = true;
    }
    assert(t);
}


void only_brackets() {
    bool t = false;
    try {
        auto text = format("{}", 2, "one");
    }
    catch(Bad_index& b) {
	b.info();
	t = true;
    }
    assert(t);
}


void string_in_brackets() {
    bool t = false;
    try {
        auto text = format("{hello}", 2, "one");
    }
    catch(Bad_index& b) {
	b.info();
	t = true;
    }
    assert(t);
}

void mix_of_num_and_string_in_brackets() {
    bool t = false;
    try {
        auto text = format("{1e}", 2, "one");
    }
    catch(Bad_bracket& b) {
	b.info();
	t = true;
    }
    assert(t);
}


void big_int_in_brackets() {
    bool t = false;
    try {
        auto text = format("{99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999}", 2);
    }
    catch(Big_index& b) {
	b.info();
	t = true;
    }
    assert(t);
}

int main() {
    ok_work_test();
    empty_string();
    one_arg_test();
    many_args_test();  
    no_open_bracket_test();
    base_class_exception_test();
    no_close_bracket_test();
    single_brackets();
    unused_args_test();
    empty_index();
    wrong_index();
    big_index();
    too_much_open_brackets();
    too_much_close_brackets();   
    only_brackets();
    string_in_brackets();
    mix_of_num_and_string_in_brackets(); 
    big_int_in_brackets();
    return 0;
}





