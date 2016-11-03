#include "TCPSession.h"
#include "Logger.h"

using namespace NetworkUtils;
using namespace boost::asio::ip;

TCPSession::TCPSession(TSocket socket, TIOService& ioService) :
    m_socket(std::move(socket)),
    m_inMsgHeaderBlob(std::make_shared<Serialization::Blob>()),
    m_inMsgBodyBlob(std::make_shared<Serialization::Blob>()),
    m_outMsgBlob(std::make_shared<Serialization::Blob>()),
    m_serializer(std::make_unique<Serialization::Serializer>()),
    m_ioService(ioService)
{

}

void TCPSession::Write(const std::shared_ptr<NetworkUtils::NetworkMessage>& message)
{
    m_outputMessages.emplace_back(message);
    if (!m_outputMessages.empty())
    {
        DoWriteHeader();
    }
}

void TCPSession::DoReadHeader()
{
    auto headerSize = NetworkUtils::NetworkMessage::GetHeaderSize();
    m_inMsgHeaderBlob->Reserve(headerSize);
    auto self = shared_from_this();

    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_inMsgHeaderBlob->GetData(), headerSize),
        [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec)
        {
            std::cout << "Header size:" << length << std::endl;

            //Deseralize header
            auto headerInfo = NetworkMessage::ParseHeader(m_inMsgHeaderBlob->GetData());
            //TODO add message handling
            auto messageType = headerInfo.first;
            auto messageSize = headerInfo.second;


            DoReadBody(messageSize);
        }
        else
        {
            LOG_ERR("Can't read header! Boost err:[%s]", ec.message());
            CloseConnecton();
        }
    });
}

void TCPSession::DoReadBody(std::uint64_t bodySize)
{
    m_inMsgBodyBlob->Reserve(bodySize);
    auto self = shared_from_this();
    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_inMsgBodyBlob->GetData(), bodySize),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            OnPing();
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
    auto outMsg = m_outputMessages.front();
    m_serializer->Serialize(m_outMsgBlob, outMsg);
    auto self = shared_from_this();
    outMsg->SetMessageSize(m_outMsgBlob->Size());

    boost::asio::async_write(m_socket,
        boost::asio::buffer(outMsg->GetHeader(), outMsg->GetHeaderSize()),
        [this, self](boost::system::error_code ec, std::size_t /*lenght*/)
    {
        if (!ec)
        {
            DoWriteBody();
        }
        else
        {
            LOG_ERR("Can't write header. Boost err:[%s]", ec.message());
            CloseConnecton();
        }
    }
    );
}

void TCPSession::DoWriteBody()
{
    auto self = shared_from_this();
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

