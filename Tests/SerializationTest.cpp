#include "catch.hpp"
#include <iostream>
#include <string>
#include <memory>
#include "Serializer.h"
#include "NetworkMessage.h"
#include "Logger.h"

using namespace Network;
//using namespace Serialization;

TEST_CASE("SerializationTest")
{
    auto message1 = NetworkMessage::Create(MessageType::PING);
    auto blob = message1->SerializeBlob();

    auto message2 = NetworkMessage::Create(MessageType::PONG);
    message2->DeserializeBlob(blob);
}




