#include "NetworkMessage.h"
#include "Ping.h"
#include "Pong.h"

namespace NetworkUtils {
std::shared_ptr<NetworkMessage> NetworkMessage::Create(Type type)
{
    std::shared_ptr<NetworkMessage> message(nullptr);

    switch (type)
    {
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

constexpr std::uint8_t NetworkMessage::GetHeaderSize()
{
    return (sizeof(m_type) + sizeof(m_size));
}

NetworkUtils::NetworkMessage::THeaderInfo NetworkMessage::ParseHeader(char* data)
{
    auto numericType = *reinterpret_cast<std::uint8_t*>(data);
    auto type = static_cast<NetworkMessage::Type>(numericType);
    auto size = *reinterpret_cast<std::uint64_t*>(data + sizeof(numericType));

    auto headerInfo = std::make_pair(type, size);
    return headerInfo;
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

char* NetworkMessage::GetHeader()
{
    std::memcpy(m_header.get(), &m_type, sizeof(m_type));
    std::memcpy(m_header.get() + sizeof(m_type), &m_size, sizeof(m_size));

    return m_header.get();
}

NetworkMessage::NetworkMessage(NetworkMessage::Type type) :
m_type(static_cast<std::uint8_t>(type)),
m_size(0),
m_header(std::make_unique<char[]>(NetworkMessage::GetHeaderSize()))
{}

}

