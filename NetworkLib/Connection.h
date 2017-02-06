#pragma once
#include "NetworkDefs.h"
#include "Logger.h"
#include "Session.h"
#include <unordered_map>

namespace Network {
class Connection
{
public:
    Connection();
    ~Connection();

public:
    void AddSession(const std::shared_ptr<Session>& session);
    std::shared_ptr<Session> GetSession(Network::TSessionId sessionId);

    void RemoveSession(Network::TSessionId id);
    void RemoveSessions();

public:
    void StartSession(Network::TSessionId sessionId);
    void StopSession(Network::TSessionId stopSession);
    void StartSessions();
    void StopSessions();

private:
    std::unordered_map<Network::TSessionId, std::shared_ptr<Session>> m_sessions;
};


}

