#include "ClientRegistration.h"

namespace NetworkUtils {

ClientRegistration::ClientRegistration()
: NetworkMessage(MessageType::REGISTRATION)
{

}

void ClientRegistration::SetFirstName(const std::wstring& firstName)
{
    m_firstName = firstName;
}

std::wstring ClientRegistration::GetFirstName() const
{
    return m_firstName;
}

void ClientRegistration::SetSecondName(const std::wstring& secondName)
{
    m_secondName = secondName;
}

std::wstring ClientRegistration::GetSecondName() const
{
    return m_secondName;
}

void ClientRegistration::SetAge(std::uint32_t age)
{
    m_age = age;
}

std::uint32_t ClientRegistration::GetAge() const
{
    return m_age;
}

void ClientRegistration::SetPassword(const std::wstring& password)
{
    m_password = password;
}

std::wstring ClientRegistration::GetPassword() const
{
    return m_password;
}

void ClientRegistration::SetLoginName(const std::wstring& loginName)
{
    m_loginName = loginName;
}

std::wstring ClientRegistration::GetLoginName() const
{
    return m_loginName;
}

void ClientRegistration::SetGroupsTags(const std::vector<TGroupTag>& groupsTags)
{
    m_groupsTags = groupsTags;
}

std::vector<TGroupTag> ClientRegistration::GetGroupsTags() const
{
    return m_groupsTags;
}

}

