project(BaseObjects)
cmake_minimum_required(VERSION 3.0)
set(Headers
	Blob.h
	)
set(Sources
	Blob.cpp
	)
	
source_group("BaseObjects\\Headers" FILES ${Headers})
source_group("BaseObjects\\Sources" FILES ${Sources})

add_library(${PROJECT_NAME} STATIC ${Headers} ${Sources})