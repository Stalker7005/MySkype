#include "Ping.h"
namespace NetworkUtils {

Ping::Ping(): NetworkMessage(MessageType::PING)
{}

void Ping::Serialize(SerializerBase& serializer) const
{
    NetworkMessage::Serialize(serializer);
}

void Ping::Deserialize(DeserializerBase& deserializer)
{
    NetworkMessage::Deserialize(deserializer);
}

}

