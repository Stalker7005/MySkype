#pragma once
#include <memory>

namespace Netowrk {
class Session;
class IConnection
{
public:
    virtual void AddSession(const std::shared_ptr<Session>& session);
    virtual void AddSession();
    virtual void RemoveSession();
};
}

