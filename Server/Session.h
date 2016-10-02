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

#include <boost/asio.hpp>

#include "NetworkMessage.h"
#include "Blob.h"
#include "Serializer.h"

class Session : public std::enable_shared_from_this<Session>
{
public:
    using TSocket = boost::asio::ip::tcp::socket;


public:
    Session(TSocket socket);

    void Start();

    void Deliver(const std::shared_ptr<NetworkUtils::NetworkMessage>& message);

private:
    void DoReadHeader();

    void DoReadBody(std::uint64_t bodySize);
    void DoWriteHeader();

    void DoWriteBody();

    void OnPing()
    {
        auto message = NetworkUtils::NetworkMessage::Create(NetworkUtils::NetworkMessage::Type::PONG);
        std::cout << "Pong" << std::endl;

        Deliver(message);
    }

private:
    std::shared_ptr<Serialization::Blob> m_inMsgHeaderBlob;
    std::shared_ptr<Serialization::Blob> m_inMsgBodyBlob;
    std::shared_ptr<Serialization::Blob> m_outMsgBlob;
    std::unique_ptr<Serialization::Serializer> m_serializer;

    bool m_writeInProgress;
    TSocket m_socket;

    std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>> m_outputMessages;
};