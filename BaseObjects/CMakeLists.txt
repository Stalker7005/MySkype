project(BaseObjects)
cmake_minimum_required(VERSION 2.6)

set(BaseObjectsHeaders
    Logger.h
    FileUtils.h
    ProcessUtils.h
	INetworkMessagesListener.h
	NetworkMessagesProvider.h
    CommonDefs.h
	)
set(BaseObjectsSources
    Logger.cpp
    FileUtils.cpp
    ProcessUtils.cpp
	NetworkMessageProvider.cpp
	)

source_group("BaseObjects\\Headers" FILES ${BaseObjectsHeaders})
source_group("BaseObjects\\Sources" FILES ${BaseObjectsSources})

add_library(${PROJECT_NAME} STATIC ${BaseObjectsHeaders} ${BaseObjectsSources})

include_directories(
					${Boost_INCLUDE_DIRS}
					${LOG4CPLUS_INCLUDE}					
					../NetworkUtilsLib
                    ../SerealizationUtilsLib
				    )

target_link_libraries(${PROJECT_NAME} 
					  ${Boost_LIBRARIES} 
					  ${LOG4CPLUS_LIB_DIRS}
					  )			  