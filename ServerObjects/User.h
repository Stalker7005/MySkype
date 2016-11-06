#pragma  once
#include <cstdint>
#include <string>
#include <vector>

#include "IBaseEntity.h"

namespace Entities {
class User: public IBaseEntity,
            public std::enable_shared_from_this<User>
{
public:
    User();
    ~User() = default;
    
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

    void SetContactsList(const std::vector<std::wstring>& contacts);
    std::vector<std::wstring> GetContactsList() const;

    void Fill(std::shared_ptr<IEntitiesVisitor>& visitor) override;
    void Clear() override;

private:
    std::wstring m_firstName;
    std::wstring m_secondName;
    std::uint32_t m_age;
    std::wstring m_password;
    std::wstring m_loginName;
    std::vector<std::wstring> m_contactsList;
};
}



