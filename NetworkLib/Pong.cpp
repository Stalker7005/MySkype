#include "Pong.h"

namespace NetworkUtils {
Pong::Pong() : NetworkMessage(MessageType::PONG)
{}

void Pong::Serialize(SerializerBase& serializer) const
{
    NetworkMessage::Serialize(serializer);
}

void Pong::Deserialize(DeserializerBase& deserializer)
{
    NetworkMessage::Deserialize(deserializer);
}

}
