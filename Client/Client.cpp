#include "Client.h"
#include <iostream>
#include "Logger.h"
#include "FileUtils.h"
#include "ProcessUtils.h"
#include "TCPSession.h"
#include "Serializer.h"

using namespace Network;

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpointIterator) : 
m_ioService(io_service),
m_connection(std::make_shared<Connection>())
{
    auto session = std::make_shared<Network::TCPSession>(Session::MAIN_TCP_SESSION, m_ioService);
    
    boost::asio::async_connect(session->GetSocket(), endpointIterator, [this, session](const boost::system::error_code& ec,
        boost::asio::ip::tcp::resolver::iterator iterator)
    {
        if (!ec)
        {
            m_connection->AddSession(session);
            m_connection->StartSessions();
        }
    });
}

void Client::OnSendData(Network::TSessionId id, const std::shared_ptr<Blob>& blob)
{
    std::cout << "Session id:" << id << std::endl;
    std::cout << "Blob data:" << blob->GetData() << std::endl;
}

void Client::Post(Network::TSessionId id, const std::shared_ptr<Blob>& blob)
{
    m_connection->SendData(id, blob);
}

bool Client::StartInternal()
{
    m_readConnection = m_connection->AddSendListener(std::bind(&Client::OnSendData, shared_from_this(), std::placeholders::_1, std::placeholders::_2));

    return true;
}

bool Client::StopInternal()
{
    m_connection->StopSessions();
    m_readConnection.release();
    return true;
}

bool Client::IsCanStart()
{
    return true;
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
        auto c = std::make_shared<Client>(ioService, endpoint_iterator);

        std::cout << "Sending ping" << std::endl;
        std::thread t([&ioService]() {ioService.run();});

        auto message = Network::NetworkMessage::Create(MessageType::PING);
        auto blob = message->SerializeBlob();
        c->Start();

        while (true)
        {
            c->Post(Session::MAIN_TCP_SESSION, blob);
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