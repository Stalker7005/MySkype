#include "Server.h"
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
#include "Serealizer.h"

using boost::asio::ip::tcp;



class Session: public IUser,
               public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, std::shared_ptr<UsersGroup>& users): 
    m_socket(std::move(socket)),
    m_users(users),
    m_serializer(std::make_shared<Serialization::Serializer>(Serialization::Serializer::Type::BINARY))
    {

    }

    void Start()
    {
        DoReadHeader();
    }

    void Deliver(const std::shared_ptr<NetworkUtils::NetworkMessage>& message) override
    {
        bool write_in_progress = !m_ouputMessages.empty();
        m_ouputMessages.emplace_back(message);

        if (!m_writeInProgress)
        {
            DoWrite();
        }
    }

private:
    void DoReadHeader()
    {
        auto headerSize = NetworkUtils::NetworkMessage::GetHeaderSize();
        auto self(shared_from_this());
        boost::asio::async_read(m_socket,
            m_header, boost::asio::transfer_exactly(headerSize),
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                auto headerMessage = Deserialize(m_header, NetworkUtils::NetworkMessage::Type::HEADER);
                auto bodySize = headerMessage->GetMessageSize();
                auto messageType = headerMessage->GetType();
                DoReadBody(bodySize, messageType);
            }
            else
            {
                //Leave logic
            }
        });
    }

    void DoReadBody(std::uint64_t bodySize, NetworkUtils::NetworkMessage::Type msgType)
    {
        auto self(shared_from_this());
        boost::asio::async_read(m_socket,
            m_body, boost::asio::transfer_exactly(bodySize),
            [this, self, msgType](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                auto resultMessage = Deserialize(m_body, msgType);

                DoReadHeader();
            }
            else
            {
                //Leave logic
            }
        });
    }

    void DoWrite()
    {
        auto message = m_ouputMessages.front();
        auto& writeBuf = boost::asio::streambuf();
        auto& buf = Serialize(message, writeBuf);

        auto self(shared_from_this());
        boost::asio::async_write(m_socket,
            buf,
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                m_ouputMessages.pop_front();
                if (!m_ouputMessages.empty())
                {
                    DoWrite();
                }
            }
            else
            {
                //Leave logic
            }
        });
    }

    boost::asio::streambuf& Serialize(const std::shared_ptr<NetworkUtils::NetworkMessage>& message, boost::asio::streambuf& buf)
    {
        std::ostream outputArchiveStream(&buf);
        cereal::BinaryOutputArchive outputArchive(outputArchiveStream);
        outputArchive(message);

        return buf;
    }

    std::shared_ptr<NetworkUtils::NetworkMessage> Deserialize(boost::asio::streambuf& data, NetworkUtils::NetworkMessage::Type type)
    {
        std::stringstream inputStream;
        inputStream << &data;

        cereal::BinaryInputArchive inputArchive(inputStream);
        auto messagePtr = NetworkUtils::NetworkMessage::Create(type);
        inputArchive(messagePtr);

        return messagePtr;
    }

private:

    boost::asio::streambuf m_header;
    boost::asio::streambuf m_body;

    std::shared_ptr<UsersGroup>& m_users;
    bool m_writeInProgress;
    tcp::socket m_socket;
    std::shared_ptr<Serialization::Serializer> m_serializer;

    std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>> m_ouputMessages;
    std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>> m_inputMessages;
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

    return 0;
}