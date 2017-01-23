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
    using TCallback = std::function<void(const std::shared_ptr<Network::NetworkMessage>& message)>;

public:
    Session(Network::TSessionId sessionId);
    virtual ~Session();
    
public:
    Network::TSessionId GetId() const;
    virtual void Post(const std::shared_ptr<Network::NetworkMessage>& message) = 0;
    virtual void Read(TCallback callback) = 0;
    
private:
    Network::TSessionId m_sessionId;
};
}


