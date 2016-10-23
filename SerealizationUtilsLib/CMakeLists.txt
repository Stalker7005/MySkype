project(SerealizationUtilsLib)
cmake_minimum_required(VERSION 2.6)

set(Headers
	Blob.h	
    Serializer.h
	)

set(Sources
	Blob.cpp
    Serializer.cpp
	)
	
add_library(${PROJECT_NAME} STATIC ${Headers} ${Sources})

source_group("SerializerUtils\\Headers" FILES ${Headers})
source_group("SerializerUtils\\Sources" FILES ${Sources})