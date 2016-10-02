#include "UsersGroup.h"



void UsersGroup::Join(NetworkDefs::TUiid uuid, std::shared_ptr<IUser> user)
{
    auto existingUser = FindUser(uuid);
    if (!existingUser)
    {
        m_users.emplace(std::make_pair(uuid, user));
    }
}

void UsersGroup::Leave(NetworkDefs::TUiid uuid)
{
    m_users.erase(uuid);
}

void UsersGroup::Deliver(NetworkDefs::TUiid uuid, std::shared_ptr<NetworkUtils::NetworkMessage>& message)
{
    auto user = FindUser(uuid);
    if (user)
    {
        user->Deliver(message);
    }
}

std::shared_ptr<IUser> UsersGroup::FindUser(NetworkDefs::TUiid uuid)
{
    auto iter = m_users.begin();
    if ((iter = m_users.find(uuid)) != m_users.end())
    {
        auto& user = iter->second;
        return user;
    }

    return nullptr;
}
