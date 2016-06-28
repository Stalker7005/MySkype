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
    using TTCPResolver = boost::asio::ip::tcp::resolver;
    using TEndPointIter = TTCPResolver::iterator;
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
    NetworkUtils::ChatMessage GetFirsttMessage();

    void PostMessages(const std::deque<NetworkUtils::ChatMessage>& messages);
    std::deque<NetworkUtils::ChatMessage> GetMessages();

protected:
    void DoConnect(TEndPointIter endPointIter);
    void DoReadHeader();
    void DoReadBody();
    void DoWrite();

private:
    char readBuf[500];
    char writeBuf[500];
    TIOService& io_service;
    TTCPSocket tcpSocket;
    std::unique_ptr<TIOService::strand> strand;
    std::deque<NetworkUtils::ChatMessage> inputMessagesQueue;
    std::deque<NetworkUtils::ChatMessage> outputMessagesQueue;
};
}