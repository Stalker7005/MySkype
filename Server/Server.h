#include <boost/asio.hpp>
#include <memory>

class Server
{
public:
    using TSocket = boost::asio::ip::tcp::socket;
    using TEndpoint = boost::asio::ip::tcp::endpoint;
    using TAcceptor = boost::asio::ip::tcp::acceptor;

public:
    Server(boost::asio::io_service& ioService,
        const TEndpoint& endpoint);

private:
    void DoAccept();

private:
    TAcceptor m_acceptor;
    TSocket m_socket;
};