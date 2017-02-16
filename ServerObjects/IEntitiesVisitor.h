#pragma once
#include <memory>

namespace Entities {
class Client;
class UsersGroup;

class IEntitiesVisitor
{
public:
    virtual void VisitUser(std::shared_ptr<Entities::Client>& user) = 0;
    virtual void VisitGroup(std::shared_ptr<Entities::UsersGroup>& group) = 0;
};
}


