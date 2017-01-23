#include "SessionProvider.h"

namespace Network {

Network::SessionProvider::TConnection SessionProvider::AddReadListener(TReadCallback::slot_function_type slot)
{
    m_readCallback.connect(slot);
}

void SessionProvider::FireReadListener(const std::shared_ptr<NetworkMessage>& message)
{
    m_readCallback(message);
}

}

