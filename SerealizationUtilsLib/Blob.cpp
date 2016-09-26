#include "Blob.h"

namespace Serialization{

const std::uint64_t Blob::DefaultBlobSize = 64;

Blob::Blob(): Blob{DefaultBlobSize}
{
    
}

Blob::Blob(std::uint64_t size):
m_blobSize(size)
{
    Reserve(size);
}

Blob::~Blob()
{
    Dispose();
}

void Blob::Reserve(std::uint64_t size)
{
    m_dataSize = size;

    if (m_data)
    {
        if (size > m_blobSize)
        {
            m_data = std::make_unique<char[]>(size);
            m_blobSize = size;
        }
        else
        {
            ClearData();
        }
    }
    else
    {
        m_data = std::make_unique<char[]>(size);
        m_blobSize = size;
    }
}

char* Blob::GetData() const
{
    return m_data.get();
}

std::uint64_t Blob::Size() const
{
    return m_dataSize;
}

void Blob::Dispose()
{
    m_data.reset();
}

void Blob::SetData(const char* data, std::uint64_t size)
{
    Reserve(size);
    std::memcpy(m_data.get(), data, size * sizeof(char));
}

void Blob::ClearData()
{
    std::memset(m_data.get(), 0, m_blobSize * sizeof(char));
}

}