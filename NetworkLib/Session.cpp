#include "Session.h"

namespace Network {
Session::Session(Network::TSessionId sessionId)
: m_sessionId(sessionId)
{
}

Session::~Session()
{
}

Network::TSessionId Session::GetId() const
{
    return m_sessionId;
}

}

