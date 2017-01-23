project(NetworkLib)
cmake_minimum_required(VERSION 3.0)

set(MessagesHeaders
    NetworkMessage.h
    Ping.h
    Pong.h
    ClientRegistration.h
    Header.h
	)
	
set(MessagesSources
    NetworkMessage.cpp
    Ping.cpp
    Pong.cpp
    ClientRegistration.cpp
    Header.cpp
	)
	
set(NetworkDefsHeaders
	NetworkDefs.h
	)
	
set(CommonHeaders
	Connection.h
    Session.h
	TCPSession.h
	ISessionListener.h
	SessionProvider.h
    )
	
set(CommonSources
	Connection.cpp
    Session.cpp
    TCPSession.cpp
    )
	
set(HeadersLst
    ${MessagesHeaders}
    ${NetworkDefsHeaders}
	${CommonHeaders}
    )
set(SourcesLst 
    ${MessagesSources}
    ${NetrowkDefsSources}
	${CommonSources}
    )

message(STATUS "${PROJECT_NAME} added: Headers:${HeadersLst}, Sources:${SourcesLst}")

include_directories(
					${Boost_INCLUDE_DIRS}
                    ${LOG4CPLUS_INCLUDE}
                    ../BaseObjects
                    ../SerializationLib
                    ../ThreadsUtilsLib
				    )

add_library(${PROJECT_NAME} STATIC ${HeadersLst} ${SourcesLst})

source_group("Messages\\Headers" FILES ${MessagesHeaders})
source_group("Messages\\Sources" FILES ${MessagesSources})

source_group("NetworkDefs\\Headers" FILES ${NetworkDefsHeaders})
source_group("NetworkDefs\\Sources" FILES ${NetrowkDefsSources})

source_group("Common\\Headers" FILES ${CommonHeaders})
source_group("Common\\Sources" FILES ${CommonSources})

