#pragma once
#include "Serealizer.h"
#include <cereal/archives/xml.hpp>

namespace Serialization {
class XMLSerializer : public Serializer
{
public:
    template<typename Type>
    void Serizlize(Type& obj)
    {
        cereal::XMLOutputArchive xmlArhive(m_stream);
        xmlArhive(obj);
    }
    template<typename Type>
    void Deserialize(Type& obj)
    {
        cereal::XMLInputArchive xmlArhive(m_stream);
        xmlArhive(obj);
    }
};
}


