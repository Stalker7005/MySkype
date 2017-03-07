#pragma once
#include <string>
#include "NanoODBCHelper.h"
#include "DBClientsManagmentConfig.h"

namespace ServerManagment {
class DBClientsManagmentHelper
{
public:
    using TDatabaseQuery = std::wstring;
    using TDatabaseHelper = std::unique_ptr<ODBC::NanoODBCHelper>;
    using TDBClientsConfig = std::unique_ptr<DBClientsManagmentConfig>;

public:
    DBClientsManagmentHelper(const DBClientsManagmentHelper& helper) = delete;
    DBClientsManagmentHelper& operator=(const DBClientsManagmentHelper& helper) = delete;
    DBClientsManagmentHelper(DBClientsManagmentHelper&& helper) = delete;
    DBClientsManagmentHelper& operator=(DBClientsManagmentHelper&& helper) = delete;

public:
    DBClientsManagmentHelper& GetInstance();
    void Init(TDBClientsConfig config);

private:
    bool CreateDB();
    bool CreateTable();

private:
    DBClientsManagmentHelper();
    ~DBClientsManagmentHelper();

private:
    TDatabaseHelper m_databaseHelper;
    TDBClientsConfig m_config;
    TDatabaseQuery m_createQueryDBQuery;
    TDatabaseQuery m_createTableQuery;
};
}

