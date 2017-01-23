cmake_minimum_required(VERSION 3.0)
project(Tests C CXX)
set(TestsHeaders
	Program.cpp
	)
set(TestsSources
	DummyTest.cpp
    ODBCHelperTest.cpp
    SerializationTest.cpp
	)
	
add_executable(${PROJECT_NAME} ${TestsHeaders} ${TestsSources})

include_directories(
                    ${Boost_INCLUDE_DIRS}
                    ${LOG4CPLUS_INCLUDE}
                    ../ODBCHelperLib
                    ../BaseObjects
                    ../SerializationLib
                    ../NetworkLib
                    ..
					.)

target_link_libraries(
					  ${PROJECT_NAME} 
                      ${Boost_LIBRARIES}
					  ODBCHelperLib
                      SerializationLib
                      BaseObjects
                      NetworkLib
					  )


