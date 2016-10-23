#pragma once

namespace BaseObjects {
class INetworkMessagesListener
{
public:
    virtual void OnUserRegistration() = 0;
    virtual void OnPing() = 0;
    virtual void OnPong() = 0;
};

}
