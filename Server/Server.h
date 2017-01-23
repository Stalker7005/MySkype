#include <boost/asio.hpp>
#include <memory>
#include "TCPSession.h"

class Server
{
public:
    using TSocket = boost::asio::ip::tcp::socket;
    using TEndpoint = boost::asio::ip::tcp::endpoint;
    using TAcceptor = boost::asio::ip::tcp::acceptor;
    using TIOService = boost::asio::io_service;

public:
    Server(TIOService& ioService,
        const TEndpoint& endpoint);

private:
    void DoAccept();

private:
    std::shared_ptr<Network::TCPSession> m_session;
    TAcceptor m_acceptor;
    TIOService& m_ioService;
};