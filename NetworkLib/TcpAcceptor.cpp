#include "TcpAcceptor.h"

namespace Network {

TcpAcceptor::TcpAcceptor(const std::shared_ptr<boost::asio::io_service>& ioService, NetworkUtils::TTcpSocket socket, const Endpoint& endpoint, TTcpCallback callback) : TcpSessionRole(ioService, std::move(socket))
, m_callback(callback)
, m_acceptor(*ioService)
{
    auto asioEndpoint = Endpoint::TTcpEndpoint();
    endpoint.Get(asioEndpoint);
    m_acceptor.bind(asioEndpoint);
}

void TcpAcceptor::Invoke()
{
    m_acceptor.async_accept(m_socket, m_callback);
}

}
