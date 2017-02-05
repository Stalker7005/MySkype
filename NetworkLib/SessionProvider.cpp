#include "SessionProvider.h"

namespace Network {

Network::SessionProvider::TConnection SessionProvider::AddRecvListener(TReadCallback::slot_function_type slot)
{
    return m_readCallback.connect(slot);
}

Network::SessionProvider::TConnection SessionProvider::AddCloseListener(TCloseConnectionCallback::slot_function_type slot)
{
    return m_closeConnectionCallback.connect(slot);
}

void SessionProvider::FireRecv(const std::shared_ptr<Blob>& blob)
{
    m_readCallback(blob);
}

void SessionProvider::FireClose(TSessionId id)
{
    m_closeConnectionCallback(id);
}

}

