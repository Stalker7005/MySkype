#pragma once
#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

namespace ThreadsUtils {
template<typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue()
    {}
    ~ThreadSafeQueue()
    {}
    void Push(T value)
    {
        auto data = std::make_shared<T>(std::move(value));
        std::lock_guard<std::mutex> guard(m_mutex);
        m_queue.push(data);
        m_dataCond.notify_one();
    }
    bool TryPop(T& value)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (m_queue.empty())
        {
            return false;
        }
        value = std::move(*m_queue.front());
        m_queue.pop();

        return true;
    }
    std::shared_ptr<T> TryPop()
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (m_queue.empty())
        {
            return std::shared_ptr<T>();
        }
        auto res = m_queue.front();
        m_queue.pop();
        return res;
    }
    void WaitAndPop(T& value)
    {
        std::unique_lock<std::mutex> guard(m_mutex);
        m_dataCond.wait(guard, [] {return !m_queue.empty();});
        value = std::move(*m_queue.front());
        m_queue.pop();
    }
    std::shared_ptr<T> WaitAndPop()
    {
        std::unique_lock<std::mutex> guard(m_mutex);
        m_dataCond.wait(guard, [] {return !m_queue.empty();});
        auto value = std::move(*m_queue.front());
        m_queue.pop();

        return value;
    }
    bool Empty()
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        return m_queue.empty();
    }
private:
    std::mutex m_mutex;
    std::queue<std::shared_ptr<T>> m_queue;
    std::condition_variable m_dataCond;
};
}

