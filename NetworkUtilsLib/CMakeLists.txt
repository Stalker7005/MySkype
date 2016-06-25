project(NetworkUtilsLib)
cmake_minimum_required(VERSION 3.0)

set(MessagesHeaders
	ChatMessage.h
	)
	
set(MessagesSouces
	ChatMessage.cpp
	)
	
source_group("Messages\\Headers" FILES ${MessagesHeaders})
source_group("Messages\\Sources" FILES ${MessagesSouces})
message(STATUS "${PROJECT_NAME} added:${MessagesHeaders} ${MessagesSouces}")

add_library(${PROJECT_NAME} STATIC ${MessagesHeaders} ${MessagesSouces})