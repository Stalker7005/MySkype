#include "SessionProvider.h"

namespace Network {

Network::SessionProvider::TConnection SessionProvider::AddRecvDataListener(TReadCallback::slot_function_type slot)
{
    return m_readCallback.connect(slot);
}

Network::SessionProvider::TConnection SessionProvider::AddCloseSessionListener(TCloseConnectionCallback::slot_function_type slot)
{
    return m_closeConnectionCallback.connect(slot);
}

void SessionProvider::FireRecvData(TSessionId sesionId, const std::shared_ptr<Blob>& blob)
{
    m_readCallback(sesionId, blob);
}

void SessionProvider::FireCloseSession(TSessionId id)
{
    m_closeConnectionCallback(id);
}

}

