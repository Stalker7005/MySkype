#pragma once

#include <boost/asio.hpp>
#include "RunningContext.h"
#include "NetworkDefs.h"
#include "NetworkMessage.h"
#include "SessionProvider.h"
#include <functional>

namespace Network {
class Session : public ThreadsUtils::RunningContext,
                public SessionProvider
{
public:
    using TCallback = std::function<void(const std::shared_ptr<Network::NetworkMessage>& message)>;

public:
    Session(Network::TSessionId sessionId);
    virtual ~Session();
    
public:
    Network::TSessionId GetId() const;
    

private:
    Network::TSessionId m_sessionId;
};
}


