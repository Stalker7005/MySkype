#include "catch.hpp"
#include <iostream>
#include <string>
#include "NanoODBCHelper.h"
#include "Logger.h"

TEST_CASE("ODBCHelperTest")
{
    LOG_INIT();
    std::wstring connString = L"Driver={SQL Server};Server=IVAN-ой\\SQLEXPRESS;Database=Autolot";
    REQUIRE(!connString.empty());
    ODBC::NanoODBCHelper helper;
    

    SECTION("Database operations")
    {
        helper.Connect(connString);
        REQUIRE(helper.IsConnected());

        auto result = helper.Execute(L"drop table SimpleTest");
        REQUIRE(result);

        result = helper.Execute(L"create table SimpleTest(Name varchar(50), Age int)");
        REQUIRE(result);

        result = helper.Execute(L"insert into SimpleTest values('Ivan', 21)");
        REQUIRE(result);
        result = helper.Execute(L"insert into SimpleTest values('Jun', 26)");
        REQUIRE(result);
        result = helper.Execute(L"insert into SimpleTest values('Fred', 50)");
        REQUIRE(result);

        result = helper.Execute(L"Select * From SimpleTest");
        REQUIRE(result.columns() == 2);

        while (result.next())
        {
            std::wcout << result.get<std::wstring>(L"Name") << result.get<std::wstring>(L"Age") << std::endl;
        }

    }
}



