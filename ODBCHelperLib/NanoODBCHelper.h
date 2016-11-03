#pragma once

#include <string>
#include <cstdint>
#include "nanodbc.h"

#pragma comment(lib,"odbc32.lib")

namespace ODBC {
class NanoODBCHelper
{
public:
    NanoODBCHelper();
    NanoODBCHelper(const std::wstring& connectionString);
    ~NanoODBCHelper();

public: 
    std::wstring GetDriverName();

public:
    void Connect(const std::wstring& connectionString, std::uint32_t timeout = 0);
    void Disconnect();
    bool IsConnected() const;

    nanodbc::result Execute(const std::wstring& query);
    

private:
    std::wstring m_connectionString;
    nanodbc::connection m_connection;

};
}


