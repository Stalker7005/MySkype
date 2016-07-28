#pragma  once
#include "Serealizer.h"
#include <cereal/archives/json.hpp>

namespace Serialization {
class JSONSerizlier : public Serializer
{
public:
    template<typename Type>
    void Serizlize(Type& obj)
    {
        cereal::JSONOutputArchive jsonArhive(m_stream);
        jsonArhive(obj);
    }
    template<typename Type>
    void Deserialize(Type& obj)
    {
        cereal::JSONInputArchive jsonArhive(m_stream);
        jsonArhive(obj);
    }
};
}