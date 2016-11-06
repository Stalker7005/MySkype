#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <functional>

#include "ThreadsJoiner.h"
#include "ThreadSafeQueue.h"

namespace ThreadsUtils {
class ThreadPool
{
public:
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

public:
    static ThreadPool& Get();

    template<typename TaskType>
    void PostTask(TaskType task);
    
protected:
    ThreadPool();

private:
    void WorkerThread();

private:
    std::atomic_bool m_done;
    ThreadSafeQueue<std::function<void()>> m_workQueue;
    std::vector<std::thread> m_threads;
    ThreadsJoiner m_joiner;

};

template<typename TaskType>
void ThreadsUtils::ThreadPool::PostTask(TaskType task)
{
    m_workQueue.Push(std::function<void()>(task));
}

}

