#pragma once
#include "Blob.h"
#include "NetworkDefs.h"
#include <memory>
#include <boost/signals2.hpp>


namespace Network {
class SessionProvider
{
public: 
    using TReadCallback = boost::signals2::signal<void(const std::shared_ptr<Blob>&)>;
    using TCloseConnectionCallback = boost::signals2::signal<void(TSessionId)>;
    using TConnection = boost::signals2::connection;

public:
    virtual void Post(const std::shared_ptr<Blob>& blob) = 0;
    TConnection AddRecvListener(TReadCallback::slot_function_type slot);
    TConnection AddCloseListener(TCloseConnectionCallback::slot_function_type slot);

protected:
    void FireRecv(const std::shared_ptr<Blob>& message);
    void FireClose(TSessionId id);

private:
    TReadCallback m_readCallback;
    TCloseConnectionCallback m_closeConnectionCallback;
};
}

