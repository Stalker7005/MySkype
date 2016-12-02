#pragma once
#include "SessionRole.h"
#include "NetworkDefs.h"

namespace Network {
class TcpSessionRole: public SessionRole
{
public:
    TcpSessionRole(const std::shared_ptr<boost::asio::io_service>& ioService, NetworkUtils::TTcpSocket socket);

protected:
    NetworkUtils::TTcpSocket m_socket;
};
}

