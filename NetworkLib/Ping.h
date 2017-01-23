#pragma once
#include "NetworkMessage.h"
namespace Network {
class Ping : public NetworkMessage
{
public:
    Ping();

    virtual void Serialize(SerializerBase& serializer) const override;
    virtual void Deserialize(DeserializerBase& deserializer) override;
};
}


