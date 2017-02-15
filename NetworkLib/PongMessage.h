#pragma once
#include "NetworkMessage.h"

namespace Network {
class PongMessage : public NetworkMessage
{
public:
    PongMessage();

protected:
    void Serialize(SerializerBase& serializer) const override;
    void Deserialize(DeserializerBase& deserializer) override;
    std::uint64_t GetSizeInternal() const override;


};
}


