#pragma once
#include "NetworkMessage.h"
#include <cereal/types/polymorphic.hpp>

namespace NetworkUtils {
class Ping : public NetworkMessage
{
public:
    Ping();

    template<typename Archive>
    void serialize(Archive& archive)
    {
        archive(cereal::base_class<NetworkMessage>(this));
    }
};
}

CEREAL_REGISTER_TYPE(NetworkUtils::Ping);


