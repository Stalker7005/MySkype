#pragma once
#include "TcpSessionRole.h"
#include "Endpoint.h"

namespace Network {
class TcpConnector : public TcpSessionRole
{
public:
    using TCallBack = std::function<void(boost::system::error_code, boost::asio::ip::tcp::resolver::iterator)>;
public:
    TcpConnector(const std::shared_ptr<boost::asio::io_service>& ioService, NetworkUtils::TTcpSocket socket, const Endpoint& endpoint, TCallBack callback);
    ~TcpConnector() = default;

public:
    void Invoke() override;

private:
    TCallBack m_callback;
    Endpoint::TTcpResolverIter m_iter;
};
}

