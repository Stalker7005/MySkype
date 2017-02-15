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
    auto iter = m_sessions.find(session->GetId());
    if (iter == m_sessions.end())
    {
        session->AddRecvDataListener(std::bind(&Connection::OnRecvData, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
        session->AddCloseSessionListener(std::bind(&Connection::OnCloseSession, shared_from_this(), std::placeholders::_1));
        m_sessions.emplace(std::make_pair(session->GetId(), session));
        LOG_INFO("Added session with id:[%d]", session->GetId());
    }
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
        LOG_WARN("Can't find session to remove: %d", id);
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
    else
    {
        LOG_ERR("Can't stop session with id: %d", sessionId);
    }
}

void Network::Connection::StopSession(Network::TSessionId sessionId)
{
    auto session = GetSession(sessionId);
    if (session)
    {
        session->Stop();
    }
    else
    {
        LOG_ERR("Can't start session with id: %d", sessionId);
    }
}

void Connection::OnRecvData(TSessionId id, const std::shared_ptr<Blob>& blob)
{
    auto session = GetSession(id);
    if (session)
    {
        FireSendData(id, blob);
    }
    else
    {
        LOG_ERR("Can't post message to session with id: %d", id);
    }
}

void Connection::OnCloseSession(TSessionId id)
{
    auto session = GetSession(id);
    if (session)
    {
        session->Stop();
        RemoveSession(id);
    }
    else
    {
        LOG_ERR("Can't close session with id: %d", id);
    }
}

void Connection::OnSendData(TSessionId sessionId, const std::shared_ptr<Blob>& blob)
{
    auto session = GetSession(sessionId);
    if (session)
    {
        session->Post(blob);
    }
    else
    {
        LOG_ERR("Can't send data to session with id: %d", sessionId);
    }
}

void Connection::SendData(TSessionId sessionId, const std::shared_ptr<Blob>& blob)
{
    auto session = GetSession(sessionId);
    if(session)
    {
        session->Post(blob);
    }
    else
    {
        LOG_ERR("Can't send data");
    }
}

}

