cmake_minimum_required(VERSION 3.0)
project(Tests C CXX)
set(TestsHeaders
	Program.cpp
	)
set(TestsSources
	DummyTest.cpp
    ODBCHelperTest.cpp
	)
	
add_executable(${PROJECT_NAME} ${TestsHeaders} ${TestsSources})

include_directories(
                    ${Boost_LIBRARIES}
                    ${LOG4CPLUS_INCLUDE}
                    ../ODBCHelperLib
                    ../BaseObjects
                    ..
					.)

target_link_libraries(
					  ${PROJECT_NAME} 
					  ODBCHelperLib
                      BaseObjects
					  )


