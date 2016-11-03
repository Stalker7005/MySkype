cmake_minimum_required(VERSION 3.0)
project(ODBCHelperLib)

add_definitions(-DNANODBC_USE_UNICODE)

set(ODBCHelperHeaders
	nanodbc.h
    NanoODBCHelper.h
    NanoODBCUnicodeUtils.h
	)
set(ODBCHelperSources
	nanodbc.cpp
    NanoODBCHelper.cpp
	)

include_directories(
                    ${LOG4CPLUS_INCLUDE}
                    ../BaseObjects
                    )

add_library(ODBCHelperLib ${ODBCHelperHeaders} ${ODBCHelperSources})