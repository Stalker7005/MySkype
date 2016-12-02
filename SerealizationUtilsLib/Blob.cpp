#include "Blob.h"

namespace Serialization{

const std::uint64_t Blob::DefaultBlobSize = 64;

Blob::Blob(): Blob{DefaultBlobSize}
{
}

Blob::Blob(std::uint64_t size):
m_blobSize(size)
{
    Resize(size);
}

Blob::Blob(const void* data, std::uint64_t size)
{
    SetData(data, size);
}

Blob::Blob(const Blob& blob)
{
    SetData(blob.GetData(), blob.Size());
}

Blob::Blob(Blob&& blob)
: m_data(std::move(blob.m_data))
, m_blobSize(blob.m_blobSize)
{
    blob.m_blobSize = 0;
}

Blob& Blob::operator=(Blob&& blob)
{
    m_data = std::move(blob.m_data);
    m_blobSize = blob.m_blobSize;
    blob.m_blobSize = 0;

    return *this;
}

Blob& Blob::operator=(const Blob& blob)
{
    SetData(blob.m_data.get(), blob.m_blobSize);

    return *this;
}

bool Blob::operator==(const Blob& blob)
{
    if (m_blobSize == blob.m_blobSize)
    {
        return memcmp(m_data.get(), blob.m_data.get(), m_blobSize);
    }

    return false;
}

bool Blob::operator!=(const Blob& blob)
{
    return !Blob::operator==(blob);
}

Blob::operator bool()
{
    return m_data.get() != nullptr;
}

void Blob::Resize(std::uint64_t size, bool saveData /*= false*/)
{
    m_dataSize = size;

    if (m_data)
    {
        if (size > m_blobSize)
        {
            if (saveData)
            {
                auto prevData = std::move(m_data);
                auto prevSize = m_blobSize;
                m_data = std::make_unique<std::uint8_t[]>(size);
                m_blobSize = size;
                ClearData();

                memcpy(m_data.get(), prevData.get(), prevSize);
            }
            else
            {
                m_data = std::make_unique<std::uint8_t[]>(size);
                m_blobSize = size;
                ClearData();
            }
            
        }
    }
    else
    {
        m_data = std::make_unique<std::uint8_t[]>(size);
        m_blobSize = size;
        ClearData();
    }
}

std::uint8_t* Blob::GetData() const
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

void Blob::SetData(const void* data, std::uint64_t size)
{
    Resize(size);
    std::memcpy(m_data.get(), data, size);
}

void Blob::ClearData()
{
    std::memset(m_data.get(), 0, m_blobSize);
}

}