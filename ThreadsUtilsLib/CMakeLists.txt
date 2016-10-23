project(ThreadsUtilsLib)
cmake_minimum_required(VERSION 3.0)

set(CommonHeaders
	RunningContext.h
	)
set(CommonSources
	RunningContext.cpp
	)
	

add_library(${PROJECT_NAME} STATIC ${CommonHeaders} ${CommonSources})

source_group("Common\\Headers" FILES ${BaseObjectsHeaders})
source_group("Common\\Sources" FILES ${BaseObjectsSources})