#pragma once
#include "NetworkDefs.h"
#include <cereal/types/polymorphic.hpp>

namespace NetworkUtils {
class Header
{
public:
    Header();
    Header(TMessageNumericType type);
    Header(TMessageNumericType type, TMessageSize size);
    ~Header() = default;
    
    template<typename Archive>
    void serialize(Archive& archive)
    {
        archive(m_size, m_type);
    }

    static THeaderSize GetHeaderSize();

public:
    void SetMessageSize(std::uint64_t size);
    std::uint64_t GetMessageSize() const;

    void SetType(uint8_t type);
    std::uint8_t GetType() const;

public:
    TMessageSize m_size;
    TMessageNumericType m_type;
};
}

