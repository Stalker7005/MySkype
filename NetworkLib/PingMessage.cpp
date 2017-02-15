#include "PingMessage.h"
namespace Network {

PingMessage::PingMessage(): NetworkMessage(MessageType::PING)
{}

void PingMessage::Serialize(SerializerBase& serializer) const
{
    NetworkMessage::Serialize(serializer);
}

void PingMessage::Deserialize(DeserializerBase& deserializer)
{
    NetworkMessage::Deserialize(deserializer);
}

}

