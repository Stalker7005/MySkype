#pragma once
#include <memory>
#include <thread>
#include <vector>
#include "RunningContext.h"

namespace boost 
{
    namespace asio 
    {
        class io_service;
    }
}

namespace Network {
class IoServiceThreadsPoolManager: public ThreadsUtils::RunningContext,
                                   public std::enable_shared_from_this<IoServiceThreadsPoolManager>
{
public:
    static IoServiceThreadsPoolManager& GetInstance();
    std::shared_ptr<boost::asio::io_service> GetIoService();
    boost::asio::io_service& Get();

protected:
    bool StartInternal() override;
    bool StopInternal() override;
    bool IsCanStart() override;

private:
    IoServiceThreadsPoolManager();
    ~IoServiceThreadsPoolManager();

    IoServiceThreadsPoolManager(const IoServiceThreadsPoolManager&) = delete;
    IoServiceThreadsPoolManager(IoServiceThreadsPoolManager&&) = delete;

    IoServiceThreadsPoolManager& operator=(const IoServiceThreadsPoolManager&) = delete;
    IoServiceThreadsPoolManager& operator=(IoServiceThreadsPoolManager&&) = delete;

private:
    std::shared_ptr<boost::asio::io_service> m_ioService;
    std::vector<std::thread> m_threads;
    void* m_work;
};
}

