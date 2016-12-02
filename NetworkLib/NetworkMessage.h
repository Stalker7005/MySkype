#pragma once
#include <memory>
#include <cstdint>
#include <utility>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/polymorphic.hpp>

#include "NetworkDefs.h"
#include "Header.h"

namespace NetworkUtils{
class NetworkMessage
{
public:
    NetworkMessage();
    virtual ~NetworkMessage() {}

public:
    template<typename Archive>
    void serialize(Archive& archive)
    {
        archive(m_header);
    }

public:
    static std::shared_ptr<NetworkMessage> Create(MessageType type);
    static std::uint8_t GetHeaderSize();

public:
    void SetMessageSize(std::uint64_t size);
    std::uint64_t GetMessageSize() const;

public:
    MessageType GetType() const;
    std::shared_ptr<Header> GetHeader();

public:
    NetworkMessage(const NetworkMessage&) = delete;
    NetworkMessage& operator=(const NetworkMessage&) = delete;

protected:
    NetworkMessage(MessageType type);
    NetworkMessage(MessageType type, TMessageSize size);

private:
     std::shared_ptr<Header> m_header;
};
}

