project(CommonDefs)
cmake_minimum_required(VERSION 3.0)
set(CommonDefsHeaders
	CommonDefs.h
	)
set(CommonDefsSources
	
	)

add_library(${PROJECT_NAME} STATIC ${CommonDefsHeaders} ${CommonDefsSources})

source_group("CommonDefs\\Headers" FILES CommonDefsHeaders)
source_group("CommonDefs\\Sources" FILES CommonDefsSources)

if(Boost_FOUND)
message(STATUS "Boost Include Dirs:${Boost_INCLUDE_DIRS}")
else()
message(FATAL_ERROR "Can't find boost!")
endif()

include_directories(${Boost_INCLUDE_DIRS})
