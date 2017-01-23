#include "stdafx.h"
#include "DeserializerBase.h"
#include <stdexcept>
#include "ISerializable.h"

DeserializerBase::DeserializerBase(const void* data, size_t size)
    : m_base(static_cast<const boost::uint8_t* const>(data))
    , m_data(static_cast<const boost::uint8_t*>(data))
    , m_size(size)
{
    if (!m_data || !m_size)
    {
        throw std::invalid_argument("invalid_argument");
    }
}

size_t DeserializerBase::Used() const
{
    return m_data - m_base;
}

DeserializerBase& DeserializerBase::GetFixed(void* get, size_t size)
{
    if (Used() + size <= m_size)
    {
        memcpy(get, m_data, size);
        m_data += size;
        return *this;
    }
    else
    {
        throw std::out_of_range("out_of_range");
    }
}

DeserializerBase& DeserializerBase::Get(std::uint8_t& data)
{
    return GetFixed(&data, sizeof(data));
}

DeserializerBase& DeserializerBase::Get(std::uint16_t& data)
{
    return GetFixed(&data, sizeof(data));
}

DeserializerBase& DeserializerBase::Get(std::uint32_t& data)
{
    return GetFixed(&data, sizeof(data));
}

DeserializerBase& DeserializerBase::Get(std::uint64_t& data)
{
    return GetFixed(&data, sizeof(data));
}

DeserializerBase& DeserializerBase::Get(std::int8_t& data)
{
    return GetFixed(&data, sizeof(data));
}

DeserializerBase& DeserializerBase::Get(std::int16_t& data)
{
    return GetFixed(&data, sizeof(data));
}

DeserializerBase& DeserializerBase::Get(std::int32_t& data)
{
    return GetFixed(&data, sizeof(data));
}

DeserializerBase& DeserializerBase::Get(std::int64_t& data)
{
    return GetFixed(&data, sizeof(data));
}

DeserializerBase& DeserializerBase::Get(bool& data_)
{
    boost::uint8_t data;
    Get(data);
    data_ = data ? true : false;
    return *this;
}

DeserializerBase& DeserializerBase::GetSize(size_t& size)
{
    if (Used() + sizeof(TSize) <= m_size)
    {
        auto sizeRaw = *reinterpret_cast<const TSize*>(m_data);
        size = static_cast<size_t>(sizeRaw);
        m_data += sizeof(sizeRaw);
        return *this;
    }
    else
    {
        throw std::out_of_range("out_of_range");
    }
}

DeserializerBase& DeserializerBase::GetSized(TGetter getter)
{
    size_t size;
    GetSize(size);
    
    if (Used() + size <= m_size)
    {
        getter(m_data, size);
        m_data += size;
        return *this;
    }
    else
    {
        throw std::out_of_range("out_of_range");
    }
}

DeserializerBase& DeserializerBase::Get(Blob& blob)
{
    return GetSized([&](const std::uint8_t* data, size_t size){
        blob.SetData(data, size);
    });
}

DeserializerBase& DeserializerBase::Get(ISerializable& serializable)
{
    serializable.Deserialize(*this);
    return *this;
}
