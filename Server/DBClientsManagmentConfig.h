#pragma once
#include <string>

//TODO add loading from xml or something like that
namespace ServerManagment {
class DBClientsManagmentConfig
{
public:
    DBClientsManagmentConfig(const std::wstring& connectionString,
                            const std::wstring& databaseName,
                            const std::wstring& tableName);
    ~DBClientsManagmentConfig();

public:
    DBClientsManagmentConfig(DBClientsManagmentConfig&& config)  noexcept;
    DBClientsManagmentConfig& operator=(DBClientsManagmentConfig&& config) noexcept;

public:
    void SetConnectionString(const std::wstring& connectionString);
    std::wstring GetConnectionString() const;
    void SetDatabaseName(const std::wstring& databaseName);
    std::wstring GetDatabaseName() const;
    void SetTableName(const std::wstring& tableName);
    std::wstring GetTableName() const;

public:
    DBClientsManagmentConfig(const DBClientsManagmentConfig& other) = delete;
    DBClientsManagmentConfig& operator=(const DBClientsManagmentConfig& other) = delete;

private:
    std::wstring m_connectionString;
    std::wstring m_databaseName;
    std::wstring m_tableName;
};
}

