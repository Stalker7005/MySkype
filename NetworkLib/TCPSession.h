#pragma  once
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
    TCPSession(Network::TSessionId sessionId, TIOService& ioService);
    ~TCPSession();

public:
    void Post(const std::shared_ptr<Network::NetworkMessage>& message) override;
    void Read(TCallback callback) override;
    TSocket& GetSocket();

protected:
    void CloseConnecton();

    virtual bool StartInternal() override;
    virtual bool StopInternal() override;
    virtual bool IsCanStart() override;

private:
    void DoReadHeader();
    void DoReadBody(const std::shared_ptr<Network::NetworkMessage>& message);
    void DoWrite();

private:
    TIOService& m_ioService;
    TSocket m_socket;
    Session::TCallback m_readCallback;

private:
    std::deque<std::shared_ptr<Network::NetworkMessage>> m_outputMessages;
    std::shared_ptr<Blob> m_inMsgBlob;
    std::shared_ptr<Blob> m_outMsgBlob;
    std::unique_ptr<Serializer> m_serializer;
    boost::asio::strand m_sendStrand;
    boost::asio::strand m_recvStrand;
};
}
