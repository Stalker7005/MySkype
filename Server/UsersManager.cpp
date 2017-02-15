#include "UsersManager.h"
#include "Logger.h"

namespace ServerManagment {

UsersManager::UsersManager()
: m_databaseHelper(std::make_unique<ODBC::NanoODBCHelper>())
{

}

UsersManager::~UsersManager()
{
}

void UsersManager::VisitUser(std::shared_ptr<Entities::User>& user)
{
    
}

void UsersManager::VisitGroup(std::shared_ptr<Entities::UsersGroup>& group)
{
    LOG_ERR("Not implemented!");
}

}

