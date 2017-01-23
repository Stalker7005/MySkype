#include "Client.h"
#include <iostream>
#include "Logger.h"
#include "FileUtils.h"
#include "ProcessUtils.h"
#include "TCPSession.h"
using namespace Network;

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpointIterator) : 
m_ioService(io_service)
{
    DoConnect(endpointIterator);
}

void Client::OnRead(const std::shared_ptr<NetworkMessage>& message)
{
    std::cout << "Message readed" << std::endl;
}

void Client::Post(const std::shared_ptr<Network::NetworkMessage>& message)
{
    m_session->Post(message);
}

void Client::DoConnect(tcp::resolver::iterator endpointIterator)
{
    m_session = std::make_shared<Network::TCPSession>(1, m_ioService);
    auto message = Network::NetworkMessage::Create(Network::MessageType::PING);
    boost::asio::async_connect(m_session->GetSocket(), endpointIterator, [this](const boost::system::error_code& ec,
        boost::asio::ip::tcp::resolver::iterator iterator)
    {
        if (!ec)
        {
            m_session->Read(std::bind(&Client::OnRead, this, std::placeholders::_1));
        }
    });
}

int main(int argc, char* argv[])
{
    try
    {
        LOG_INIT();

        if (argc != 3)
        {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service ioService;

        tcp::resolver resolver(ioService);
        auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
        std::shared_ptr<Client> c = std::make_shared<Client>(ioService, endpoint_iterator);

        std::cout << "Sending ping" << std::endl;
        std::thread t([&ioService]() {ioService.run();});

        auto message = Network::NetworkMessage::Create(MessageType::PING);
        
        while (true)
        {
            c->Post(message);
        }
        t.join();

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    system("pause");
    return 0;
}