#pragma once

#include "Common.h"

class ISerializable;

class DeserializerBase
{
public:
    typedef boost::uint32_t TSize;
    typedef std::function<void(const std::uint8_t* data, size_t size)> TGetter;

public:
    DeserializerBase(const void* data, size_t size);

    DeserializerBase& GetFixed(void* get, size_t size);
    DeserializerBase& Get(std::uint8_t&  data);
    DeserializerBase& Get(std::uint16_t& data);
    DeserializerBase& Get(std::uint32_t& data);
    DeserializerBase& Get(std::uint64_t& data);
    DeserializerBase& Get(std::int8_t&  data);
    DeserializerBase& Get(std::int16_t& data);
    DeserializerBase& Get(std::int32_t& data);
    DeserializerBase& Get(std::int64_t& data);
    DeserializerBase& Get(bool& data);

    DeserializerBase& GetSized(TGetter getter);
    DeserializerBase& Get(Blob& blob);
    DeserializerBase& Get(ISerializable& serializable);

    DeserializerBase& GetSize(size_t& size);

    template<class T>
    typename std::enable_if<std::is_enum<T>::value, DeserializerBase&>::type Get(T& data)
    {
        return GetFixed(&data, sizeof(data));
    }

    template<class _Elem, class _Traits, class _Alloc>
    DeserializerBase& Get(std::basic_string<_Elem, _Traits, _Alloc>& string)
    {
        return GetSized([&](const boost::uint8_t* data, size_t size) {
            string.assign(reinterpret_cast<const _Elem*>(data), size / sizeof(_Elem));
        });
    }

    template<class T>
    DeserializerBase& Get(boost::shared_ptr<T>& object)
    {
        object = boost::make_shared<T>();
        return Get(*object);
    }
    template<class T>
    DeserializerBase& Get(std::unique_ptr<T>& object)
    {
        object = std::make_unique<T>();
        return Get(*object);
    }
    template<class T>
    DeserializerBase& Get(std::vector<T>& container)
    {
        return GetContainerSingle(container);
    }
    template<class T>
    DeserializerBase& Get(std::deque<T>& container)
    {
        return GetContainerSingle(container);
    }
    template<class T>
    DeserializerBase& Get(std::list<T>& container)
    {
        return GetContainerSingle(container);
    }
    template<class T>
    DeserializerBase& Get(std::set<T>& container)
    {
        return GetContainerSingleSet(container);
    }
    template<class T>
    DeserializerBase& Get(std::unordered_set<T>& container)
    {
        return GetContainerSingleSet(container);
    }
    template<class T>
    DeserializerBase& Get(boost::unordered_set<T>& container)
    {
        return GetContainerSingleSet(container);
    }
    template<class K, class V>
    DeserializerBase& Get(std::map<K, V>& container)
    {
        return GetContainerPaired(container);
    }
    template<class T, class P, class A>
    DeserializerBase& Get(std::set<T, P, A>& container)
    {
        return GetContainerSingleSet(container);
    }
    template<class K, class V>
    DeserializerBase& Get(std::unordered_map<K, V>& container)
    {
        return GetContainerPaired(container);
    }
    template<class K, class V>
    DeserializerBase& Get(boost::unordered_map<K, V>& container)
    {
        return GetContainerPaired(container);
    }

protected:
    size_t Used() const;

    template<class T>
    DeserializerBase& GetContainerSingle(T& container)
    {
        size_t size;
        GetSize(size);

        for (size_t i = 0; i < size; i++)
        {
            typename T::value_type value;
            Get(value);
            container.emplace(container.end(), value);
        }
        return *this;
    }

    template<class T>
    DeserializerBase& GetContainerSingleSet(T& container)
    {
        size_t size;
        GetSize(size);

        for (size_t i = 0; i < size; i++)
        {
            typename T::value_type value;
            Get(value);
            container.emplace(value);
        }
        return *this;
    }

    template<class T>
    DeserializerBase& GetContainerPaired(T& container)
    {
        size_t size;
        GetSize(size);

        for (size_t i = 0; i < size; i++)
        {
            typename T::key_type key;
            typename T::mapped_type mapped;
            Get(key);
            Get(mapped);
            container.emplace(key, mapped);
        }
        return *this;
    }

    const std::uint8_t* const m_base;
    const std::uint8_t* m_data;
    const size_t m_size;
};