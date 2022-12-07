cmake_minimum_required(VERSION 3.2)

project(RemoveRepeat)
aux_source_directory(. SOURCES)

#set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g2 -ggdb}")
#set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb}")
#set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_executable(removerepeat ${SOURCES})

include_directories(./)
