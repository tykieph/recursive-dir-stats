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
    
    bool try_pop(T &Value)
    {
        std::lock_guard<std::mutex> Lock(mMutex);
        if (mQueue.empty())
            return false;

        Value = std::move(*mQueue.front());
        mQueue.pop();
        return true;        
    }

    bool empty()
    {
        std::lock_guard<std::mutex> Lock(mMutex);
        return mQueue.empty();        
    }
private:
    
// Variables
public:

private:
    std::mutex mMutex;
    std::condition_variable mCondVar;
    std::queue<std::shared_ptr<T>> mQueue;
};