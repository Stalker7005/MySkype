#include <cstdint>
#include <deque>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

namespace Clients {
class ChatClient
{
public:
    ChatClient(boost::asio::io_service& io_service);
};
}