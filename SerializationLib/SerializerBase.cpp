#include "stdafx.h"
#include "SerializerBase.h"
#include "ISerializable.h"

size_t SerializerBase::Used() const
{
    return m_data - m_base;
}

SerializerBase& SerializerBase::AddFixed(const void* data, size_t size)
{
    if (Used() + size > m_size)
    {
        Resize(Used() + size);
    }

    memcpy(m_data, data, size);
    m_data += size;
    return *this;
}

SerializerBase& SerializerBase::Add(std::uint8_t data)
{
    return AddFixed(&data, sizeof(data));
}

SerializerBase& SerializerBase::Add(std::uint16_t data)
{
    return AddFixed(&data, sizeof(data));
}

SerializerBase& SerializerBase::Add(std::uint32_t data)
{
    return AddFixed(&data, sizeof(data));
}

SerializerBase& SerializerBase::Add(std::uint64_t data)
{
    return AddFixed(&data, sizeof(data));
}

SerializerBase& SerializerBase::Add(std::int8_t data)
{
    return AddFixed(&data, sizeof(data));
}

SerializerBase& SerializerBase::Add(std::int16_t data)
{
    return AddFixed(&data, sizeof(data));
}

SerializerBase& SerializerBase::Add(std::int32_t data)
{
    return AddFixed(&data, sizeof(data));
}

SerializerBase& SerializerBase::Add(std::int64_t data)
{
    return AddFixed(&data, sizeof(data));
}

SerializerBase& SerializerBase::Add(bool data_)
{
    boost::uint8_t data = data_ ? 1 : 0;
    return Add(data);
}

SerializerBase& SerializerBase::AddSize(size_t size_)
{
    auto size = static_cast<TSize>(size_);
    return AddFixed(&size, sizeof(size));
}

SerializerBase& SerializerBase::AddSized(const void* data, size_t size)
{
    return AddSize(size).AddFixed(data, size);
}

SerializerBase& SerializerBase::Add(const Blob& blob)
{
    return AddSized(blob.GetData(), blob.GetSize());
}

SerializerBase& SerializerBase::Add(const ISerializable& serializable)
{
    serializable.Serialize(*this);
    return *this;
}