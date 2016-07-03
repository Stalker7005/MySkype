#include "Server.h"
#include <cstdlib>
#include <deque>
#include <iostream>
#include <memory>
#include <utility>
#include <cstdint>
#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/functional/hash.hpp>

#include "NetworkMessage.h"
#include "NetworkDefs.h"
#include "ChatMessage.h"
#include "IUser.h"
#include "UsersGroup.h"

using boost::asio::ip::tcp;



//class Session: public IUser,
//               public std::enable_shared_from_this<Session>
//{
//public:
//    Session(tcp::socket socket, UsersGroup& users): 
//    m_socket(std::move(socket)),
//    m_users(users)
//    {
//    }
//
//    void Start()
//    {
//        DoReadHeader();
//    }
//
//    void Deliver(const std::shared_ptr<NetworkUtils::NetworkMessage>& message) override
//    {
//        bool write_in_progress = !m_ouputMessages.empty();
//        m_ouputMessages.emplace_back(message);
//
//        if (!m_writeInProgress)
//        {
//            DoWrite();
//        }
//    }
//
//private:
//    void DoReadHeader()
//    {
//        auto self(shared_from_this());
//        boost::asio::async_read(m_socket,
//            boost::asio::buffer(m_inputMessages.data(), NetworkUtils::ChatMessage::header_length),
//            [this, self](boost::system::error_code ec, std::size_t /*length*/)
//        {
//            if (!ec)
//            {
//                DoReadBody();
//            }
//            else
//            {
//                //Leave logic
//            }
//        });
//    }
//
//    void DoReadBody()
//    {
//        auto self(shared_from_this());
//        boost::asio::async_read(m_socket,
//            boost::asio::buffer(m_inputMessages.body(), m_inputMessages.body_length()),
//            [this, self](boost::system::error_code ec, std::size_t /*length*/)
//        {
//            if (!ec)
//            {
//                /*room_.deliver(read_msg_);*/
//                DoReadHeader();
//            }
//            else
//            {
//                //Leave logic
//            }
//        });
//    }
//
//    void DoWrite()
//    {
//        auto self(shared_from_this());
//        boost::asio::async_write(m_socket,
//            boost::asio::buffer(m_ouputMessages.front().data(),
//                m_ouputMessages.front()->length()),
//            [this, self](boost::system::error_code ec, std::size_t /*length*/)
//        {
//            if (!ec)
//            {
//                m_ouputMessages.pop_front();
//                if (!m_ouputMessages.empty())
//                {
//                    DoWrite();
//                }
//            }
//            else
//            {
//                //Leave logic
//            }
//        });
//    }
//
//private:
//    UsersGroup& m_users;
//    bool m_writeInProgress;
//    tcp::socket m_socket;
//    
//    std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>> m_ouputMessages;
//    std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>> m_inputMessages;
//};

//----------------------------------------------------------------------

class chat_server
{
public:
    chat_server(boost::asio::io_service& ioService,
        const tcp::endpoint& endpoint)
        : m_acceptor(ioService, endpoint),
        m_socket(ioService),
        m_usersGroup(std::make_shared<UsersGroup>())
    {
        do_accept();
    }

private:
    void do_accept()
    {
        m_acceptor.async_accept(m_socket,
            [this](boost::system::error_code ec)
        {
            if (!ec)
            {
                /*auto session = std::make_shared<Session>(std::move(m_socket));
                session->Start();*/
            }

            do_accept();
        });
    }

    tcp::acceptor m_acceptor;
    tcp::socket m_socket;
    std::shared_ptr<UsersGroup> m_usersGroup;
};

int main(int argc, char* argv[])
{
   /* try
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
    }*/

    return 0;
}