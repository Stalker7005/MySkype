#include "Client.h"
namespace Entities {

void Client::SetFirstName(const std::wstring& firstName)
{
    m_firstName = firstName;
}

std::wstring Client::GetFirstName() const
{
    return m_firstName;
}

void Client::SetSecondName(const std::wstring& secondName)
{
    m_secondName = secondName;
}

std::wstring Client::GetSecondName() const
{
    return m_secondName;
}

void Client::SetAge(std::uint32_t age)
{
    m_age = age;
}

std::uint32_t Client::GetAge() const
{
    return m_age;
}

void Client::SetPassword(const std::wstring& password)
{
    m_password = password;
}

std::wstring Client::GetPassword() const
{
    return m_password;
}

void Client::SetLoginName(const std::wstring& loginName)
{
    m_loginName = loginName;
}

std::wstring Client::GetLoginName() const
{
    return m_loginName;
}

void Client::SetGroupsTags(const std::vector<std::wstring>& groupsTagc)
{
    m_groupsTags = groupsTagc;
}

std::vector<std::wstring> Client::GetGroupsTags() const
{
    return m_groupsTags;
}

void Client::Fill(std::shared_ptr<IEntitiesVisitor>& visitor)
{
    visitor->VisitUser(shared_from_this());
}

void Client::Clear()
{
    m_firstName.clear();
    m_secondName.clear();
    m_age = 0;
    m_password.clear();
    m_loginName.clear();
    m_groupsTags.clear();
}

Client::Client():
m_age(0)
{

}

void Client::SetUserState(UserState state)
{
    m_userState = state;
}

Entities::Client::UserState Client::GetUserState() const
{
    return m_userState;
}

}
