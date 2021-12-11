#include "SafeQueue.hpp"

/************************************************************/
// template <typename T>
// SafeQueue<T>::SafeQueue()
// {

// }
/************************************************************/
// template <typename T>
// void SafeQueue<T>::push(T Value)
// {
//     std::shared_ptr<T> Data(std::make_shared<T>(std::move(Value)));
//     std::lock_guard<std::mutex> Lock(mMutex);
//     mQueue.push(Data);
//     mCondVar.notify_one();
// }
/************************************************************/
template <typename T>
std::shared_ptr<T> SafeQueue<T>::wait_and_pop()
{
    std::unique_lock<std::mutex> Lock(mMutex);
    mCondVar.wait(Lock, [this] {
        return !mQueue.empty();
    });

    std::shared_ptr<T> Ref = mQueue.front();
    mQueue.pop();

    return Ref;
}
/************************************************************/
template <typename T>
std::shared_ptr<T> SafeQueue<T>::try_pop()
{
    std::lock_guard<std::mutex> Lock(mMutex);
    if (mQueue.empty())
        return std::shared_ptr<T>();

    std::shared_ptr<T> Ref = mQueue.front();
    mQueue.pop();
    return Ref;
}
/************************************************************/
template <typename T>
void SafeQueue<T>::wait_and_pop(T &Value)
{
    std::unique_lock<std::mutex> Lock(mMutex);
    mCondVar.wait(Lock, [this](){
        return !mQueue.empty();
    });

    Value = std::move(*mQueue.front());
    mQueue.pop();
}
/************************************************************/
// template <typename T>
// bool SafeQueue<T>::try_pop(T &Value)
// {
//     std::lock_guard<std::mutex> Lock(mMutex);
//     if (mQueue.empty())
//         return false;

//     Value = std::move(*mQueue.front());
//     mQueue.pop();
//     return true;
// }
/************************************************************/
template <typename T>
bool SafeQueue<T>::empty()
{
    std::lock_guard<std::mutex> Lock(mMutex);
    return mQueue.empty();
}
/************************************************************/

/************************************************************/

/************************************************************/