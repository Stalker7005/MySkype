project(NetworkUtilsLib)
cmake_minimum_required(VERSION 3.0)

set(MessagesHeaders
    NetworkMessage.h
    Ping.h
    Pong.h
	)
	
set(MessagesSources
    NetworkMessage.cpp
    Ping.cpp
    Pong.cpp
	)
	
set(NetworkDefsHeaders
	NetworkDefs.h
	)
set(NetrowkDefsSources
    NetworkDefs.cpp
	)

set(HeadersLst
    ${MessagesHeaders}
    ${NetworkDefsHeaders}
    )
set(SourcesLst 
    ${MessagesSources}
    ${NetrowkDefsSources}
    )



message(STATUS "${PROJECT_NAME} added: Headers:${HeadersLst}, Sources:${SourcesLst}")

include_directories(
					${Boost_INCLUDE_DIRS}
				    )

add_library(${PROJECT_NAME} STATIC ${HeadersLst} ${SourcesLst})

source_group("Messages\\Headers" FILES ${MessagesHeaders})
source_group("Messages\\Sources" FILES ${MessagesSources})

source_group("NetworkDefs\\Headers" FILES ${NetworkDefsHeaders})
source_group("NetworkDefs\\Sources" FILES ${NetrowkDefsSources})

