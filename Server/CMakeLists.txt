project(Server)
cmake_minimum_required(VERSION 2.6)

set(ServerHeaders
	Server.h
	Session.h
	TCPSession.h
	)
set(ServerSources
	Server.cpp
	Session.cpp
	TCPSession.cpp
	)
	
add_executable(${PROJECT_NAME} ${ServerHeaders} ${ServerSources})

source_group("Server\\Headers" FILES ${ServerHeaders})
source_group("Server\\Sources" FILES ${ServerSources})

include_directories(
					${Boost_INCLUDE_DIRS}
                    ${LOG4CPLUS_INCLUDE}
					../NetworkUtilsLib
                    ../SerealizationUtilsLib
                    ../ThreadsUtilsLib
                    ../BaseObjects
				    )

target_link_libraries(${PROJECT_NAME} 
					  ${Boost_LIBRARIES}
					  ${LOG4CPLUS_LIB_DIRS}					  
					  NetworkUtilsLib
                      SerealizationUtilsLib
                      ThreadsUtilsLib
                      BaseObjects
					  )
