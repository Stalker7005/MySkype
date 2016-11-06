#pragma once
#include <vector>
#include <thread>
namespace ThreadsUtils {
class ThreadsJoiner
{
public:
    ThreadsJoiner(std::vector<std::thread>& threads) :
        m_threads(threads)
    {}
    ~ThreadsJoiner()
    {
        for (auto i = 0; i < m_threads.size();++i)
        {
            if (m_threads[i].joinable())
            {
                m_threads[i].join();
            }

        }
    }

private:
    std::vector<std::thread>& m_threads;
};
}


