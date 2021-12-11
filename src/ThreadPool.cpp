#include "ThreadPool.hpp"

/************************************************************/
ThreadPool::ThreadPool(uint32_t Size)
    : mDone(false), joiner(mThreads)
{
    for (uint32_t i = 0; i < Size; i++)
    {
        mThreads.push_back(
            std::thread(&ThreadPool::worker_thread, this));
    }
}
/************************************************************/
ThreadPool::~ThreadPool()
{
    mDone = true;
}
/************************************************************/
// std::future<typename std::result_of<TTask()>::type> ThreadPool::submit(TTask Task)
// {
//     typedef typename std::result_of<TTask()>::type TResult;
//     std::packaged_task<TResult()> PackagedTask(std::move(Task));
//     std::future<TResult> Result(PackagedTask.get_future());
//     mQueue.push(std::move(PackagedTask));

//     return Result;
// }

// template<typename T>
// void ThreadPool::submit(T Task)
// {
//     mQueue.push(std::function<void()>(Task));
// }
/************************************************************/
void ThreadPool::worker_thread()
{
    while (!mDone)
    {
        function_wrapper Task;
        if (mQueue.try_pop(Task))
        {
            Task();
        }
        else
        {
            std::this_thread::yield();
        }
    }
}
/************************************************************/
join_threads::join_threads(std::vector<std::thread>& _threads) :
    threads(_threads)
{
}
/************************************************************/
join_threads::~join_threads()
{
    for (std::size_t i = 0; i < threads.size(); i++)
    {
        if (threads[i].joinable())
            threads[i].join();
    }
}
/************************************************************/
