#pragma once
#include "NetworkMessage.h"
#include <string>

namespace Network {
class ClientLoginMessage: public NetworkMessage
{
public:
    ClientLoginMessage();
    ~ClientLoginMessage();

public:
    void SetPassword(const std::wstring& password);
    std::wstring GetPassword() const;
    void SetLoginName(const std::wstring& loginName);
    std::wstring GetLoginName() const;

protected:
    void Serialize(SerializerBase& serializer) const override;
    void Deserialize(DeserializerBase& deserializer) override;
    std::uint64_t GetSizeInternal() const override;

private:
    std::wstring m_loginName;
    std::wstring m_password;
};
}

