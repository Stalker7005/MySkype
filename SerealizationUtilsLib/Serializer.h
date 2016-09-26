#pragma once
#include <memory>
#include <sstream>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>

#include <cereal/types/array.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/queue.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>

#include "Blob.h"

namespace Serialization {
class Serializer
{
public:
    enum class Type: std::uint8_t
    {
        Binary,
        PortableBinary
    };

public:
    Serializer(Type serializeType = Type::PortableBinary);
    ~Serializer();

public:
    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer&) = delete;

public:
    template<typename... Args>
    void Serialize(std::shared_ptr<Serialization::Blob>& blob, Args&&... params)
    {
        ClearDataStream();
        if (m_type == Type::Binary)
        {
            cereal::BinaryOutputArchive archive(m_dataStream);
            archive(std::forward<Args>(params)...);
        }
        else if (m_type == Type::PortableBinary)
        {
            cereal::PortableBinaryOutputArchive archive(m_dataStream);
            archive(std::forward<Args>(params)...);
        }
        else
        {
            //TODO Add Logger 
        }

        auto data = m_dataStream.str();
        blob->SetData(data.data(), data.size());
    }

    template<typename... Args>
    void Deserialize(std::shared_ptr<Serialization::Blob>& blob, Args&&... params)
    {
        ClearDataStream();
        auto& stream = m_dataStream.write(blob->GetData(), 44);
        if (!stream)
        {
            std::cout << "Can't serialize data" << std::endl;
        }

        if (m_type == Type::Binary)
        {
            cereal::BinaryInputArchive archive(m_dataStream);
            archive(std::forward<Args>(params)...);
        }
        else if (m_type == Type::PortableBinary)
        {
            cereal::PortableBinaryInputArchive archive(m_dataStream);
            archive(std::forward<Args>(params)...);
        }
        else
        {
            //TODO Add Logger 
        }
    }

private:
    void ClearDataStream();

private:
    Type m_type;
    std::stringstream m_dataStream;
    
};
}

