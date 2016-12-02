#pragma once

#include <memory>
#include "IEntitiesVisitor.h"

namespace Entities {
class IBaseEntity
{
public:
    virtual void Fill(std::shared_ptr<IEntitiesVisitor>& visitor) = 0;
    virtual void Clear() = 0;
};
}

