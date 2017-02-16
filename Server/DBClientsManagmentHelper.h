#pragma once
#include "NanoODBCHelper.h"

namespace ServerManagment {
class DBClientsManagmentHelper
{
public:
    using TDatabaseHelper = std::unique_ptr<ODBC::NanoODBCHelper>;

public:
    DBClientsManagmentHelper(const DBClientsManagmentHelper& helper) = delete;
    DBClientsManagmentHelper& operator=(const DBClientsManagmentHelper& helper) = delete;
    DBClientsManagmentHelper(DBClientsManagmentHelper&& helper) = delete;
    DBClientsManagmentHelper& operator=(DBClientsManagmentHelper&& helper) = delete;

public:
    DBClientsManagmentHelper& GetInstance();

private:
    DBClientsManagmentHelper();
    ~DBClientsManagmentHelper();

private:
    TDatabaseHelper m_databaseHelper;
};
}

