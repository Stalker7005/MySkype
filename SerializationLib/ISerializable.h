#pragma once

#include "Serializer.h"
#include "Deserializer.h"

class ISerializable
{
public:
    virtual void Serialize(SerializerBase& serializer) const = 0;
    virtual void Deserialize(DeserializerBase& deserializer) = 0;

    std::shared_ptr<Blob> SerializeBlob() const
    {
        Serializer serializer;
        Serialize(serializer);
        return serializer.GetBlob();
    }

    void DeserializeBlob(const std::shared_ptr<Blob>& blob)
    {
        Deserializer deserializer(blob);
        Deserialize(deserializer);
    }
};

