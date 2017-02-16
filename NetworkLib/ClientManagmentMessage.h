#pragma once
#include "NetworkMessage.h"
#include <string>

namespace Network {
class ClientManagmentMessage: public NetworkMessage
{
public:
    enum class Type: std::uint8_t
    {
        Login,
        Logout,
        Remove
    };

public:
    ClientManagmentMessage();
    ~ClientManagmentMessage();

public:
    void SetPassword(const std::wstring& password);
    std::wstring GetPassword() const;
    void SetClientName(const std::wstring& loginName);
    std::wstring GetClientName() const;

    void SetManagmentType(Type type);
    Type GetManagmentType() const;

protected:
    void Serialize(SerializerBase& serializer) const override;
    void Deserialize(DeserializerBase& deserializer) override;
    std::uint64_t GetSizeInternal() const override;

private:
    std::wstring m_loginName;
    std::wstring m_password;
    Type m_type;
};
}

