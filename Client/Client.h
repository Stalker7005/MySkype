#include <cstdlib>
#include <memory>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "NetworkMessage.h"
#include <cereal/archives/binary.hpp>

using boost::asio::ip::tcp;



class Client
{
public:
    using TMessagesQueue = std::deque<std::shared_ptr<NetworkUtils::NetworkMessage>>;

public:
    Client(boost::asio::io_service& io_service,
        tcp::resolver::iterator endpoint_iterator);

    void Write(const std::shared_ptr<NetworkUtils::NetworkMessage>& msg);
    void Close();

private:
    void DoConnect(tcp::resolver::iterator endpoint_iterator);
    void DoReadHeader();
    void DoReadBody(std::uint64_t bodySize, NetworkUtils::NetworkMessage::Type type);
    void DoWrite();

    std::ostream& Serialize(const std::shared_ptr<NetworkUtils::NetworkMessage>& message);
    std::shared_ptr<NetworkUtils::NetworkMessage> Deserialize(boost::asio::streambuf& data);

private:
    boost::asio::io_service& io_service;
    

    boost::asio::streambuf m_header;
    boost::asio::streambuf m_body;

    tcp::socket m_socket;
    NetworkUtils::NetworkMessage m_inputMessage;
    TMessagesQueue m_outputMessages;
};