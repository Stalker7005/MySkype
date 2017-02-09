#pragma once
#include "NetworkDefs.h"
class Blob;

namespace Network {
class ISessionSendListener
{
public:
    virtual void OnSend(TSessionId sessionId, const std::shared_ptr<Blob>& blob) = 0;
};
}

