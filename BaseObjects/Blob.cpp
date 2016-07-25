#include "Blob.h"

namespace BaseObjects {

Blob::Blob()
{
    m_buffer.exceptions(0);
}

Blob::~Blob()
{

}

void Blob::Clear()
{
    m_buffer.clear();
    m_buffer.str("");
}

std::stringstream& Blob::GetStream()
{
    return m_buffer;
}

const char* Blob::GetCString()
{
    return m_buffer.str().c_str();
}

std::string Blob::GetString()
{
    return m_buffer.str();
}

}