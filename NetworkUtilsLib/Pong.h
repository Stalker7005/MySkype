#pragma once
#include "NetworkMessage.h"
#include <cereal/types/polymorphic.hpp>

namespace NetworkUtils {
class Pong : public NetworkMessage
{
public:
    Pong();

    template<typename Archive>
    void serialize(Archive& archive)
    {
        archive(cereal::base_class<NetworkMessage>(this));
    }
};
}

CEREAL_REGISTER_TYPE(NetworkUtils::Pong);


