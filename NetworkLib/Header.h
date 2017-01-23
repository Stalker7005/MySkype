#pragma once
#include "NetworkDefs.h"

namespace Network {
class Header
{
public:
    Header();
    Header(MessageType type);
    Header(MessageType type, TMessageSize size);
    ~Header() = default;

    static THeaderSize GetHeaderSize();

public:
    void SetMessageSize(std::uint64_t size);
    std::uint64_t GetMessageSize() const;

    void SetType(MessageType type);
    MessageType GetType() const;

public:
    TMessageSize m_size;
    MessageType m_type;
};
}

