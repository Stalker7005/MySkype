#include <cstdlib>
#include <memory>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

#include "Blob.h"
#include "Serializer.h"
#include "NetworkMessage.h"
#include "Connection.h"
#include "TCPSession.h"
#include "RunningContext.h"
#include "NetworkDefs.h"

using boost::asio::ip::tcp;

class Client : public ThreadsUtils::RunningContext,
    public std::enable_shared_from_this<Client>
{
public:
    Client(boost::asio::io_service& io_service,
        tcp::resolver::iterator endpoint_iterator);

    void Post(Network::TSessionId id, const std::shared_ptr<Blob>& blob);

protected:
    bool StartInternal() override;
    bool StopInternal() override;
    bool IsCanStart() override;

private:
    void OnSendData(Network::TSessionId id, const std::shared_ptr<Blob>& blob);

private:
    boost::asio::io_service& m_ioService;
    boost::signals2::scoped_connection m_readConnection;
    std::shared_ptr<Network::Connection> m_connection;

};