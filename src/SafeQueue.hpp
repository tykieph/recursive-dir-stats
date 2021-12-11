#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <memory>

template<typename T>
class SafeQueue
{
// Methods
public:
    SafeQueue() {}
    ~SafeQueue() {}

    void push(T Value)
    {
        std::shared_ptr<T> Data(std::make_shared<T>(std::move(Value)));
        std::lock_guard<std::mutex> Lock(mMutex);
        mQueue.push(Data);
        mCondVar.notify_one();
    }
    
    std::shared_ptr<T> wait_and_pop();
    std::shared_ptr<T> try_pop();
    void wait_and_pop(T &Value);
    bool try_pop(T &Value)
    {
        std::lock_guard<std::mutex> Lock(mMutex);
        if (mQueue.empty())
            return false;

        Value = std::move(*mQueue.front());
        mQueue.pop();
        return true;        
    }
    bool empty();
private:
    
// Variables
public:

private:
    mutable std::mutex mMutex;
    std::condition_variable mCondVar;
    std::queue<std::shared_ptr<T>> mQueue;
};