#pragma once

#include <thread>
#include <atomic>
#include <vector>
#include <iostream>
#include <functional>
#include <future>
#include <iostream>

#include "SafeQueue.hpp"

using TTask = std::function<void()>;

class join_threads 
{
	std::vector<std::thread>& threads;

public:
	join_threads(std::vector<std::thread>& _threads);
	~join_threads();
};


class function_wrapper {
	struct impl_base {
		virtual void call() = 0;
		virtual ~impl_base() {}
	};

	template<typename F>
	struct impl_type : impl_base
	{
		F f;
		impl_type(F&& f_) : f(std::move(f_)) {}
		void call() { f(); }
	};

	std::unique_ptr<impl_base> impl;

public:
	template<typename F>
	function_wrapper(F&& f) :
		impl(new impl_type<F>(std::move(f)))
	{}

	void operator()() { impl->call(); }

	function_wrapper()
	{}

	function_wrapper(function_wrapper&& other) :
		impl(std::move(other.impl))
	{}

	function_wrapper& operator=(function_wrapper&& other)
	{
		impl = std::move(other.impl);
		return *this;
	}

	function_wrapper(const function_wrapper&) = delete;
	function_wrapper(function_wrapper&) = delete;
};


class ThreadPool
{
// Methods
public:

    ThreadPool(uint32_t Size = std::thread::hardware_concurrency());
    ~ThreadPool();
    
    // std::future<typename std::result_of<TTask()>::type> submit(TTask Task);
    template<typename T>
    // void submit(T Task)
    std::future<typename std::result_of<T()>::type> ThreadPool::submit(T Task)
    {
        typedef typename std::result_of<T()>::type TResult;
        std::packaged_task<TResult()> PackagedTask(std::move(Task));
        std::future<TResult> Result(PackagedTask.get_future());
        mQueue.push(std::move(PackagedTask));

        return Result;
    }
private:
    void worker_thread();

// Variables
public:

private:
    std::atomic_bool mDone;
    SafeQueue<function_wrapper> mQueue;
    std::vector<std::thread> mThreads;
    join_threads joiner;
    
};

