project(SerealizationUtilsLib)
cmake_minimum_required(VERSION 3.0)

set(Headers
	Blob.h
	Serealizer.h
    BinarySerializer.h
    JSONSerializer.h
    XMLSerializer.h
	)
set(Sources
	Blob.cpp
	Serealizer.cpp
	)
	
source_group("SerealizationUtilsLib\\Headers" FILES ${Headers})
source_group("SerealizationUtilsLib\\Sources" FILES ${Sources})

add_library(${PROJECT_NAME} STATIC ${Headers} ${Sources})