#pragma once
#include <memory>

namespace Entities {
class User;
class UsersGroup;

class IEntitiesVisitor
{
public:
    virtual void VisitUser(std::shared_ptr<Entities::User>& user) = 0;
    virtual void VisitGroup(std::shared_ptr<Entities::UsersGroup>& group) = 0;
};
}


