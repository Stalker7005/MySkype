#include "TcpSessionRole.h"

namespace Network {

TcpSessionRole::TcpSessionRole(const std::shared_ptr<boost::asio::io_service>& ioService, NetworkUtils::TTcpSocket socket) 
: SessionRole(ioService)
, m_socket(std::move(socket))
{
}

}

