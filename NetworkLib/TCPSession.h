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
#include <memory>
#include <boost/asio.hpp>

#include "NetworkMessage.h"
#include "Blob.h"
#include "Serializer.h"
#include "RunningContext.h"

class TCPSession : public ThreadsUtils::RunningContext,
                   public std::enable_shared_from_this<TCPSession>
{
public:
    using TSocket = boost::asio::ip::tcp::socket;
    using TIOService = boost::asio::io_service;

public:
    TCPSession(TIOService& ioService);

    void Write(const std::shared_ptr<NetworkUtils::NetworkMessage>& message);
    TSocket& GetSocket();

protected:
    void CloseConnecton();

    virtual bool StartInternal() override;
    virtual bool StopInternal() override;
    virtual bool IsCanStart() override;

private:
    void DoReadHeader();

    void DoReadBody(const std::shared_ptr<NetworkUtils::Header>& header);
    void DoWriteHeader();

    void DoWriteBody(const std::shared_ptr<NetworkUtils::NetworkMessage>& outMsg);

    void OnPing()
    {
        auto message = NetworkUtils::NetworkMessage::Create(NetworkUtils::MessageType::PONG);
        std::cout << "Pong" << std::endl;

        Write(message);
    }
private:
    TIOService& m_ioService;
    TSocket m_socket;

private:
    std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>> m_outputMessages;
    std::shared_ptr<Serialization::Blob> m_inMsgHeaderBlob;
    std::shared_ptr<Serialization::Blob> m_inMsgBodyBlob;
    std::shared_ptr<Serialization::Blob> m_outMsgBlob;
    std::unique_ptr<Serialization::Serializer> m_serializer;
};