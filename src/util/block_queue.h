#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class BlockQueue
{
public:
    BlockQueue(size_t max_size = 1000) : max_size_(max_size) {}

    void setMaxSize(size_t max_size)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        max_size_ = max_size;
    }

    void push(const T& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        not_full_.wait(lock, [this] { return queue_.size() < max_size_; });
        queue_.push(item);
        not_empty_.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        not_empty_.wait(lock, [this] { return !queue_.empty(); });
        T item = queue_.front();
        queue_.pop();
        not_full_.notify_one();
        return item;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    size_t max_size_;
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
};