#include "stdafx.h"
#include "Serializer.h"

Serializer::Serializer() : m_blob(std::make_shared<Blob>(4096))
{
    m_base = m_blob->GetData();
    m_data = m_blob->GetData();
    m_size = m_blob->GetSize();
}

Serializer::Serializer(size_t size): m_blob(std::make_shared<Blob>(size))
{
    m_base = m_blob->GetData();
    m_data = m_blob->GetData();
    m_size = m_blob->GetSize();
}

std::shared_ptr<Blob> Serializer::GetBlob()
{
    m_blob->Resize(Used());
    return m_blob;
}

void Serializer::Resize(size_t size)
{
    auto used = Used();
    m_blob->Resize(size * 2, true);
    m_base = m_blob->GetData();
    m_data = m_blob->GetData() + used;
    m_size = m_blob->GetSize();
}
