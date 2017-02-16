#pragma once

#include "IEntitiesVisitor.h"
#include "ClientRegistrationMessage.h"
#include "ClientManagmentMessage.h"

#include <memory>

namespace ODBC 
{
    class NanoODBCHelper;
}


namespace ServerManagment {
class ClientsManager: public Entities::IEntitiesVisitor
{
public:
    using TDatabaseHelper = std::unique_ptr<ODBC::NanoODBCHelper>;

public:
    ClientsManager();
    ~ClientsManager();

public:
    void OnUserRegistration(std::shared_ptr<Network::ClientRegistrationMessage>& clientRegistration);
    void OnUserLogin(std::shared_ptr<Network::ClientManagmentMessage>& clientLogingMessage);
    void OnUserLogout(std::shared_ptr<Network::ClientManagmentMessage>& clientManagmentMessage);
    void OnUserRemove(std::shared_ptr<Network::ClientManagmentMessage>& clientManagmentMessage);

public:
    void VisitUser(std::shared_ptr<Entities::Client>& user) override;
    void VisitGroup(std::shared_ptr<Entities::UsersGroup>& group) override;

private:
    TDatabaseHelper m_databaseHelper;
};
}