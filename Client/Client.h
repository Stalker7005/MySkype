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

using boost::asio::ip::tcp;

class Client : public ThreadsUtils::RunningContext,
    public std::enable_shared_from_this<Client>
{
public:
    Client(boost::asio::io_service& io_service,
        tcp::resolver::iterator endpoint_iterator);

    void Post(const std::shared_ptr<Blob>& blob);

protected:
    bool StartInternal() override;
    bool StopInternal() override;
    bool IsCanStart() override;

private:
    void DoConnect(tcp::resolver::iterator endpointIterator);
    void OnRead(const std::shared_ptr<Blob>& blob);

private:
    boost::asio::io_service& m_ioService;
    boost::signals2::scoped_connection m_readConnection;
    std::unique_ptr<Network::Connection> m_connection;

};