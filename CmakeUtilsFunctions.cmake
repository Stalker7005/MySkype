cmake_minimum_required(VERSION 3.0)
project(CmakeUtilsFunctions)

include(CmakeConstants.cmake)

function(debug msg)

message(STATUS ${msg})

endfunction()

function(Assert arg)
if(${arg})
message(STATUS "Find:${arg}")
else()
message(FATAL_ERROR "Can't find:${arg}")
endif()
endfunction()

function(getArchitecture Artitecture)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
set(${Artitecture} x64 PARENT_SCOPE)
else()
set(${Artitecture} x86 PARENT_SCOPE)
endif()
endfunction(getArchitecture)

function(addLibInclude LIB_NAME)
set(UPPER_LIB_NAME)
STRING(TOUPPER  ${LIB_NAME} UPPER_LIB_NAME)
debug(${UPPER_LIB_NAME})

set(${UPPER_LIB_NAME}_INCLUDE ${BUILD_FILES_DIR}/${LIB_NAME}/include PARENT_SCOPE)
endfunction()

function(addLibLink LIB_NAME IS_DEBUG SOURCE_NAME)

set(ARC)
getArchitecture(ARC)
debug("Arhitecture:${ARC}")

if(${IS_DEBUG} EQUAL 1)
set(FOLDER ${DEBUG_FOLDER})
set(BUILD_TYPE debug)
elseif(${IS_DEBUG} EQUAL 0)
set(FOLDER ${RELEASE_FOLDER})
set(BUILD_TYPE optimized)
else()
Assert(0)
endif()

set(UPPER_LIB_NAME)
STRING(TOUPPER  ${LIB_NAME} UPPER_LIB_NAME)
debug(${UPPER_LIB_NAME})

set(${UPPER_LIB_NAME}_LIB_DIRS ${${UPPER_LIB_NAME}_LIB_DIRS} ${BUILD_TYPE} ${BUILD_FILES_DIR}/${LIB_NAME}/${FOLDER}/${ARC}/${SOURCE_NAME} PARENT_SCOPE)
#message(FATAL_ERROR "LIB DIRS:${BUILD_FILES_DIR}/${LIB_NAME}/${FOLDER}/${ARC}/${SOURCE_NAME}")

endfunction()



