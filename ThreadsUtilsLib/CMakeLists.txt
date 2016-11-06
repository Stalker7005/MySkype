project(ThreadsUtilsLib)
cmake_minimum_required(VERSION 3.0)

set(CommonHeaders
	RunningContext.h
	)
set(CommonSources
	RunningContext.cpp
	)
	
set(ThreadPoolHeaders
	ThreadPool.h
    ThreadsJoiner.h
    ThreadSafeQueue.h
	)
	
set(ThreadPoolSources	
	ThreadPool.cpp
	)
	
set(Headers
	${CommonHeaders}
	${ThreadPoolHeaders}
	)
set(Sources
	${CommonSources}
	${ThreadPoolSources}
	)
	

add_library(${PROJECT_NAME} STATIC ${Headers} ${Sources})

source_group("Common\\Headers" FILES ${CommonHeaders})
source_group("Common\\Sources" FILES ${CommonSources})

source_group("ThreadPool\\Headers" FILES ${ThreadPoolHeaders})
source_group("ThreadPool\\Sources" FILES ${ThreadPoolSources})