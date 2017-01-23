#pragma once

#include "Common.h"

class ISerializable;

class SerializerBase
{
public:
    typedef std::uint32_t TSize;

public:

    SerializerBase& AddFixed(const void* data, size_t size);
    SerializerBase& Add(std::uint8_t  data);
    SerializerBase& Add(std::uint16_t data);
    SerializerBase& Add(std::uint32_t data);
    SerializerBase& Add(std::uint64_t data);
    SerializerBase& Add(std::int8_t  data);
    SerializerBase& Add(std::int16_t data);
    SerializerBase& Add(std::int32_t data);
    SerializerBase& Add(std::int64_t data);
    SerializerBase& Add(bool data);

    SerializerBase& AddSized(const void* data, size_t size);

    SerializerBase& Add(const Blob& blob);
    SerializerBase& Add(const ISerializable& serializable);

    template<class T>
    typename std::enable_if<std::is_enum<T>::value, SerializerBase&>::type Add(const T& data)
    {
        return AddFixed(&data, sizeof(data));
    }

    template<class _Elem, class _Traits, class _Alloc>
    SerializerBase& Add(const std::basic_string<_Elem, _Traits, _Alloc>& string)
    {
        return AddSized(string.data(), string.size()*sizeof(_Elem));
    }

    template<class T>
    SerializerBase& Add(const boost::shared_ptr<T>& object)
    {
        return Add(*object);
    }
    template<class T>
    SerializerBase& Add(const std::unique_ptr<T>& object)
    {
        return Add(*object);
    }
    template<class T>
    SerializerBase& Add(const std::vector<T>& container)
    {
        return AddContainerSingle(container);
    }
    template<class T>
    SerializerBase& Add(const std::deque<T>& container)
    {
        return AddContainerSingle(container);
    }
    template<class T>
    SerializerBase& Add(const std::list<T>& container)
    {
        return AddContainerSingle(container);
    }
    template<class T, class P, class A>
    SerializerBase& Add(const std::set<T, P, A>& container)
    {
        return AddContainerSingle(container);
    }

    template<class T>
    SerializerBase& Add(const std::unordered_set<T>& container)
    {
        return AddContainerSingle(container);
    }
    template<class T>
    SerializerBase& Add(const boost::unordered_set<T>& container)
    {
        return AddContainerSingle(container);
    }
    template<class K, class V>
    SerializerBase& Add(const std::map<K, V>& container)
    {
        return AddContainerPaired(container);
    }
    template<class K, class V>
    SerializerBase& Add(const std::unordered_map<K, V>& container)
    {
        return AddContainerPaired(container);
    }
    template<class K, class V>
    SerializerBase& Add(const boost::unordered_map<K, V>& container)
    {
        return AddContainerPaired(container);
    }

protected:
    size_t Used() const;
    virtual void Resize(size_t size) = 0;

    SerializerBase& AddSize(size_t size);

    template<class T>
    SerializerBase& AddContainerSingle(const T& container)
    {
        AddSize(container.size());
        for (const auto& value : container)
        {
            Add(value);
        }
        return *this;
    }

    template<class T>
    SerializerBase& AddContainerPaired(const T& container)
    {
        AddSize(container.size());
        for (const auto& value : container)
        {
            Add(value.first);
            Add(value.second);
        }
        return *this;
    }

    const std::uint8_t* m_base;
    std::uint8_t* m_data;
    size_t m_size;
};
