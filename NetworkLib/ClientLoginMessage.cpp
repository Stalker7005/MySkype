#include "ClientLoginMessage.h"

namespace Network {

ClientLoginMessage::ClientLoginMessage()
: NetworkMessage(MessageType::LOGIN)
{

}

ClientLoginMessage::~ClientLoginMessage()
{

}

void ClientLoginMessage::SetPassword(const std::wstring& password)
{
    m_password = password;
}

std::wstring ClientLoginMessage::GetPassword() const
{
    return m_password;
}

void ClientLoginMessage::SetLoginName(const std::wstring& loginName)
{
    m_loginName = loginName;
}

std::wstring ClientLoginMessage::GetLoginName() const
{
    return m_loginName;
}

void ClientLoginMessage::Serialize(SerializerBase& serializer) const
{
    NetworkMessage::Serialize(serializer);
    serializer.Add(m_loginName).Add(m_password);
}

void ClientLoginMessage::Deserialize(DeserializerBase& deserializer)
{
    NetworkMessage::Deserialize(deserializer);
    deserializer.Get(m_loginName).Get(m_password);
}

std::uint64_t ClientLoginMessage::GetSizeInternal() const
{
    return m_loginName.size() + m_password.size();
}

}

