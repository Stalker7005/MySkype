#include <cstdlib>
#include <memory>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

#include "Blob.h"
#include "Serializer.h"
#include "NetworkMessage.h"
#include "Connection.h"

using boost::asio::ip::tcp;

class Client : public std::enable_shared_from_this<Client>
{
public:
    Client(boost::asio::io_service& io_service,
        tcp::resolver::iterator endpoint_iterator);

private:
    boost::asio::io_service& m_ioService;
    std::unique_ptr<Network::Connection> m_connection;

};