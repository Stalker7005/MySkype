#pragma once
#include "NetworkMessage.h"
#include <cereal/types/polymorphic.hpp>
namespace NetworkUtils {
class Pong : public NetworkMessage
{
public:
    Pong();

    void Serialize(SerializerBase& serializer) const override;
    void Deserialize(DeserializerBase& deserializer) override;

};
}


