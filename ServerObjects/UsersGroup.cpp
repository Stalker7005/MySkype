#include "UsersGroup.h"

namespace Entities {

UsersGroup::UsersGroup()
{}

UsersGroup::~UsersGroup()
{}

void UsersGroup::Fill(std::shared_ptr<IEntitiesVisitor>& visitor)
{
    visitor->VisitGroup(shared_from_this());
}

void UsersGroup::Clear()
{
    m_groupTag.clear();
    m_usersGroup.clear();
}

void UsersGroup::SetGroupTag(const TGroupTag& groupTag)
{
    m_groupTag = groupTag;
}

TGroupTag UsersGroup::GetGroupTag() const
{
    return m_groupTag;
}

void UsersGroup::AddUsers(const TUsersGroup& group)
{
    m_usersGroup = group;
}

UsersGroup::TUsersGroup UsersGroup::GetUsers() const
{
    return m_usersGroup;
}

}

