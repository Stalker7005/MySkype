#include "Header.h"
#include "NetworkDefs.h"

namespace NetworkUtils {

Header::Header(): Header{static_cast<uint8_t>(MessageType::INVALID), 0}
{}

Header::Header(TMessageNumericType type, TMessageSize size)
: m_size(size)
, m_type(type)
{}

Header::Header(TMessageNumericType type): Header{type, 0}
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

void Header::SetType(uint8_t type)
{
    m_type = type;
}

std::uint8_t Header::GetType() const
{
    return m_type;
}

}

