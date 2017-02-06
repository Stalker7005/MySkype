#include "TCPSession.h"
#include "Logger.h"

using namespace Network;
using namespace boost::asio::ip;
namespace Network {
TCPSession::TCPSession(Network::TSessionId sessionId, TIOService& ioService)
: Session(sessionId),
m_socket(ioService),
m_inMsgBlob(std::make_shared<Blob>()),
m_outMsgBlob(std::make_shared<Blob>()),
m_serializer(std::make_unique<Serializer>()),
m_ioService(ioService),
m_sendStrand(ioService),
m_recvStrand(ioService)
{
}

TCPSession::~TCPSession()
{}

void TCPSession::Post(const std::shared_ptr<Blob>& blob)
{
    auto handler = [this, blob]()
    {
        m_outputMessages.emplace_back(blob);
        if (!m_outputMessages.empty())
        {
            DoWrite();
        }
    };

    m_ioService.post(m_sendStrand.wrap(handler));
}

void TCPSession::DoReadHeader()
{
    auto headerSize = Network::NetworkMessage::GetHeaderSize();
    m_inMsgBlob->Resize(headerSize);
    auto self = shared_from_this();

    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_inMsgBlob->GetData(), headerSize),
        [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec)
        {
            auto message = Network::NetworkMessage::Create(MessageType::BASE);
            message->DeserializeBlob(m_inMsgBlob);

            DoReadBody(message);
        }
        else
        {
            LOG_ERR("Can't read header! Boost err:[%s]", ec.message());
            CloseConnecton();
        }
    });
}

void TCPSession::DoReadBody(const std::shared_ptr<Network::NetworkMessage>& message)
{
    m_inMsgBlob->Clear();

    auto messageSize = message->GetMessageSize();
    m_inMsgBlob->Resize(messageSize);

    auto self = shared_from_this();
    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_inMsgBlob->GetData(), messageSize),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            FireRecv(m_inMsgBlob);
            DoReadHeader();
        }
        else
        {
            LOG_ERR("Can't read body. Boost err:[%s]", ec.message());
            CloseConnecton();
        }
    });
}

void TCPSession::DoWrite()
{
    auto blob = m_outputMessages.front();
    auto size = blob->GetSize();
    auto self = shared_from_this();
    boost::asio::async_write(m_socket,
        boost::asio::buffer(blob->GetData(), size),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
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
            LOG_ERR("Can't write body. Boost err:[%s]", ec.message());
            CloseConnecton();
        }
    });
}

bool TCPSession::StartInternal()
{
    auto self = shared_from_this();
    auto handler = [this, self]()
    {
        DoReadHeader();
    };

    m_ioService.post(m_recvStrand.wrap(handler));

    return true;
}

bool TCPSession::StopInternal()
{
    CloseConnecton();
    m_outputMessages.clear();

    return true;
}

bool TCPSession::IsCanStart()
{
    return m_socket.is_open();
}

void TCPSession::CloseConnecton()
{
    if (m_socket.is_open())
    {
        {
            boost::system::error_code error;
            m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
            if (error)
            {
                LOG_WARN("Error can't shutdown socket! Error:%s", error.message());
            }
        }
        
    
        {
            boost::system::error_code error;
            m_socket.close(error);
            if (error)
            {
                LOG_WARN("Error can't close socket! Erorr:%s", error.message());
            }
        }

        FireClose(GetId());
    }
}

TCPSession::TSocket& TCPSession::GetSocket()
{
    return m_socket;
}

}


