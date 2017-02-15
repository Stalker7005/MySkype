#pragma once
#include "NetworkMessage.h"
namespace Network {
class PingMessage : public NetworkMessage
{
public:
    PingMessage();

protected:
    void Serialize(SerializerBase& serializer) const override;
    void Deserialize(DeserializerBase& deserializer) override;
    std::uint64_t GetSizeInternal() const override;

};
}


