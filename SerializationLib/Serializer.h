#pragma once

#include "SerializerBase.h"

class Serializer : public SerializerBase
{
public:
    typedef boost::uint32_t TSize;

public:
    Serializer();
    Serializer(size_t size);

    std::shared_ptr<Blob> GetBlob();

protected:
    virtual void Resize(size_t size);

    std::shared_ptr<Blob> m_blob;
};