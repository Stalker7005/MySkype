#include "Session.h"

using namespace NetworkUtils;
using boost::asio::ip::tcp;

Session::Session(tcp::socket socket) :
    m_socket(std::move(socket)),
    m_inMsgHeaderBlob(std::make_shared<Serialization::Blob>()),
    m_inMsgBodyBlob(std::make_shared<Serialization::Blob>()),
    m_outMsgBlob(std::make_shared<Serialization::Blob>()),
    m_serializer(std::make_unique<Serialization::Serializer>())
{

}

void Session::Start()
{
    DoReadHeader();
}

void Session::Deliver(const std::shared_ptr<NetworkUtils::NetworkMessage>& message)
{
    bool write_in_progress = !m_outputMessages.empty();
    m_outputMessages.emplace_back(message);

    /*if (!m_writeInProgress)
    {*/
    DoWriteHeader();
    /*}*/
}

void Session::DoReadHeader()
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
            //Leave logic
        }
    });
}

void Session::DoReadBody(std::uint64_t bodySize)
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
            //Leave logic
        }
    });
}

void Session::DoWriteHeader()
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
    }
    );
}

void Session::DoWriteBody()
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
            //m_socket.close();
            std::cout << "Fuck DoWrite" << std::endl;
        }
    });
}

