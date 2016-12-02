#include "SessionRole.h"

namespace Network {

SessionRole::SessionRole(const std::shared_ptr<boost::asio::io_service>& ioService)
: m_ioService(ioService)
{

}

}

