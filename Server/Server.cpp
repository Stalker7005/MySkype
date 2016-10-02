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
#include "NetworkDefs.h"
#include "IUser.h"
#include "UsersGroup.h"
#include "Blob.h"
#include "Serializer.h"

using namespace NetworkUtils;
using boost::asio::ip::tcp;


class Session: public IUser,
               public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, std::shared_ptr<UsersGroup>& users): 
    m_socket(std::move(socket)),
    m_users(users),
    m_inMsgHeaderBlob(std::make_shared<Serialization::Blob>()),
    m_inMsgBodyBlob(std::make_shared<Serialization::Blob>()),
    m_outMsgBlob(std::make_shared<Serialization::Blob>()),
    m_serializer(std::make_unique<Serialization::Serializer>())
    {

    }

    void Start()
    {
        DoReadHeader();
    }

    void Deliver(const std::shared_ptr<NetworkUtils::NetworkMessage>& message) override
    {
        bool write_in_progress = !m_outputMessages.empty();
        m_outputMessages.emplace_back(message);

        /*if (!m_writeInProgress)
        {*/
            DoWriteHeader();
        /*}*/
    }

private:
    void DoReadHeader()
    {
        auto headerSize = NetworkUtils::NetworkMessage::GetHeaderSize();
        m_inMsgHeaderBlob->Reserve(headerSize);
        auto self = shared_from_this();

        boost::asio::async_read(m_socket,
            boost::asio::buffer(m_inMsgHeaderBlob->GetData(), headerSize),
            [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::cout << "Header size:" << length << std::endl;
                
                //Deseralize header
                auto headerInfo = NetworkMessage::ParseHeader(m_inMsgHeaderBlob->GetData());
                //TODO add message handling
                auto messageType = headerInfo.first;
                auto messageSize = headerInfo.second;
                

                DoReadBody(messageSize);
            }
            else
            {
                //Leave logic
            }
        });
    }

    void DoReadBody(std::uint64_t bodySize)
    {
        m_inMsgBodyBlob->Reserve(bodySize);
        auto self = shared_from_this();
        boost::asio::async_read(m_socket,
            boost::asio::buffer(m_inMsgBodyBlob->GetData(), bodySize),
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                OnPing();
                DoReadHeader();
            }
            else
            {
                //Leave logic
            }
        });
    }

    void DoWriteHeader()
    {
        auto outMsg = m_outputMessages.front();
        m_serializer->Serialize(m_outMsgBlob, outMsg);
        auto self = shared_from_this();
        outMsg->SetMessageSize(m_outMsgBlob->Size());

        boost::asio::async_write(m_socket,
            boost::asio::buffer(outMsg->GetHeader(), outMsg->GetHeaderSize()),
            [this, self](boost::system::error_code ec, std::size_t /*lenght*/)
        {
            if (!ec)
            {
                DoWriteBody();
            }
        }
        );
    }

    void DoWriteBody()
    {
        auto self = shared_from_this();
        boost::asio::async_write(m_socket,
            boost::asio::buffer(m_outMsgBlob->GetData(), m_outMsgBlob->Size()),
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                m_outputMessages.pop_front();
                if (!m_outputMessages.empty())
                {
                    DoWriteHeader();
                }
            }
            else
            {
                //m_socket.close();
                std::cout << "Fuck DoWrite" << std::endl;
            }
        });
    }

    void OnPing()
    {
        auto message = NetworkMessage::Create(NetworkMessage::Type::PONG);
        std::cout << "Pong" << std::endl;

        Deliver(message);
    }

private:
    std::shared_ptr<Serialization::Blob> m_inMsgHeaderBlob;
    std::shared_ptr<Serialization::Blob> m_inMsgBodyBlob;
    std::shared_ptr<Serialization::Blob> m_outMsgBlob;
    std::unique_ptr<Serialization::Serializer> m_serializer;

    std::shared_ptr<UsersGroup>& m_users;
    bool m_writeInProgress;
    tcp::socket m_socket;

    std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>> m_outputMessages;
};

class chat_server
{
public:
    chat_server(boost::asio::io_service& ioService,
        const tcp::endpoint& endpoint)
        : m_acceptor(ioService, endpoint),
        m_socket(ioService),
        m_usersGroup(std::make_shared<UsersGroup>())
    {
        DoAccept();
    }

private:
    void DoAccept()
    {
        m_acceptor.async_accept(m_socket,
            [this](boost::system::error_code ec)
        {
            if (!ec)
            {
                auto session = std::make_shared<Session>(std::move(m_socket), m_usersGroup);
                session->Start();
            }

            DoAccept();
        });
    }

private:
    tcp::acceptor m_acceptor;
    tcp::socket m_socket;
    std::shared_ptr<UsersGroup> m_usersGroup;
};

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

        std::list<chat_server> servers;
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