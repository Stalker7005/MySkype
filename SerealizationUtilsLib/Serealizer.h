#pragma once
#include <cstdint>
#include <memory>

#include <cereal/types/map.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/stack.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>

#include "Blob.h"

namespace Serialization {

class Serializer
{
public:
    enum class Type : std::uint8_t
    {
        BINARY,
        JSON,
        XML
    };

public:
    Serializer();
    Serializer(Type serializerType);
    ~Serializer();

public:
    void SetType(Type serializerType);

    template<typename Type>
    void Serialize(Type& obj)
    {
        self->Serialize(obj);
    }

    template<typename Type>
    void Deserialize(Type& obj)
    {
        self->Deserialize(obj);
    }
    
protected:
    std::stringstream m_stream;

private:
    void ChangeSerealizer(Type type);

private:
    std::shared_ptr<Serializer> m_self;

};

}