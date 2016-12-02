#pragma once
#include "TcpSessionRole.h"
#include "Endpoint.h"

namespace Network {
class TcpAcceptor : public TcpSessionRole
{
public:
    using TTcpAcceptor = boost::asio::ip::tcp::acceptor;
    using TTcpCallback = std::function<void(boost::system::error_code ec)>;

public:
    TcpAcceptor(const std::shared_ptr<boost::asio::io_service>& ioService, NetworkUtils::TTcpSocket socket, const Endpoint& endpoint, TTcpCallback callback);
    virtual void Invoke() override;

private:
    TTcpAcceptor m_acceptor;
    TTcpCallback m_callback;
};
}
