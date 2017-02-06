#include "IoServiceThreadsPoolManager.h"
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>

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
        auto thread = std::thread(boost::bind(&boost::asio::io_service::run, m_ioService));
        m_threads.emplace_back(std::move(thread));
    }

    return true;
}

bool IoServiceThreadsPoolManager::StopInternal()
{
    if (m_work)
    {
        delete reinterpret_cast<boost::asio::io_service::work*>(m_work);
    }

    for (auto i = 0; i < m_threads.size(); ++i)
    {
        m_threads[i].join();
    }

    return true;
}

bool IoServiceThreadsPoolManager::IsCanStart()
{
    return m_ioService != nullptr;
}

std::shared_ptr<boost::asio::io_service> IoServiceThreadsPoolManager::GetIoService()
{
    return m_ioService;
}

boost::asio::io_service& IoServiceThreadsPoolManager::Get()
{
    return *m_ioService;
}

}

