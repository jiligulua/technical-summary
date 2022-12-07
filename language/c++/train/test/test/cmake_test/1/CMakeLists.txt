cmake_minimum_required(VERSION 3.2)

project(HELLO VERSION 1.0.0.0 LANGUAGES C CXX)

#set(SOURCES hello.c main.c)
#add_executable(hello ${SOURCES})

option(TEST_DEBUG "option for debug" OFF)

if(TEST_DEBUG)
	message("add_definitions -DTEST_DEBUG")
	add_definitions(-DMY_TEST_DEBUG)
endif()

add_definitions(-DBUILD_SHARED)

add_subdirectory(src)

add_subdirectory(libhello)
