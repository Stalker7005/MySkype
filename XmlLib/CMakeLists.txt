project(XMLLib)
cmake_minimum_required(VERSION 2.6)

set(XMLLibHeaders
	tinyxml2.h
    XMLDocument.h
    XMLElement.h
    XMLFindStrategy.h
    XMLBSFFindStrategy.h
	)

set(XMLLibSources
	tinyxml2.cpp
    XMLDocument.cpp
    XMLElement.cpp
    XMLBSFFindStrategy.cpp
	)
	
include_directories(../BaseObjects
					${LOG4CPLUS_INCLUDE}
				    )

add_library(${PROJECT_NAME} ${XMLLibHeaders} ${XMLLibSources})

source_group("XML\\Headers" FILES ${XMLLibHeaders})
source_group("XML\\Sources" FILES ${XMLLibSources})
