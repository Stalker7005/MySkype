#include "ClientsManager.h"
#include "NanoODBCHelper.h"
#include "Logger.h"

namespace ServerManagment {

ClientsManager::ClientsManager()
: m_databaseHelper(std::make_unique<ODBC::NanoODBCHelper>())
{

}

ClientsManager::~ClientsManager()
{
}

void ClientsManager::VisitUser(std::shared_ptr<Entities::Client>& user)
{
    
}

void ClientsManager::VisitGroup(std::shared_ptr<Entities::UsersGroup>& group)
{
    LOG_ERR("Not implemented!");
}

void ClientsManager::OnUserRegistration(std::shared_ptr<Network::ClientRegistrationMessage>& clientRegistration)
{

}

void ClientsManager::OnUserLogin(std::shared_ptr<Network::ClientManagmentMessage>& clientLogingMessage)
{

}

void ClientsManager::OnUserLogout(std::shared_ptr<Network::ClientManagmentMessage>& clientManagmentMessage)
{

}

void ClientsManager::OnUserRemove(std::shared_ptr<Network::ClientManagmentMessage>& clientManagmentMessage)
{

}

}

