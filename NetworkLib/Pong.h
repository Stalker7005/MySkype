#pragma once
#include "NetworkMessage.h"

namespace Network {
class Pong : public NetworkMessage
{
public:
    Pong();

    void Serialize(SerializerBase& serializer) const override;
    void Deserialize(DeserializerBase& deserializer) override;

};
}


