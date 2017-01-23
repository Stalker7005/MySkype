#include "TCPSession.h"
#include "Logger.h"

using namespace NetworkUtils;
using namespace boost::asio::ip;
namespace Network {
TCPSession::TCPSession(NetworkUtils::TSessionId sessionId, TIOService& ioService) 
: Session(sessionId),
  m_socket(ioService),
  m_inMsgBlob(std::make_shared<Blob>()),
  m_outMsgBlob(std::make_shared<Blob>()),
  m_serializer(std::make_unique<Serializer>()),
  m_ioService(ioService)
{

}

TCPSession::~TCPSession()
{

}

void TCPSession::Post(const std::shared_ptr<NetworkUtils::NetworkMessage>& message)
{
    auto handler = [this, message]()
    {
        m_outputMessages.emplace_back(message);
        if (!m_outputMessages.empty())
        {
            DoWrite();
        }
    };

    m_ioService.post(handler);
}

void TCPSession::Read(TCallback callback)
{
    auto handler = [this, callback]()
    {
        m_readCallback = callback;
        DoReadHeader();
    };
    
    m_ioService.post(handler);
}

void TCPSession::DoReadHeader()
{
    auto headerSize = NetworkUtils::NetworkMessage::GetHeaderSize();
    m_inMsgBlob->Resize(headerSize);
    auto self = shared_from_this();

    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_inMsgBlob->GetData(), headerSize),
        [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec)
        {
            auto message = NetworkUtils::NetworkMessage::Create(MessageType::BASE);
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

void TCPSession::DoReadBody(const std::shared_ptr<NetworkUtils::NetworkMessage>& message)
{
    m_inMsgBlob->Clear();

    auto messageSize = message->GetMessageSize();
    m_inMsgBlob->Resize(messageSize);

    auto self = shared_from_this();
    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_inMsgBlob->GetData(), messageSize),
        [this, self, message](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            if (m_readCallback)
            {
                auto messageType = message->GetType();
                auto message = NetworkUtils::NetworkMessage::Create(messageType);
                message->DeserializeBlob(m_inMsgBlob);
                m_readCallback(message);
            }
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
    auto message = m_outputMessages.front();
    m_outMsgBlob = message->SerializeBlob();
    auto size = message->GetMessageSize();
    auto self = shared_from_this();
    boost::asio::async_write(m_socket,
        boost::asio::buffer(m_outMsgBlob->GetData(), message->GetMessageSize()),
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
    DoReadHeader();
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
    return true;
}

void TCPSession::CloseConnecton()
{
    m_ioService.post([this]() { m_socket.close(); });
}

TCPSession::TSocket& TCPSession::GetSocket()
{
    return m_socket;
}
}


