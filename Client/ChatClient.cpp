#include "ChatClient.h"
namespace Clients {

ChatClient::ChatClient(TIOService& io_service):
io_service(io_service),
m_strand(std::make_unique<TIOService::strand>(io_service)),
tpcSocket(io_service)
{

}

ChatClient::~ChatClient()
{

}

void ChatClient::Connect(const std::string& host, const std::string& port)
{

}

void ChatClient::Close()
{

}

void ChatClient::PostMessage(const NetworkUtils::ChatMessage& message)
{

}

NetworkUtils::ChatMessage ChatClient::GetLastMessage()
{
    return outputMessagesQueue.back();
}

void ChatClient::PostMessages(const std::deque<NetworkUtils::ChatMessage>& messages)
{

}

std::deque<NetworkUtils::ChatMessage> ChatClient::GetMessages()
{
    return outputMessagesQueue;
}

}

