#include "Connection.h"

namespace Network {
Network::Connection::Connection()
{
}

Network::Connection::~Connection()
{
    RemoveSessions();
}

void Network::Connection::AddSession(const std::shared_ptr<Session>& session)
{
    m_sessions.emplace(std::make_pair(session->GetId(), session));
    LOG_INFO("Added session with id:[%d]", session->GetId());
}

void Network::Connection::RemoveSession(Network::TSessionId id)
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

std::shared_ptr<Session> Network::Connection::GetSession(Network::TSessionId sessionId)
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

void Network::Connection::StartSession(Network::TSessionId sessionId)
{
    auto session = GetSession(sessionId);
    if (session)
    {
        session->Start();
    }
}

void Network::Connection::StopSession(Network::TSessionId sessionId)
{
    auto session = GetSession(sessionId);
    if (session)
    {
        session->Stop();
    }
}
}

