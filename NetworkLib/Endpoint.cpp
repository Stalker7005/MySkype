#include "Endpoint.h"

namespace Network {

Endpoint::Endpoint(TTcpResolverIter iter)
{
    Set(iter);
}

Endpoint::Endpoint(TUdpResolverIter iter)
{
    Set(iter);
}

Endpoint::Endpoint(const TTcpEndpoint& endpoint)
{
    Set(endpoint);
}

Endpoint::Endpoint(const TUdpEndpoint& endpoint)
{
    Set(endpoint);
}

void Endpoint::Set(TTcpResolverIter iter)
{
    m_tcpIter = iter;
}

void Endpoint::Set(TUdpResolverIter iter)
{
    m_updIter = iter;
}

void Endpoint::Set(const TTcpEndpoint& endpoint)
{
    m_tcpEndpoint = endpoint;
}

void Endpoint::Set(const TUdpEndpoint& endpoint)
{
    m_updEndpoint = endpoint;
}

void Endpoint::Get(TTcpEndpoint& endpoint) const
{
    endpoint = m_tcpEndpoint;
}

void Endpoint::Get(TTcpResolverIter& iter) const
{
    iter = m_tcpIter;
}

void Endpoint::Get(TUdpEndpoint& endpoint) const
{
    endpoint = m_updEndpoint;
}

void Endpoint::Get(TUdpResolverIter& iter) const
{
    iter = m_updIter;
}

}

