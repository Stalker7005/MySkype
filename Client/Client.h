#include <cstdlib>
#include <memory>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

#include "Blob.h"
#include "Serializer.h"
#include "NetworkMessage.h"

using boost::asio::ip::tcp;

class Client: public std::enable_shared_from_this<Client>
{
public:
    using TMessagesQueue = std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>>;

public:
    Client(boost::asio::io_service& io_service,
        tcp::resolver::iterator endpoint_iterator);

    void Write(const std::shared_ptr<NetworkUtils::NetworkMessage> msg);
    void Close();

private:
    void DoConnect(tcp::resolver::iterator endpoint_iterator);
    void DoReadHeader();
    void DoReadBody(std::uint64_t bodySize);
    void DoWriteBody();
    void DoWriteHeader();
    void OnPong();

private:
    boost::asio::io_service& m_io_service;
    std::unique_ptr<Serialization::Serializer> m_serializer;
    std::shared_ptr<Serialization::Blob> m_inMsgHeaderBlob;
    std::shared_ptr<Serialization::Blob> m_inMsgBodyBlob;
    std::shared_ptr<Serialization::Blob> m_outMsgBlob;

    tcp::socket m_socket;
    TMessagesQueue m_outputMessages;
};