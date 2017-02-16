#include "ClientManagmentMessage.h"

namespace Network {

ClientManagmentMessage::ClientManagmentMessage()
: NetworkMessage(MessageType::LOGIN)
{

}

ClientManagmentMessage::~ClientManagmentMessage()
{

}

void ClientManagmentMessage::SetPassword(const std::wstring& password)
{
    m_password = password;
}

std::wstring ClientManagmentMessage::GetPassword() const
{
    return m_password;
}

void ClientManagmentMessage::SetClientName(const std::wstring& loginName)
{
    m_loginName = loginName;
}

std::wstring ClientManagmentMessage::GetClientName() const
{
    return m_loginName;
}

void ClientManagmentMessage::Serialize(SerializerBase& serializer) const
{
    NetworkMessage::Serialize(serializer);

    serializer.Add(m_loginName).Add(m_password);
}

void ClientManagmentMessage::Deserialize(DeserializerBase& deserializer)
{
    NetworkMessage::Deserialize(deserializer);

    deserializer.Get(m_loginName).Get(m_password);
}

std::uint64_t ClientManagmentMessage::GetSizeInternal() const
{
    return m_loginName.size() + m_password.size();
}

void ClientManagmentMessage::SetManagmentType(Type type)
{
    m_type = type;
}

Network::ClientManagmentMessage::Type ClientManagmentMessage::GetManagmentType() const
{
    return m_type;
}

}

