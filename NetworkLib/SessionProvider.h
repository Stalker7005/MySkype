#pragma once
#include "Blob.h"
#include "NetworkDefs.h"
#include <memory>
#include <boost/signals2.hpp>


namespace Network {
class SessionProvider
{
public: 
    using TReadCallback = boost::signals2::signal<void(TSessionId sesionId, const std::shared_ptr<Blob>&)>;
    using TCloseConnectionCallback = boost::signals2::signal<void(TSessionId)>;
    using TConnection = boost::signals2::connection;

public:
    TConnection AddRecvDataListener(TReadCallback::slot_function_type slot);
    TConnection AddCloseSessionListener(TCloseConnectionCallback::slot_function_type slot);

protected:
    void FireRecvData(TSessionId sesionId, const std::shared_ptr<Blob>& message);
    void FireCloseSession(TSessionId id);

private:
    TReadCallback m_readCallback;
    TCloseConnectionCallback m_closeConnectionCallback;
};
}

