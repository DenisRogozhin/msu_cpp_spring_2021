#include "thread_pool.h"
#include <unistd.h>
#include <stdio.h> 
#include <time.h> 


int sum(int a, int b) {
    return a+b; 
}


int diff(int a, int b) { 
    return a-b;
}



void ok_test() {
    ThreadPool pool(3);
    auto task1 = pool.exec(sum, 10, 5);
    auto task2 = pool.exec(diff, 10, 5);
    auto res_1 = task1.get(); 
    auto res_2 = task2.get();
    assert((res_1 == 15) && (res_2 == 5));
}

void queue_test() {
    time_t start, end;
    ThreadPool pool(2);
    time(&start);
    auto task1 = pool.exec([]() { sleep(2); return 1; });
    auto task2 = pool.exec([]() { sleep(2); return 1; });
    auto task3 = pool.exec([]() { sleep(2); return 1; });
    task1.get(); 
    task2.get();
    task3.get();
    time(&end);
    double seconds = difftime(end, start); 
    assert ((seconds > 3.5) && (seconds < 6.0));
}



int main() {
    ok_test();
    queue_test();
}





