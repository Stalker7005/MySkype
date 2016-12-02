#include "catch.hpp"
#include <iostream>
#include <string>
#include <memory>
#include "Serializer.h"
#include "NetworkMessage.h"
#include "Logger.h"

using namespace NetworkUtils;
using namespace Serialization;

TEST_CASE("SerializationTest")
{
    auto serializer = std::make_unique<Serializer>();
    auto message = NetworkMessage::Create(MessageType::PING);
    auto message2 = NetworkMessage::Create(MessageType::BASE);

    auto header = message->GetHeader();
    auto blob = std::make_shared<Blob>(header->GetHeaderSize());
    auto blob2 = std::move(blob);
    REQUIRE(blob != blob2);

    serializer->Serialize(blob2, header);
    serializer->Deserialize(blob2, header);

    serializer->Serialize(blob, message);
    serializer->Deserialize(blob, message2);
    

}




