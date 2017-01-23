#pragma once

#include "DeserializerBase.h"

class Deserializer : public DeserializerBase
{
public:
    Deserializer(const std::shared_ptr<Blob>& blob);

};