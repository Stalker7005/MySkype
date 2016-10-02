#pragma once
#include <memory>
#include <cstdint>
#include <utility>


#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/polymorphic.hpp>

namespace NetworkUtils{
class NetworkMessage
{
public:
    enum class Type : std::uint8_t
    {
        PING,
        PONG,
        TEXT,
        VOICE,
        ARCHIVE,
        SCREENSHOT,
        VIDEO,
        INVALID
    };

public:
    using TSize = std::uint64_t;
    using THeaderInfo = std::pair<Type, TSize>;

public:
    NetworkMessage();
    virtual ~NetworkMessage() {}

public:
    static std::shared_ptr<NetworkMessage> Create(Type type);
    constexpr static std::uint8_t GetHeaderSize();
    static THeaderInfo ParseHeader(char* data);

public:
    void SetMessageSize(std::uint64_t size);
    std::uint64_t GetMessageSize() const;
    Type GetType() const;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        archive(m_type, m_size);
    }
    virtual char* GetHeader();

public:
    NetworkMessage(const NetworkMessage&) = delete;
    NetworkMessage& operator=(const NetworkMessage&) = delete;

protected:
    
    NetworkMessage(NetworkMessage::Type type);

private:
    std::uint8_t m_type;
    TSize m_size;
    std::unique_ptr<char[]> m_header;
};
}

