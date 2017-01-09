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
    std::shared_ptr<Session> GetSession(NetworkUtils::TSessionId sessionId);

    void RemoveSession(NetworkUtils::TSessionId id);
    void RemoveSessions();

public:
    void StartSession(NetworkUtils::TSessionId sessionId);
    void StopSession(NetworkUtils::TSessionId stopSession);
    void StartSessions();
    void StopSessions();

private:
    NetworkUtils::TSessionId m_sessionId;
    std::unordered_map<NetworkUtils::TSessionId, std::shared_ptr<Session>> m_sessions;
};

Network::Connection::Connection()
    : m_sessionId(0)
{

}

Network::Connection::~Connection()
{
    RemoveSessions();
}

void Network::Connection::AddSession(const std::shared_ptr<Session>& session)
{
    m_sessions.emplace(std::make_pair(m_sessionId, session));
    LOG_INFO("Added session with id:[%d]", m_sessionId);
    ++m_sessionId;
}

void Network::Connection::RemoveSession(NetworkUtils::TSessionId id)
{
    auto iter = m_sessions.find(id);
    if (iter != m_sessions.end())
    {
        m_sessions.erase(iter);
        LOG_INFO("Session removed id: [%d]", id);
    }
    else
    {
        LOG_WARN("Can't find session to remove");
    }
}

void Network::Connection::RemoveSessions()
{
    StopSessions();
    m_sessions.clear();
}

void Network::Connection::StartSessions()
{
    for (auto iter : m_sessions)
    {
        auto session = iter.second;
        session->Start();
    }
}

void Network::Connection::StopSessions()
{
    for (auto iter : m_sessions)
    {
        auto session = iter.second;
        session->Stop();
    }
}

std::shared_ptr<Session> Network::Connection::GetSession(NetworkUtils::TSessionId sessionId)
{
    std::shared_ptr<Session> result;
    auto iter = m_sessions.find(sessionId);
    if (iter != m_sessions.end())
    {
        result = iter->second;
    }
    else
    {
        LOG_WARN("Can't find session with id:[%d]", sessionId);
    }

    return result;
}

void Network::Connection::StartSession(NetworkUtils::TSessionId sessionId)
{
    auto session = GetSession(sessionId);
    if (session)
    {
        session->Start();
    }
}

void Network::Connection::StopSession(NetworkUtils::TSessionId sessionId)
{
    auto session = GetSession(sessionId);
    if (session)
    {
        session->Stop();
    }
}
}

