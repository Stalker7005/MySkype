//// chat_server.cpp
//// ~~~~~~~~~~~~~~~
////
//// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
////
//// Distributed under the Boost Software License, Version 1.0. (See accompanying
//// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////
//
//#include <cstdlib>
//#include <deque>
//#include <iostream>
//#include <list>
//#include <memory>
//#include <set>
//#include <utility>
//#include <cstdint>
//#include <boost/asio.hpp>
//#include <boost/uuid/uuid.hpp>
//#include <unordered_map>
//#include "ChatMessage.h"
//
//using boost::asio::ip::tcp;
//
//class ClientsConteiner
//{
//public:
//    
//private:
//    
//};
//class Session: public std::enable_shared_from_this<Session>
//{
//public:
//    Session(tcp::socket socket)
//        : socket_(std::move(socket))
//    {
//    }
//
//    void Start()
//    {
//        /*room_.join(shared_from_this());*/
//        DoReadHeader();
//    }
//
//    void Deliver(const NetworkUtils::ChatMessage& msg)
//    {
//        /*bool write_in_progress = !write_msgs_.empty();*/
//        /*write_msgs_.push_back(msg);*/
//        if (!write_in_progress)
//        {
//            DoWrite();
//        }
//    }
//
//private:
//    void DoReadHeader()
//    {
//        auto self(shared_from_this());
//        boost::asio::async_read(socket_,
//            boost::asio::buffer(read_msg_.data(), NetworkUtils::ChatMessage::header_length),
//            [this, self](boost::system::error_code ec, std::size_t /*length*/)
//        {
//            if (!ec && read_msg_.decode_header())
//            {
//                DoReadBody();
//            }
//            else
//            {
//                /*room_.leave(shared_from_this());*/
//            }
//        });
//    }
//
//    void DoReadBody()
//    {
//        auto self(shared_from_this());
//        boost::asio::async_read(socket_,
//            boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
//            [this, self](boost::system::error_code ec, std::size_t /*length*/)
//        {
//            if (!ec)
//            {
//                /*room_.deliver(read_msg_);*/
//                DoReadHeader();
//            }
//            else
//            {
//                /*room_.leave(shared_from_this());*/
//            }
//        });
//    }
//
//    void DoWrite()
//    {
//       /* auto self(shared_from_this());
//        boost::asio::async_write(socket_,
//            boost::asio::buffer(write_msgs_.front().data(),
//                write_msgs_.front().length()),*/
//            [this, self](boost::system::error_code ec, std::size_t /*length*/)
//        {
//            if (!ec)
//            {
//                /* write_msgs_.pop_front();
//                 if (!write_msgs_.empty())
//                 {
//                     DoWrite();
//                 }*/
//            }
//            else
//            {
//                /*room_.leave(shared_from_this());*/
//            }
//        });
//    }
//
//    tcp::socket socket_;
//    NetworkUtils::ChatMessage read_msg_;
//   /* chat_message_queue write_msgs_;*/
//};
//
////----------------------------------------------------------------------
//
//class chat_server
//{
//public:
//    chat_server(boost::asio::io_service& io_service,
//        const tcp::endpoint& endpoint)
//        : acceptor_(io_service, endpoint),
//        socket_(io_service)
//    {
//        do_accept();
//    }
//
//private:
//    void do_accept()
//    {
//        acceptor_.async_accept(socket_,
//            [this](boost::system::error_code ec)
//        {
//            if (!ec)
//            {
//                std::make_shared<Session>(std::move(socket_), room_)->start();
//            }
//
//            do_accept();
//        });
//    }
//
//    tcp::acceptor acceptor_;
//    tcp::socket socket_;
//   /* chat_room room_;*/
//};

//----------------------------------------------------------------------

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