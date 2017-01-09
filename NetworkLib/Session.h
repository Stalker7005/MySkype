#pragma once

#include <boost/asio.hpp>
#include "RunningContext.h"
#include "NetworkDefs.h"
#include "NetworkMessage.h"
#include <functional>

namespace Network {
class Session : public ThreadsUtils::RunningContext
{
public:
    using TCallback = std::function<void(const std::shared_ptr<NetworkUtils::NetworkMessage>& message)>;

public:
    Session(NetworkUtils::TSessionId sessionId);
    virtual ~Session();
    
public:
    NetworkUtils::TSessionId GetId() const;
    virtual void Post(const std::shared_ptr<NetworkUtils::NetworkMessage>& message) = 0;
    virtual void Read(TCallback callback) = 0;
    
private:
    NetworkUtils::TSessionId m_sessionId;
};
}


