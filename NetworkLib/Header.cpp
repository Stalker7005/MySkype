#include "Header.h"
#include "NetworkDefs.h"

namespace NetworkUtils {

Header::Header(): Header{MessageType::INVALID, 0}
{}

Header::Header(MessageType type, TMessageSize size)
: m_size(size)
, m_type(type)
{}

Header::Header(MessageType type): Header{type, 0}
{

}

NetworkUtils::THeaderSize Header::GetHeaderSize()
{
    return (sizeof(m_type) + sizeof(m_size));
}

void Header::SetMessageSize(std::uint64_t size)
{
    m_size = size;
}

std::uint64_t Header::GetMessageSize() const
{
    return m_size;
}

void Header::SetType(MessageType type)
{
    m_type = type;
}

NetworkUtils::MessageType Header::GetType() const
{
    return m_type;
}

}

