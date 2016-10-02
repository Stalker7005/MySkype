#pragma once
#include <string>
#include "NetworkMessage.h"

class IUser
{
public:
    virtual ~IUser() {}
    virtual void Deliver(const std::shared_ptr<NetworkUtils::NetworkMessage>& message) = 0;

};
