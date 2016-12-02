#pragma once
#include <vector>
#include <memory>

#include "IBaseEntity.h"
#include "EntitiesDefs.h"
#include "CommonDefs.h"

namespace Entities {
class User;

class UsersGroup: public IBaseEntity,
                  public std::enable_shared_from_this<UsersGroup>
{
public:
    using TUser = std::shared_ptr<User>;
    using TUsersGroup = std::vector<TUser>;

public:
    UsersGroup();
    ~UsersGroup();

public:
    void SetGroupTag(const TGroupTag& groupTag);
    TGroupTag GetGroupTag() const;

    void AddUsers(const TUsersGroup& group);
    TUsersGroup GetUsers() const;

public:
    void Fill(std::shared_ptr<IEntitiesVisitor>& visitor) override;
    void Clear() override;

private:
    TGroupTag m_groupTag;
    TUsersGroup m_usersGroup;
};
}

