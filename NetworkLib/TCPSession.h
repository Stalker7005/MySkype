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
#include "Session.h"

namespace Network {
class TCPSession : public Session,
    public std::enable_shared_from_this<TCPSession>
{
public:
    using TSocket = boost::asio::ip::tcp::socket;
    using TIOService = boost::asio::io_service;

public:
    TCPSession(NetworkUtils::TSessionId sessionId, TIOService& ioService);
    ~TCPSession();

public:
    void Post(const std::shared_ptr<NetworkUtils::NetworkMessage>& message) override;
    void Read(TCallback callback) override;
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

        Post(message);
    }

private:
    TIOService& m_ioService;
    TSocket m_socket;
    Session::TCallback m_readCallback;

private:
    std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>> m_outputMessages;
    std::shared_ptr<Serialization::Blob> m_inMsgHeaderBlob;
    std::shared_ptr<Serialization::Blob> m_inMsgBodyBlob;
    std::shared_ptr<Serialization::Blob> m_outMsgBlob;
    std::unique_ptr<Serialization::Serializer> m_serializer;
};
}
