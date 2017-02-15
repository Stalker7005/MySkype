#pragma once

#include "IEntitiesVisitor.h"
#include <memory>

namespace ODBC 
{
    class NanoODBCHelper;
}


namespace ServerManagment {
class UsersManager: public Entities::IEntitiesVisitor
{
public:
    using TDatabaseHelper = std::unique_ptr<ODBC::NanoODBCHelper>;

public:
    UsersManager();
    ~UsersManager();

public:
    void OnUserRegistration(std::shared_ptr<Network::ClientRegistrationMessage>& clientRegistration);
    void OnUserLogin();
    void OnUserLogout();
    void OnUserRemove();

public:
    void VisitUser(std::shared_ptr<Entities::User>& user) override;
    void VisitGroup(std::shared_ptr<Entities::UsersGroup>& group) override;

private:
    TDatabaseHelper m_databaseHelper;
};
}