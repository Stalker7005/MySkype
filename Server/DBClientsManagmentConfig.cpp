#include "DBClientsManagmentConfig.h"

namespace ServerManagment {



DBClientsManagmentConfig::DBClientsManagmentConfig(const std::wstring& connectionString, const std::wstring& databaseName, const std::wstring& tableName)
: m_connectionString(connectionString),
m_databaseName(databaseName),
m_tableName(tableName)
{

}

DBClientsManagmentConfig::DBClientsManagmentConfig(DBClientsManagmentConfig&& config) noexcept
: 
m_connectionString(std::move(config.m_connectionString)),
m_databaseName(std::move(config.m_databaseName)),
m_tableName(std::move(config.m_tableName))
{

}

void DBClientsManagmentConfig::SetConnectionString(const std::wstring& connectionString)
{
    m_connectionString = connectionString;
}

std::wstring DBClientsManagmentConfig::GetConnectionString() const
{
    return m_connectionString;
}

void DBClientsManagmentConfig::SetDatabaseName(const std::wstring& databaseName)
{
    m_databaseName = databaseName;
}

std::wstring DBClientsManagmentConfig::GetDatabaseName() const
{
    return m_databaseName;
}

void DBClientsManagmentConfig::SetTableName(const std::wstring& tableName)
{
    m_tableName = tableName;
}

std::wstring DBClientsManagmentConfig::GetTableName() const
{
    return m_tableName;
}

DBClientsManagmentConfig& DBClientsManagmentConfig::operator=(DBClientsManagmentConfig&& config) noexcept
{
    m_connectionString = std::move(config.m_connectionString);
    m_databaseName = std::move(config.m_databaseName);
    m_tableName = std::move(config.m_tableName);

    return *this;
}

DBClientsManagmentConfig::~DBClientsManagmentConfig()
{

}

}

