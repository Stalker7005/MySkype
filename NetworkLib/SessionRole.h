#pragma once
#include "ISessionRole.h"
#include <memory>
#include <boost/asio.hpp>

namespace Network {
class SessionRole : public ISessionRole
{
public:
    SessionRole(const std::shared_ptr<boost::asio::io_service>& ioService);
    ~SessionRole() = default;
    
protected:
    std::shared_ptr<boost::asio::io_service> m_ioService;
};
}

