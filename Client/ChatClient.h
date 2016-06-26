#include <cstdint>
#include <deque>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include "ChatMessage.h"

namespace Clients {
class ChatClient
{
public:
    using TIOService = boost::asio::io_service;
    using TEndPointIter = boost::asio::ip::tcp::resolver::iterator;
    using TTCPSocket = boost::asio::ip::tcp::socket;

public:
    ChatClient(TIOService& io_service);
    ~ChatClient();

public:
    ChatClient(const ChatClient&) = delete;
    ChatClient& operator=(const ChatClient&) = delete;

public:
    void Connect(const std::string& host, const std::string& port);
    void Close();

    void PostMessage(const NetworkUtils::ChatMessage& message);
    NetworkUtils::ChatMessage GetLastMessage();

    void PostMessages(const std::deque<NetworkUtils::ChatMessage>& messages);
    std::deque<NetworkUtils::ChatMessage> GetMessages();

private:
    TIOService& io_service;
    TTCPSocket tpcSocket;
    std::unique_ptr<TIOService::strand> m_strand;
    std::deque<NetworkUtils::ChatMessage> inputMessagesQueue;
    std::deque<NetworkUtils::ChatMessage> outputMessagesQueue;
};
}