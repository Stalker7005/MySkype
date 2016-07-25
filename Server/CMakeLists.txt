project(Server)
cmake_minimum_required(VERSION 3.0)
set(ServerHeaders
	Server.h
	Session.h
    IUser.h
    UsersGroup.h
	)
set(ServerSources
	Server.cpp
	Session.cpp
    UsersGroup.cpp
	)
	
source_group("Server\\Headers" FILES ${ServerHeaders})
source_group("Server\\Sources" FILES ${ServerSources})

add_executable(${PROJECT_NAME} ${ServerHeaders} ${ServerSources})

if(Boost_FOUND)
message(STATUS "Boost Include Dirs:${Boost_INCLUDE_DIRS}")
else()
message(FATAL_ERROR "Can't find boost!")
endif()

include_directories(
					${Boost_INCLUDE_DIRS}
					../NetworkUtilsLib
                    ../BaseObjects
				    )

message(STATUS "Boost Libraries:${Boost_LIBRARIES}")
target_link_libraries(${PROJECT_NAME} 
					  ${Boost_LIBRARIES} 
					  NetworkUtilsLib
                      BaseObjects
					  )