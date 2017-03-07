project(XMLLib)
cmake_minimum_required(VERSION 2.6)

set(XMLLibHeaders
	tinyxml2.h
	)
set(XMLLibSources
	tinyxml2.cpp
	)
	
add_library(${PROJECT_NAME} ${XMLLibHeaders} ${XMLLibSources})

source_group("XML\\Headers" FILES ${XMLLibHeaders})
source_group("XML\\Sources" FILES ${XMLLibSources})
