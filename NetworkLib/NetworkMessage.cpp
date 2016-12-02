#include "NetworkMessage.h"
#include "Ping.h"
#include "Pong.h"
#include "Header.h"

namespace NetworkUtils {
std::shared_ptr<NetworkMessage> NetworkMessage::Create(MessageType type)
{
    std::shared_ptr<NetworkMessage> message(nullptr);

    switch (type)
    {
    case MessageType::BASE:
        message = std::make_shared<NetworkMessage>();
        break;
    case MessageType::PING:
        message = std::make_shared<Ping>();
        break;
    case MessageType::PONG:
        message = std::make_shared<Pong>();
        break;
    case MessageType::TEXT:
        break;
    case MessageType::VOICE:
        break;
    case MessageType::ARCHIVE:
        break;
    case MessageType::SCREENSHOT:
        break;
    case MessageType::VIDEO:
        break;
    default:
        //TODO Add Logger
        break;
    }

    return message;
}

std::uint8_t NetworkMessage::GetHeaderSize()
{
    return Header::GetHeaderSize();
}

void NetworkMessage::SetMessageSize(std::uint64_t size)
{
    m_header->SetMessageSize(size);
}

std::uint64_t NetworkMessage::GetMessageSize() const
{
    return m_header->GetMessageSize();
}

NetworkUtils::MessageType NetworkMessage::GetType() const
{
    return static_cast<MessageType>(m_header->GetType());
}

std::shared_ptr<Header> NetworkMessage::GetHeader()
{
    return m_header;
}

NetworkMessage::NetworkMessage(MessageType type)
: NetworkMessage{type, 0}
{
}

NetworkMessage::NetworkMessage()
: NetworkMessage{MessageType::BASE, 0}
{
}

NetworkMessage::NetworkMessage(MessageType type, TMessageSize size)
: m_header(std::make_shared<Header>(static_cast<TMessageNumericType>(type), size))
{}

}

