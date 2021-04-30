#include "format.h"

void ok_work_test() {
    auto text = format("{1}+{1} = {0}. {2}-{1}={0},{3}", 2, "one","3","okay");
    assert(text == "one+one = 2. 3-one=2,okay");
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


void empty_string_test(){
    auto text = format("", 2, "one","3","okay");
    assert(text == "");
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

int main() {
    ok_work_test();
    no_open_bracket_test();
    no_close_bracket_test();
    single_brackets();
    empty_string_test();
    empty_index();
    wrong_index();
    big_index();
    return 0;
}





