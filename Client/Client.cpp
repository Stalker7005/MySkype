#include "Client.h"

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpointIterator) : 
io_service(io_service),
m_socket(io_service)
{
    DoConnect(endpointIterator);
}

void Client::Write(const std::shared_ptr<NetworkUtils::NetworkMessage>& msg)
{
    auto handler = [this, msg]()
    {
        bool writeInProgress = !m_outputMessages.empty();
        m_outputMessages.push_back(msg);
        if (!writeInProgress)
        {
            DoWrite();
        }
    };

    io_service.post(handler);
}

void Client::Close()
{
    io_service.post([this]() { m_socket.close(); });
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
    auto headerSize = NetworkUtils::NetworkMessage::GetHeaderSize();
    boost::asio::async_read(m_socket,
        m_header, boost::asio::transfer_exactly(headerSize),
        [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            auto headerMessage = Deserialize(m_header);
            auto messageSize = headerMessage->GetMessageSize();
            auto messageType = headerMessage->GetType();

            DoReadBody(messageSize, messageType);
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
    auto curMessage = m_outputMessages.front();
    auto& stream = Serialize(curMessage);
    
    boost::asio::streambuf outputBuf;
    
    boost::asio::async_write(m_socket,
        ,
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

boost::asio::streambuf& Client::Serialize(const std::shared_ptr<NetworkUtils::NetworkMessage>& message)
{

    std::ostream out()

    cereal::BinaryOutputArchive outputArchive(m_outputArhiveStream);
    outputArchive(message);
    
    return ;
}

std::shared_ptr<NetworkUtils::NetworkMessage> Client::Deserialize(boost::asio::streambuf& data)
{
    m_archiveStream << &data;
    cereal::BinaryInputArchive inputArchive(m_archiveStream);
    auto messagePtr = std::make_shared<NetworkUtils::NetworkMessage>();
    inputArchive(messagePtr);

    m_archiveStream.clear();
    m_archiveStream.str("");

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

        std::thread t([&io_service]() { io_service.run(); });

        /*while (std::cin.getline(line, NetworkUtils::ChatMessage::max_body_length + 1))
        {
            NetworkUtils::ChatMessage msg;
            msg.body_length(std::strlen(line));
            std::memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            c.Write(msg);
        }*/

        c.Close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}