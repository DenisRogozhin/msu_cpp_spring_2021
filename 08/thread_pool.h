#pragma once

#include <iostream>
#include <cassert> 
#include <sstream>
#include <thread>
#include <mutex>
#include <future>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>



class ThreadPool  {
	std::vector<std::thread> pool;
        std::queue<std::function<void()>> tasks;
        size_t size;
	bool stop;
	std::mutex tasks_mutex;
        std::condition_variable condition; 

    public:
         ThreadPool(size_t poolSize) {
	    stop = false;
	    size = poolSize;    
            for (int i = 0; i < size; ++i)
        	pool.emplace_back( 
		    [this] {
                	while (true) {
                    	    std::function<void()> task;
                            {
                        	std::unique_lock<std::mutex> lock(tasks_mutex);
				while (!stop && tasks.empty())
                        	    condition.wait(lock);
                        	if (stop && tasks.empty()) 
                            	    return;
                        	task = std::move(tasks.front());
                        	tasks.pop();  
                    	    }
                    	    task();
                        }
                    }
                );
	}




	~ThreadPool() {
            {
                std::unique_lock<std::mutex> lock(tasks_mutex);
                stop = true;
            }
            condition.notify_all();
            for(std::thread &worker: pool)
                worker.join(); 
        }



        template <class Func, class... Args>
        auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    	    using return_type = typename std::result_of<Func(Args...)>::type;
            auto task = std::make_shared<std::packaged_task<return_type()>> (
                std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
            );
            std::future<return_type> result = task->get_future(); 
	    {
        	std::unique_lock<std::mutex> lock(tasks_mutex);
        	tasks.emplace([task](){ (*task)(); });
            }
    	    condition.notify_one();
            return result;
        }
};
