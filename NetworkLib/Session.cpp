#include "Session.h"

namespace Network {
Session::Session(NetworkUtils::TSessionId sessionId)
: m_sessionId(sessionId)
{
}

Session::~Session()
{
}

NetworkUtils::TSessionId Session::GetId() const
{
    return m_sessionId;
}

}

