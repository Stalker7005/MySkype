#pragma once
#include "NetworkDefs.h"
#include <cereal/types/polymorphic.hpp>

namespace NetworkUtils {
class Header
{
public:
    Header();
    Header(MessageType type);
    Header(MessageType type, TMessageSize size);
    ~Header() = default;
    
    template<typename Archive>
    void serialize(Archive& archive)
    {
        archive(m_size, static_cast<TMessageNumericType>(m_type));
    }

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

