#pragma once
#include "NetworkMessage.h"
#include "CommonDefs.h"

namespace Network {
class ClientRegistrationMessage : public NetworkMessage
{
public:
    ClientRegistrationMessage();
    ~ClientRegistrationMessage() = default;

public:
    void SetFirstName(const std::wstring& firstName);
    std::wstring GetFirstName() const;

    void SetSecondName(const std::wstring& secondName);
    std::wstring GetSecondName() const;

    void SetAge(std::uint32_t age);
    std::uint32_t GetAge() const;

    void SetPassword(const std::wstring& password);
    std::wstring GetPassword() const;

    void SetLoginName(const std::wstring& loginName);
    std::wstring GetLoginName() const;

    void SetGroupsTags(const std::vector<TGroupTag>& groupsTags);
    std::vector<TGroupTag> GetGroupsTags() const;

protected:
    void Serialize(SerializerBase& serializer) const override;
    void Deserialize(DeserializerBase& deserializer) override;

private:
    std::wstring m_firstName;
    std::wstring m_secondName;
    std::uint32_t m_age;
    std::wstring m_password;
    std::wstring m_loginName;
    std::vector<std::wstring> m_groupsTags;
};
}


