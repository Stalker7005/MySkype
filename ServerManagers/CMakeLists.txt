cmake_minimum_required(VERSION 3.0)
project(ServerManagers)

set(ManagersHeaders
	UsersManager.h
	)
set(ManagersSources
	UsersManager.cpp
	)
	
source_group("Managers\\Headers" FILES ${ManagersHeaders})
source_group("Managers\\Sources" FILES ${ManagersSources})

add_library(${PROJECT_NAME} 
			${ManagersHeaders}
			${ManagersSources}
			)
