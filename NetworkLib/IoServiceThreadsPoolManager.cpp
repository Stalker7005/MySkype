#include "IoServiceThreadsPoolManager.h"
#include <boost/asio/io_service.hpp>

namespace Network {

Network::IoServiceThreadsPoolManager& IoServiceThreadsPoolManager::GetInstance()
{
    static IoServiceThreadsPoolManager ioServiceThreadManager;

    return ioServiceThreadManager;
}

IoServiceThreadsPoolManager::IoServiceThreadsPoolManager()
: m_work(nullptr)
{
    m_ioService.reset(new boost::asio::io_service);
}

IoServiceThreadsPoolManager::~IoServiceThreadsPoolManager()
{}

bool IoServiceThreadsPoolManager::StartInternal()
{
    auto numThreads = std::thread::hardware_concurrency();
    m_work = new boost::asio::io_service::work(*m_ioService);

    for (decltype(numThreads) i = 0; i < numThreads; ++i)
    {
        auto thread = std::thread(std::bind(&boost::asio::io_service::run, m_ioService));
        m_threads.emplace_back()
    }
}

bool IoServiceThreadsPoolManager::StopInternal()
{
    
}

bool IoServiceThreadsPoolManager::IsCanStart()
{
    return m_ioService != nullptr;
}

}

