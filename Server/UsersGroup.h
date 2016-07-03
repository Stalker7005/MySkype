#pragma once
#include <unordered_map>
#include <memory>
#include <boost/functional/hash.hpp>
#include "NetworkMessage.h"
#include "NetworkDefs.h"
#include "ChatMessage.h"
#include "IUser.h"

class UsersGroup
{
public:
    void Join(NetworkDefs::TUiid uuid, std::shared_ptr<IUser> user);
    void Leave(NetworkDefs::TUiid uuid);
    void Deliver(NetworkDefs::TUiid uuid, std::shared_ptr<NetworkUtils::NetworkMessage>& message);

private:
    std::shared_ptr<IUser> FindUser(NetworkDefs::TUiid uuid);

private:
    std::unordered_map<NetworkDefs::TUiid, std::shared_ptr<IUser>, boost::hash<NetworkDefs::TUiid>> m_users;
};


