#pragma once
#include <memory>

namespace Entities {
class User;

class IEntitiesVisitor
{
public:
    virtual void VisitUser(std::shared_ptr<Entities::User>& user) = 0;
};
}


