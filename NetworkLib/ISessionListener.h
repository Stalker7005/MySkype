#pragma once
#include <memory>
#include "NetworkMessage.h"

namespace Network {
class ISessionListener
{
public:
    virtual void OnRead(const std::shared_ptr<NetworkMessage>& message) = 0;
};
}

