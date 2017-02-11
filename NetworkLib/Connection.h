#pragma once
#include "NetworkDefs.h"
#include "Logger.h"
#include "Session.h"
#include "SessionProvider.h"
#include "SessionSendProvider.h"
#include "ISessionSendListener.h"
#include "ISessionListener.h"

#include <unordered_map>

namespace Network {
class Connection: public ISessionListener,
                  public SessionProvider,
                  public ISessionSendListener,
                  public SessionSendProvider,
                  public std::enable_shared_from_this<Connection>
{
public:
    Connection();
    ~Connection();

public:
    void AddSession(const std::shared_ptr<Session>& session);
    std::shared_ptr<Session> GetSession(Network::TSessionId sessionId);

    void RemoveSession(Network::TSessionId id);
    void RemoveSessions();

    void OnSendData(TSessionId sessionId, const std::shared_ptr<Blob>& blob) override;

public:
    void StartSession(Network::TSessionId sessionId);
    void StopSession(Network::TSessionId stopSession);
    void StartSessions();
    void StopSessions();

private:
    void OnRecvData(TSessionId id, const std::shared_ptr<Blob>& blob) override;
    void OnCloseSession(TSessionId id) override;

private:
    std::unordered_map<Network::TSessionId, std::shared_ptr<Session>> m_sessions;
};


}

