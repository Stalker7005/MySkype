#include "TCPSession.h"
#include "Logger.h"

using namespace NetworkUtils;
using namespace boost::asio::ip;
namespace Network {
TCPSession::TCPSession(NetworkUtils::TSessionId sessionId, TIOService& ioService) 
: Session(sessionId),
  m_socket(ioService),
  m_inMsgHeaderBlob(std::make_shared<Serialization::Blob>()),
  m_inMsgBodyBlob(std::make_shared<Serialization::Blob>()),
  m_outMsgBlob(std::make_shared<Serialization::Blob>()),
  m_serializer(std::make_unique<Serialization::Serializer>()),
  m_ioService(ioService)
{

}

TCPSession::~TCPSession()
{

}

void TCPSession::Post(const std::shared_ptr<NetworkUtils::NetworkMessage>& message)
{
    m_outputMessages.emplace_back(message);
    if (!m_outputMessages.empty())
    {
        DoWriteHeader();
    }
}

void TCPSession::Read(TCallback callback)
{
    m_readCallback = callback;
    DoReadHeader();
}

void TCPSession::DoReadHeader()
{
    auto headerSize = NetworkUtils::NetworkMessage::GetHeaderSize();
    m_inMsgHeaderBlob->Resize(headerSize);
    auto self = shared_from_this();

    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_inMsgHeaderBlob->GetData(), headerSize),
        [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec)
        {
            auto message = NetworkUtils::NetworkMessage::Create(MessageType::BASE);
            auto header = message->GetHeader();
            m_serializer->Deserialize(m_inMsgHeaderBlob, header);

            DoReadBody(header);
        }
        else
        {
            LOG_ERR("Can't read header! Boost err:[%s]", ec.message());
            CloseConnecton();
        }
    });
}

void TCPSession::DoReadBody(const std::shared_ptr<Header>& header)
{
    auto messageSize = header->GetMessageSize();
    m_inMsgBodyBlob->Resize(messageSize);
    auto self = shared_from_this();
    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_inMsgBodyBlob->GetData(), messageSize),
        [this, self, header](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            if (m_readCallback)
            {
                auto messageType = header->GetType();
                auto message = NetworkUtils::NetworkMessage::Create(messageType);
                m_serializer->Deserialize(m_inMsgBodyBlob, message);
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

void TCPSession::DoWriteHeader()
{
    auto self = shared_from_this();
    auto outMsg = m_outputMessages.front();
    auto header = outMsg->GetHeader();
    m_serializer->Serialize(m_outMsgBlob, header);

    boost::asio::async_write(m_socket,
        boost::asio::buffer(m_outMsgBlob->GetData(), outMsg->GetHeaderSize()),
        [this, self, outMsg](boost::system::error_code ec, std::size_t /*lenght*/)
    {
        if (!ec)
        {
            DoWriteBody(outMsg);
        }
        else
        {
            LOG_ERR("Can't write header. Boost err:[%s]", ec.message());
            CloseConnecton();
        }
    }
    );
}

void TCPSession::DoWriteBody(const std::shared_ptr<NetworkUtils::NetworkMessage>& outMsg)
{
    m_serializer->Serialize(m_outMsgBlob, outMsg);
    auto self = shared_from_this();
    outMsg->SetMessageSize(m_outMsgBlob->Size());

    boost::asio::async_write(m_socket,
        boost::asio::buffer(m_outMsgBlob->GetData(), m_outMsgBlob->Size()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            m_outputMessages.pop_front();
            if (!m_outputMessages.empty())
            {
                DoWriteHeader();
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


