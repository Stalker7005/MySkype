#include "ClientRegistrationMessage.h"

namespace Network {

ClientRegistrationMessage::ClientRegistrationMessage()
: NetworkMessage(MessageType::REGISTRATION)
{

}

void ClientRegistrationMessage::SetFirstName(const std::wstring& firstName)
{
    m_firstName = firstName;
}

std::wstring ClientRegistrationMessage::GetFirstName() const
{
    return m_firstName;
}

void ClientRegistrationMessage::SetSecondName(const std::wstring& secondName)
{
    m_secondName = secondName;
}

std::wstring ClientRegistrationMessage::GetSecondName() const
{
    return m_secondName;
}

void ClientRegistrationMessage::SetAge(std::uint32_t age)
{
    m_age = age;
}

std::uint32_t ClientRegistrationMessage::GetAge() const
{
    return m_age;
}

void ClientRegistrationMessage::SetPassword(const std::wstring& password)
{
    m_password = password;
}

std::wstring ClientRegistrationMessage::GetPassword() const
{
    return m_password;
}

void ClientRegistrationMessage::SetLoginName(const std::wstring& loginName)
{
    m_loginName = loginName;
}

std::wstring ClientRegistrationMessage::GetLoginName() const
{
    return m_loginName;
}

void ClientRegistrationMessage::SetGroupsTags(const std::vector<TGroupTag>& groupsTags)
{
    m_groupsTags = groupsTags;
}

std::vector<TGroupTag> ClientRegistrationMessage::GetGroupsTags() const
{
    return m_groupsTags;
}

void ClientRegistrationMessage::Serialize(SerializerBase& serializer) const
{
    NetworkMessage::Serialize(serializer);

    serializer.Add(m_firstName).Add(m_secondName).Add(m_age).Add(m_password).Add(m_loginName);
}

void ClientRegistrationMessage::Deserialize(DeserializerBase& deserializer)
{
    NetworkMessage::Deserialize(deserializer);

    deserializer.Get(m_firstName).Get(m_secondName).Get(m_age).Get(m_password).Get(m_loginName);
}

std::uint64_t ClientRegistrationMessage::GetSizeInternal() const
{
    return m_firstName.size() + m_secondName.size() + m_age + m_password.size() + m_loginName.size();
}

}

