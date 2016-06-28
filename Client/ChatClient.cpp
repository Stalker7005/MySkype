#include "ChatClient.h"
#include <cstring>
using namespace boost::asio;
namespace Clients {

ChatClient::ChatClient(TIOService& io_service):
io_service(io_service),
strand(std::make_unique<TIOService::strand>(io_service)),
tcpSocket(io_service)
{

}

ChatClient::~ChatClient()
{

}

void ChatClient::Connect(const std::string& host, const std::string& port)
{
    TTCPResolver resolver(io_service);
    auto endPointIter = resolver.resolve({ host, port });
    DoConnect(endPointIter);
}

void ChatClient::Close()
{
    io_service.post([this]() {tcpSocket.close();});
}

void ChatClient::PostMessage(const NetworkUtils::ChatMessage& message)
{

}

NetworkUtils::ChatMessage ChatClient::GetFirsttMessage()
{
    auto value = outputMessagesQueue.back();
    outputMessagesQueue.pop_front();
    return value;
}

void ChatClient::PostMessages(const std::deque<NetworkUtils::ChatMessage>& messages)
{

}

std::deque<NetworkUtils::ChatMessage> ChatClient::GetMessages()
{
    return outputMessagesQueue;
}

void ChatClient::DoConnect(TEndPointIter endPointIter)
{
    async_connect(tcpSocket, endPointIter, 
                            [this](boost::system::error_code ec, TEndPointIter iterator) {

                                if (!ec)
                                {
                                    DoReadHeader();
                                }
                            });
}

void ChatClient::DoReadHeader()
{
    auto handler = [this](boost::system::error_code ec, std::size_t lenght)
    {
        if (!ec)
        {
            DoWrite();
        }
    };

    async_read(tcpSocket, buffer(readBuf, sizeof(readBuf)), strand->wrap(handler));
}

void ChatClient::DoReadBody()
{
    
}

void ChatClient::DoWrite()
{
    auto handler = [this](boost::system::error_code ec, std::size_t lenght)
    {
        if (!ec)
        {
            DoReadHeader();
        }
    };

    std::strcpy(writeBuf, "Ping!");
    async_write(tcpSocket, buffer(writeBuf, sizeof(writeBuf)), strand->wrap(handler));

}

}

