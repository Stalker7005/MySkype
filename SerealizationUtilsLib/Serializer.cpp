#include "Serializer.h"

namespace Serialization {

Serializer::Serializer(Type serializeType /*= Type::PortableBinary*/):
m_type(serializeType)
{
}

Serializer::~Serializer()
{}

void Serializer::ClearDataStream()
{
    m_dataStream.clear();
    m_dataStream.str("");
}
}


