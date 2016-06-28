project(Server)
cmake_minimum_required(VERSION 3.0)
set(ServerHeaders
	Server.h
	Session.h
	)
set(ServerSources
	Server.cpp
	Session.cpp
	)
	
source_group("Server\\Headers" FILES ${ServerHeaders})
source_group("Server\\Sources" FILES ${ServerSources})

add_executable(${PROJECT_NAME} ${ServerHeaders} ${ServerSources})