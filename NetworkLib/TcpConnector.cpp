#include "TcpConnector.h"

namespace Network {

TcpConnector::TcpConnector(const std::shared_ptr<boost::asio::io_service>& ioService, NetworkUtils::TTcpSocket socket, const Endpoint& endpoint, TCallBack callback)
: TcpSessionRole(ioService, std::move(socket))
, m_callback(callback)
{
    auto asioIter = Endpoint::TTcpResolverIter();
    endpoint.Get(asioIter);
    m_iter = asioIter;
}

void TcpConnector::Invoke()
{
    boost::asio::async_connect(m_socket, m_iter, m_callback);
}

}

