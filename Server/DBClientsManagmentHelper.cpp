#include "DBClientsManagmentHelper.h"
#include "Logger.h"

namespace ServerManagment {

bool DBClientsManagmentHelper::CreateDB()
{
    if (m_config)
    {
        m_databaseHelper->Execute();
    }
}

bool DBClientsManagmentHelper::CreateTable()
{

}

DBClientsManagmentHelper::DBClientsManagmentHelper()
: m_config(nullptr),
  m_databaseHelper(nullptr)
{

}

ServerManagment::DBClientsManagmentHelper& DBClientsManagmentHelper::GetInstance()
{
    static DBClientsManagmentHelper helper;

    return helper;
}

void DBClientsManagmentHelper::Init(TDBClientsConfig config)
{
    m_config = std::move(config);
    if (m_config)
    {
        m_databaseHelper = std::make_unique<ODBC::NanoODBCHelper>();
        m_databaseHelper->Connect(m_config->GetConnectionString());
        if (m_databaseHelper->IsConnected())
        {
            LOG_INFO("Connection with db established");
        }
        else
        {
            LOG_INFO("Can't connection to db. Connection string %s", );
        }
    }
    
}

DBClientsManagmentHelper::~DBClientsManagmentHelper()
{

}
}

