cmake_minimum_required(VERSION 3.0)
project(ServerObjects)

set(EntitiesHeaders
    IBaseEntity.h
    IEntitiesVisitor.h
    User.h
    UsersGroup.h
    EntitiesDefs.h
    )   
set(EntitiesSources
    User.cpp
    UsersGroup.cpp
    )

set(ServerObjectsHeaders
    ${EntitiesHeaders}
	)

set(ServerObjectsSources	
    ${EntitiesSources}
	)	

source_group("Common\\Headers" FILES ${CommonHeaders})
source_group("Common\\Sources" FILES ${CommonSources})

source_group("Entities\\Headers" FILES ${EntitiesHeaders})
source_group("Entities\\Sources" FILES ${EntitiesSources})


include_directories(
					${Boost_INCLUDE_DIRS}
					${LOG4CPLUS_INCLUDE}
					../ODBCHelperLib
                    ../BaseObjects
				    )

add_library(${PROJECT_NAME} STATIC ${ServerObjectsHeaders} ${ServerObjectsSources})


