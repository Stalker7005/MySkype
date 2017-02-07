#pragma once
#include <memory>
#include "NetworkDefs.h"

class Blob;

namespace Network {
class ISessionListener
{
public:
    virtual void OnRecvData(const std::shared_ptr<Blob>& blob) = 0;
    virtual void OnCloseSession(TSessionId id) = 0;
};
}

