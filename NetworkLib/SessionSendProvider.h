#pragma once
#include <boost/signals2.hpp>
#include "NetworkDefs.h"
#include "Blob.h"

namespace Network {
class SessionSendProvider
{
public:
    using TConnection = boost::signals2::connection;
    using TSendCallback = boost::signals2::signal<void(TSessionId sesionId, const std::shared_ptr<Blob>&)>;

public:
    TConnection AddSendListener(TSendCallback::slot_function_type subscriber);

protected:
    void FireSendData(TSessionId sessionId, const std::shared_ptr<Blob>& blob);

private:
    TSendCallback m_sendCallback;
};
}

