#include "User.h"
namespace Entities {

void User::SetFirstName(const std::wstring& firstName)
{
    m_firstName = firstName;
}

std::wstring User::GetFirstName() const
{
    return m_firstName;
}

void User::SetSecondName(const std::wstring& secondName)
{
    m_secondName = secondName;
}

std::wstring User::GetSecondName() const
{
    return m_secondName;
}

void User::SetAge(std::uint32_t age)
{
    m_age = age;
}

std::uint32_t User::GetAge() const
{
    return m_age;
}

void User::SetPassword(const std::wstring& password)
{
    m_password = password;
}

std::wstring User::GetPassword() const
{
    return m_password;
}

void User::SetLoginName(const std::wstring& loginName)
{
    m_loginName = loginName;
}

std::wstring User::GetLoginName() const
{
    return m_loginName;
}

void User::SetGroupsTags(const std::vector<std::wstring>& groupsTagc)
{
    m_groupsTags = groupsTagc;
}

std::vector<std::wstring> User::GetGroupsTags() const
{
    return m_groupsTags;
}

void User::Fill(std::shared_ptr<IEntitiesVisitor>& visitor)
{
    visitor->VisitUser(shared_from_this());
}

void User::Clear()
{
    m_firstName.clear();
    m_secondName.clear();
    m_age = 0;
    m_password.clear();
    m_loginName.clear();
    m_groupsTags.clear();
}

User::User():
m_age(0)
{

}

void User::SetUserState(UserState state)
{
    m_userState = state;
}

Entities::User::UserState User::GetUserState() const
{
    return m_userState;
}

}