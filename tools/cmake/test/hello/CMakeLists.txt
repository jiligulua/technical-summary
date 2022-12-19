cmake_minimum_required(VERSION 3.2)
project(HELLO VERSION 1.0 LANGUAGES C CXX)
option(TEST_DEBUG "option for debug" OFF)
if (TEST_DEBUG)
  add_definitions(-DTEST_DEBUG)
endif()
add_definitions(-DBUILD_SHARED)
		
add_subdirectory(src)		
add_subdirectory(libhello)
	
