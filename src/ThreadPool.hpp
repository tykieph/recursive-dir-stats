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


class FunctionWrapper {
public:
	FunctionWrapper()
	{}

	FunctionWrapper(FunctionWrapper &&other) :
		impl(std::move(other.impl))
	{}

	FunctionWrapper(const FunctionWrapper&) = delete;
	FunctionWrapper(FunctionWrapper&) = delete;	

	template<typename F>
	FunctionWrapper(F &&f) :
		impl(new impl_type<F>(std::move(f)))
	{}


	inline void operator()() { impl->call(); }
	FunctionWrapper &operator=(FunctionWrapper &&other)
	{
		impl = std::move(other.impl);
		return *this;
	}
private:
	struct impl_base 
	{
		virtual void call() = 0;
		virtual ~impl_base() {}
	};

	template<typename F>
	struct impl_type : impl_base
	{
		F mFunc;
		impl_type(F&& f) : mFunc(std::move(f)) {}
		void call() { mFunc(); }
	};

	std::unique_ptr<impl_base> impl;
};


class ThreadPool
{
// Methods
public:
    ThreadPool(uint32_t Size = std::thread::hardware_concurrency())
		: mDone(false)
	{
		for (uint32_t i = 0; i < Size/2; i++)
			mThreads.push_back(std::thread(&ThreadPool::worker_thread, this));	
	}

    ~ThreadPool()
	{
    	mDone = true;	
		join_threads();	
	}
    
    template<typename T>
    std::future<typename std::result_of<T()>::type> submit(T Task)
    {
        typedef typename std::result_of<T()>::type TResult;
        std::packaged_task<TResult()> PackagedTask(std::move(Task));
        std::future<TResult> Result(PackagedTask.get_future());
        mQueue.push(std::move(PackagedTask));

        return Result;
    }
private:
    void worker_thread()
	{
		while (!mDone)
		{
			FunctionWrapper Task;
			if (mQueue.try_pop(Task))
				Task();
			else
				std::this_thread::yield();
		}
	}

	void join_threads()
	{
		for (std::size_t i = 0; i < mThreads.size(); i++)
		{
			if (mThreads[i].joinable())
				mThreads[i].join();
		}			
	}

// Variables
public:

private:
    std::atomic_bool mDone;
    SafeQueue<FunctionWrapper> mQueue;
    std::vector<std::thread> mThreads;    
};

