#pragma once
#include <memory>
#include <cstdint>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

namespace NetworkUtils{
class NetworkMessage
{
public:
    enum class Type: std::uint8_t
    {
        HEADER,
        PING,
        PONG,
        TEXT,
        VOICE,
        ARCHIVE,
        SCREENSHOT,
        VIDEO
    };

public:
    NetworkMessage();
    virtual ~NetworkMessage() {}

public:
    static std::shared_ptr<NetworkMessage> Create(Type type);
    static std::uint8_t GetHeaderSize();

public:
    void SetMessageSize(std::uint64_t size);
    std::uint64_t GetMessageSize() const;
    Type GetType() const;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        archive(m_type, m_size);
    }

public:
    NetworkMessage(const NetworkMessage&) = delete;
    NetworkMessage& operator=(const NetworkMessage&) = delete;

protected:
    NetworkMessage(NetworkMessage::Type type);

private:
    std::uint8_t m_type;
    std::uint64_t m_size;
};




}

