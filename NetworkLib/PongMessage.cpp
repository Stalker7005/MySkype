#include "PongMessage.h"

namespace Network {
PongMessage::PongMessage() 
: NetworkMessage(MessageType::PONG)
{}

void PongMessage::Serialize(SerializerBase& serializer) const
{
    NetworkMessage::Serialize(serializer);
}

void PongMessage::Deserialize(DeserializerBase& deserializer)
{
    NetworkMessage::Deserialize(deserializer);
}

std::uint64_t PongMessage::GetSizeInternal() const
{
    
}

}
