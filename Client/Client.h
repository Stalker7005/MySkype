#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "ChatMessage.h"

using boost::asio::ip::tcp;

typedef std::deque<NetworkUtils::ChatMessage> chat_message_queue;

class Client
{
public:
    Client(boost::asio::io_service& io_service,
        tcp::resolver::iterator endpoint_iterator);

    void Write(const NetworkUtils::ChatMessage& msg);
    void Close();

private:
    void DoConnect(tcp::resolver::iterator endpoint_iterator);
    void DoReadHeader();
    void DoReadBody();
    void DoWrite();

private:
    boost::asio::io_service& io_service;
    tcp::socket socket;
    NetworkUtils::ChatMessage read_msg_;
    chat_message_queue outputMessages;
};