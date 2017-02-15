#include "NetworkMessage.h"
#include "PingMessage.h"
#include "PongMessage.h"
#include "Header.h"

namespace Network {
std::shared_ptr<NetworkMessage> NetworkMessage::Create(MessageType type)
{
    std::shared_ptr<NetworkMessage> message(nullptr);

    switch (type)
    {
    case MessageType::BASE:
        message = std::make_shared<NetworkMessage>();
        break;
    case MessageType::PING:
        message = std::make_shared<PingMessage>();
        break;
    case MessageType::PONG:
        message = std::make_shared<PongMessage>();
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
    return (sizeof(m_size) + sizeof(m_type));
}

void NetworkMessage::SetMessageSize(std::uint64_t size)
{
    m_size = size;
}

std::uint64_t NetworkMessage::GetMessageSize() const
{
    return m_size == 0 ? GetSizeInternal() : m_size;
}

Network::MessageType NetworkMessage::GetType() const
{
    return m_type;
}

NetworkMessage::NetworkMessage(MessageType type)
: m_type(type)
{
}

NetworkMessage::NetworkMessage()
: NetworkMessage{MessageType::BASE}
{
}

void NetworkMessage::Serialize(SerializerBase& serializer) const
{
    auto size = m_size == 0 ? GetSizeInternal() : m_size;
    serializer.Add(size).Add(m_type);
}

void NetworkMessage::Deserialize(DeserializerBase& deserializer)
{
    deserializer.Get(m_size).Get(m_type);
}

}

