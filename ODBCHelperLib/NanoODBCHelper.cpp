#include "NanoODBCHelper.h"
#include "Logger.h"

namespace ODBC {

NanoODBCHelper::NanoODBCHelper()
{

}

NanoODBCHelper::NanoODBCHelper(const std::wstring& connectionString): 
m_connectionString(connectionString)
{
    Connect(m_connectionString);
}

NanoODBCHelper::~NanoODBCHelper()
{

}

std::wstring NanoODBCHelper::GetDriverName()
{
    auto result = std::wstring();
    if (IsConnected())
    {
        result = m_connection.driver_name();
    }

    return result;
}

void NanoODBCHelper::Connect(const std::wstring& connectionString, std::uint32_t timeout /*= 0*/)
{
    try
    {
        m_connection.connect(connectionString, timeout);
    }
    catch (const std::runtime_error& except)
    {
        LOG_ERR("Connection error! %s", except.what());
    }
}

void NanoODBCHelper::Disconnect()
{
    m_connection.disconnect();
}

bool NanoODBCHelper::IsConnected() const
{
    return m_connection.connected();
}

nanodbc::result NanoODBCHelper::Execute(const std::wstring& query)
{
    auto result = nanodbc::result();
    if (IsConnected())
    {
        try
        {
            result = nanodbc::execute(m_connection, query);
        }
        catch (const std::runtime_error& e)
        {
            LOG_ERR("Query execution exeption! %s", e.what());
        }
    }
    else
    {
        LOG_ERR("Not connected to database!");
    }

    return result;
}
}


