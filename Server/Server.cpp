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
#include "TCPSession.h"
#include "Logger.h"

Server::Server(boost::asio::io_service& ioService, const boost::asio::ip::tcp::endpoint& endpoint) :
    m_acceptor(ioService, endpoint)
{
    DoAccept();
}

void Server::DoAccept()
{
    auto session = std::make_shared<Network::TCPSession>(1, m_ioService);

    m_acceptor.async_accept(session->GetSocket(),
        [this, session](boost::system::error_code ec)
    {
        if (!ec)
        {
            session->Start();
        }
        else
        {
            LOG_ERR("Can't create client session. Boost error:[%s]", ec.message());
        }

        DoAccept();
    });
}


int main(int argc, char* argv[])
{
    try
    {
        LOG_INIT();

        if (argc < 2)
        {
            std::cerr << "Usage: chat_server <port> [<port> ...]\n";
            return 1;
        }

        boost::asio::io_service io_service;

        std::list<Server> servers;
        for (int i = 1; i < argc; ++i)
        {
            
            servers.emplace_back(io_service, endpoint);
        }
        std::shared_ptr<boost::asio::io_service> ioService;
        ioService.reset(new boost::asio::io_service);

        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), std::atoi(argv[i]));
        auto session = std::make_shared<Network::TCPSession>(1, *ioService);
        auto message = NetworkUtils::NetworkMessage::Create(NetworkUtils::MessageType::PING);
        std::cout << "Sending ping" << std::endl;



        std::thread t([&ioService]() {ioService->run();});
        t.join();
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    system("pause");
    return 0;
}
