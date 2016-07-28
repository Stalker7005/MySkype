#include "NetworkMessage.h"
#include "Ping.h"
#include "Pong.h"

namespace NetworkUtils {
std::shared_ptr<NetworkMessage> NetworkMessage::Create(Type type)
{
    std::shared_ptr<NetworkMessage> message(nullptr);

    switch (type)
    {
    case NetworkUtils::NetworkMessage::Type::HEADER:
        message = std::make_shared<NetworkMessage>();
        break;
    case NetworkUtils::NetworkMessage::Type::PING:
        message = std::make_shared<Ping>();
        break;
    case NetworkUtils::NetworkMessage::Type::PONG:
        message = std::make_shared<Pong>();
        break;
    case NetworkUtils::NetworkMessage::Type::TEXT:
        break;
    case NetworkUtils::NetworkMessage::Type::VOICE:
        break;
    case NetworkUtils::NetworkMessage::Type::ARCHIVE:
        break;
    case NetworkUtils::NetworkMessage::Type::SCREENSHOT:
        break;
    case NetworkUtils::NetworkMessage::Type::VIDEO:
        break;
    default:
        //TODO Add Logger
        break;
    }

    return message;
}

std::uint8_t NetworkMessage::GetHeaderSize()
{
    return (sizeof(m_type) + sizeof(m_size));
}

void NetworkMessage::SetMessageSize(std::uint64_t size)
{
    m_size = size;
}

std::uint64_t NetworkMessage::GetMessageSize() const
{
    return m_size;
}

NetworkMessage::Type NetworkMessage::GetType() const
{
    return static_cast<NetworkMessage::Type>(m_type);
}

NetworkMessage::NetworkMessage(NetworkMessage::Type type) :
m_type(static_cast<std::uint8_t>(type)),
m_size(0)
{}

NetworkMessage::NetworkMessage():
m_type(static_cast<std::uint8_t>(NetworkMessage::Type::HEADER)),
m_size(0)
{

}

}

