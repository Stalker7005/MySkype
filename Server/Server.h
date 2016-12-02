#include <boost/asio.hpp>
#include <memory>

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
    TAcceptor m_acceptor;
    TIOService m_ioService;
};