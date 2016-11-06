#include "ThreadPool.h"
#include <functional>
namespace ThreadsUtils {

ThreadPool& ThreadPool::Get()
{
    static ThreadPool instance;

    return instance;
}

ThreadPool::ThreadPool():
m_done(false),
m_joiner(m_threads)
{
    try
    {
        auto threadsCount = std::thread::hardware_concurrency();
        for (decltype(threadsCount) i = 0; i < threadsCount; ++i)
        {
            m_threads.push_back(std::thread(&ThreadPool::WorkerThread, this));
        }
    }
    catch (const std::exception&)
    {
        m_done = true;
        throw;
    }

}

ThreadPool::~ThreadPool()
{
    m_done = true;
}

void ThreadPool::WorkerThread()
{
    while (!m_done)
    {
        std::function<void()> task;
        if (m_workQueue.TryPop(task))
        {
            task();
        }
        else
        {
            std::this_thread::yield();
        }
    }
}

}


