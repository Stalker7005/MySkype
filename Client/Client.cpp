#include "Client.h"

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpointIterator) : 
m_io_service(io_service),
m_socket(io_service)
{
    DoConnect(endpointIterator);
}

void Client::Write(const std::shared_ptr<NetworkUtils::NetworkMessage> msg)
{
    m_io_service.post([this, msg]()
    {
        bool writeInProgress = !m_outputMessages.empty();
        m_outputMessages.push_back(msg);
        if (!writeInProgress)
        {
            DoWrite();
        }
    });
}

void Client::Close()
{
    m_io_service.post([this]() { m_socket.close(); });
}

void Client::DoConnect(tcp::resolver::iterator endpoint_iterator)
{
    boost::asio::async_connect(m_socket, endpoint_iterator,
        [this](boost::system::error_code ec, tcp::resolver::iterator)
    {
        if (!ec)
        {
            DoReadHeader();
        }
    });
}

void Client::DoReadHeader()
{
    char buf[1024];
    /*int headerSize = NetworkUtils::NetworkMessage::GetHeaderSize();*/
    boost::asio::async_read(m_socket,
        boost::asio::buffer(buf, 10),
        [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            /*auto headerMessage = Deserialize(m_header, NetworkUtils::NetworkMessage::Type::HEADER);
            auto messageSize = headerMessage->GetMessageSize();
            auto messageType = headerMessage->GetType();

            DoReadBody(messageSize, messageType);*/
        }
        else
        {
            m_socket.close();
        }
    });

}

void Client::DoReadBody(std::uint64_t bodySize, NetworkUtils::NetworkMessage::Type type)
{
    boost::asio::async_read(m_socket,
        m_body, boost::asio::transfer_exactly(bodySize),
        [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            DoReadHeader();
        }
        else
        {
            m_socket.close();
        }
    });
}

void Client::DoWrite()
{
    boost::asio::streambuf writingBuf;
    auto curMessage = m_outputMessages.front();
    /*Serialize(curMessage, writingBuf);*/
    char buf[1024];
    boost::asio::async_write(m_socket,
        boost::asio::buffer(buf), boost::asio::transfer_exactly(10),
        [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            m_outputMessages.pop_front();
            if (!m_outputMessages.empty())
            {
                DoWrite();
            }
        }
        else
        {
            m_socket.close();
        }
    });
}

boost::asio::streambuf& Client::Serialize(const std::shared_ptr<NetworkUtils::NetworkMessage>& message, boost::asio::streambuf& buf)
{
    /*cereal::BinaryOutputArchive outputArchive(outputArchiveStream);
    outputArchive(message);*/
    
    return buf;
}

std::shared_ptr<NetworkUtils::NetworkMessage> Client::Deserialize(boost::asio::streambuf& data, NetworkUtils::NetworkMessage::Type type)
{
    std::stringstream inputStream;
    inputStream << &data;

    cereal::BinaryInputArchive inputArchive(inputStream);
    auto messagePtr = NetworkUtils::NetworkMessage::Create(type);
    inputArchive(messagePtr);

    return messagePtr;
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
        Client c(io_service, endpoint_iterator);

        
        auto message = NetworkUtils::NetworkMessage::Create(NetworkUtils::NetworkMessage::Type::PING);
        c.Write(message);

        
        
        io_service.run();
        Sleep(5000);
        c.Close();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}