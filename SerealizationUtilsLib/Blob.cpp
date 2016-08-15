#include "Blob.h"

namespace Serialization{
const std::uint64_t Blob::DefaultBlobSize = 64;

Blob::Blob(): Blob{DefaultBlobSize}
{
    
}

Blob::Blob(std::uint64_t size):
m_blobSize(size)
{
    Allocate(size);
}

Blob::~Blob()
{
    Clear();
}

void Blob::Allocate(std::uint64_t size)
{
    if (size > m_blobSize)
    {
        m_dataBuf = std::make_unique<std::uint8_t[]>(size);
        m_blobSize = size;
    }
    else
    {
        std::memset(m_dataBuf.get(), 0, m_blobSize * sizeof(std::uint8_t));
    }
    
}

std::uint8_t* Blob::GetDataBuf()
{

}

std::iostream& Blob::GetDataStream()
{
    auto& stream = m_dataStream.write(reinterpret_cast<const char*>(m_dataStream.get()), m_blobSize * sizeof(std::uint8_t));
    if (!stream)
    {
        //TODO log error!
    }
    return m_dataStream;
}

std::uint64_t Blob::Size() const
{
    return m_blobSize;
}

void Blob::Clear()
{
    m_dataBuf.reset();
    m_dataStream.clear();
    m_dataStream.str("");
}

}