#pragma once
#include "Serealizer.h"
#include <cereal/archives/binary.hpp>

namespace Serialization {
class BinarySerializer : public Serializer
{
public:
    template<typename Type>
    void Serizlize(Type& obj)
    {
        cereal::BinaryOutputArchive binArhive(m_stream);
        binArhive(obj);
    }
    template<typename Type>
    void Deserialize(Type& obj)
    {
        cereal::BinaryOutputArchive binArhive(m_stream);
        binArhive(obj);
    }
};
}

