#pragma once
#include "NetworkMessage.h"
#include "CommonDefs.h"
#include <cereal/types/polymorphic.hpp>

namespace NetworkUtils {
class ClientRegistration : public NetworkMessage
{
public:
    ClientRegistration();
    ~ClientRegistration() = default;

public:
    template<typename Archive>
    void serialize(Archive& archive)
    {
        archive(m_firstName, m_secondName, m_age, m_password, m_loginName, m_groupsTags);
    }

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

private:
    std::wstring m_firstName;
    std::wstring m_secondName;
    std::uint32_t m_age;
    std::wstring m_password;
    std::wstring m_loginName;
    std::vector<std::wstring> m_groupsTags;
};
}


