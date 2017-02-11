#include "SessionSendProvider.h"

namespace Network {

SessionSendProvider::TConnection SessionSendProvider::AddSendListener(TSendCallback::slot_function_type subscriber)
{
    return m_sendCallback.connect(subscriber);
}

void SessionSendProvider::FireSendData(TSessionId sessionId, const std::shared_ptr<Blob>& blob)
{
    m_sendCallback(sessionId, blob);
}

}
