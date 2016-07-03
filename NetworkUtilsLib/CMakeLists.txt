project(NetworkUtilsLib)
cmake_minimum_required(VERSION 3.0)

set(MessagesHeaders
    NetworkMessage.h
	ChatMessage.h
	)
	
set(MessagesSources
    NetworkMessage.cpp
	ChatMessage.cpp
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


source_group("Messages\\Headers" FILES ${MessagesHeaders})
source_group("Messages\\Sources" FILES ${MessagesSources})
source_group("NetworkDefs\\Headers" FILES ${NetworkDefsHeaders})
source_group("NetworkDefs\\Sources" FILES ${NetrowkDefsSources})

message(STATUS "${PROJECT_NAME} added: Headers:${HeadersLst}, Sources:${SourcesLst}")

if(Boost_FOUND)
message(STATUS "Boost Include Dirs:${Boost_INCLUDE_DIRS}")
else()
message(FATAL_ERROR "Can't find boost!")
endif()

include_directories(
					${Boost_INCLUDE_DIRS}
				    )

add_library(${PROJECT_NAME} STATIC ${HeadersLst} ${SourcesLst})
