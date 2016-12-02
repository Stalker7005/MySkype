#pragma once
#include <boost/asio.hpp>

namespace Network {
class Endpoint
{
public:
    using TTcpResolverIter = boost::asio::ip::tcp::resolver::iterator;
    using TUdpResolverIter = boost::asio::ip::udp::resolver::iterator;
    using TTcpEndpoint = boost::asio::ip::tcp::endpoint;
    using TUdpEndpoint = boost::asio::ip::udp::endpoint;

public:
    Endpoint(TTcpResolverIter iter);
    Endpoint(TUdpResolverIter iter);
    Endpoint(const TTcpEndpoint& endpoint);
    Endpoint(const TUdpEndpoint& endpoint);
    ~Endpoint() = default;

public:
    void Set(TTcpResolverIter iter);
    void Set(TUdpResolverIter iter);
    void Set(const TTcpEndpoint& endpoint);
    void Set(const TUdpEndpoint& endpoint);

public:
    void Get(TTcpEndpoint& endpoint) const;
    void Get(TTcpResolverIter& iter) const;
    void Get(TUdpEndpoint& endpoint) const;
    void Get(TUdpResolverIter& iter) const;

private:
    TTcpEndpoint m_tcpEndpoint;
    TUdpEndpoint m_updEndpoint;
    TTcpResolverIter m_tcpIter;
    TUdpResolverIter m_updIter;
};
}


