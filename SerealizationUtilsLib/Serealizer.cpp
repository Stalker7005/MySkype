#include "Serealizer.h"
#include "BinarySerializer.h"
#include "JSONSerializer.h"
#include "XMLSerializer.h"

namespace Serialization {

Serializer::Serializer()
{

}

Serializer::Serializer(Type serializerType)
{
    ChangeSerealizer(serializerType);
}

Serializer::~Serializer()
{

}

void Serializer::SetType(Type serializerType)
{
    ChangeSerealizer(serializerType);
}

void Serializer::ChangeSerealizer(Type type)
{
    switch (type)
    {
    case Serialization::Serializer::Type::BINARY:
        m_self = std::make_shared<BinarySerializer>();
        break;
    case Serialization::Serializer::Type::JSON:
        m_self = std::make_shared<JSONSerizlier>();
        break;
    case Serialization::Serializer::Type::XML:
        m_self = std::make_shared<XMLSerializer>();
        break;
    default:
        //TODO add logger
        break;
    }
}

}