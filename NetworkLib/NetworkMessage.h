#pragma once
#include <memory>
#include <cstdint>
#include <utility>
#include "ISerializable.h"
#include "NetworkDefs.h"
#include "Header.h"

namespace NetworkUtils{
class NetworkMessage: public ISerializable
{
public:
    NetworkMessage();
    virtual ~NetworkMessage() {}

public:
    static std::shared_ptr<NetworkMessage> Create(MessageType type);
    static std::uint8_t GetHeaderSize();

public:
    void SetMessageSize(std::uint64_t size);
    std::uint64_t GetMessageSize() const;

public:
    MessageType GetType() const;

public:
    NetworkMessage(const NetworkMessage&) = delete;
    NetworkMessage& operator=(const NetworkMessage&) = delete;

protected:
    NetworkMessage(MessageType type);
    NetworkMessage(MessageType type, TMessageSize size);

    void Serialize(SerializerBase& serializer) const override;
    void Deserialize(DeserializerBase& deserializer) override;

private:
    std::uint64_t m_size;
    MessageType m_type;
};
}

