#include "stdafx.h"
#include "Deserializer.h"

Deserializer::Deserializer(const std::shared_ptr<Blob>& blob) 
: DeserializerBase(blob->GetData(), blob->GetSize())
{

}
