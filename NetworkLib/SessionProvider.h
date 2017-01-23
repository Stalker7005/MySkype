#pragma once
#include "NetworkMessage.h"
#include <memory>
#include <boost/signals2.hpp>


namespace Network {
class SessionProvider
{
public: 
    using TReadCallback = boost::signals2::signal<void(const std::shared_ptr<NetworkMessage>&)>;
    using TConnection = boost::signals2::connection;

public:
    TConnection AddReadListener(TReadCallback::slot_function_type slot);

protected:
    void FireReadListener(const std::shared_ptr<NetworkMessage>& message);

private:
    TReadCallback m_readCallback;
};
}

