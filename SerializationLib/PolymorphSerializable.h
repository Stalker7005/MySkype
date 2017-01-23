#pragma once

#include <boost/smart_ptr.hpp>
#include "ISerializable.h"

class PolymorphSerializable: public ISerializable
{
public:

    template<class DerivedClassEnumType>
    void SerializePolymorph(const DerivedClassEnumType& type, SerializerBase& serializer) const
    {
        serializer.AddFixed(&type, sizeof(DerivedClassEnumType));
    }

    template<class BaseClass, class DerivedClassEnumType>
    void DeserializePolymorph(DeserializerBase& deserializer)
    {
        DerivedClassEnumType type;
        deserializer.GetFixed(&type, sizeof(DerivedClassEnumType));

        auto classInstance = BaseClass::Create(type);
        if (classInstance)
        {
            classInstance->Deserialize(deserializer);
        }
    }
};

