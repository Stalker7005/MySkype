project(SerealizationUtilsLib)
cmake_minimum_required(VERSION 3.0)

set(Headers
	Blob.h	
    Serializer.h
	)

set(Sources
	Blob.cpp
    Serializer.cpp
	)
	
source_group("SerealizationUtilsLib\\Headers" FILES ${Headers})
source_group("SerealizationUtilsLib\\Sources" FILES ${Sources})

add_library(${PROJECT_NAME} STATIC ${Headers} ${Sources})