#include "Server.h"
#include <iostream>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <memory>
#include <utility>
#include <cstdint>
#include <unordered_map>
#include <string>
#include <sstream>

#include <boost/asio.hpp>
#include <boost/functional/hash.hpp>

#include "NetworkMessage.h"
#include "Blob.h"
#include "Serializer.h"
#include "Session.h"

using namespace NetworkUtils;
using boost::asio::ip::tcp;


Server::Server(boost::asio::io_service& ioService, const tcp::endpoint& endpoint) :
    m_acceptor(ioService, endpoint),
    m_socket(ioService)
{
    DoAccept();
}

void Server::DoAccept()
{
    m_acceptor.async_accept(m_socket,
        [this](boost::system::error_code ec)
    {
        if (!ec)
        {
            auto session = std::make_shared<Session>(std::move(m_socket));
            session->Start();
        }

        DoAccept();
    });
}


int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: chat_server <port> [<port> ...]\n";
            return 1;
        }

        boost::asio::io_service io_service;

        std::list<Server> servers;
        for (int i = 1; i < argc; ++i)
        {
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(io_service, endpoint);
        }

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    system("pause");
    return 0;
}


