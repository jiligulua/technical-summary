cmake_minimum_required(VERSION 3.15)

#if (NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE Release)
#endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(Boost_DIR "/usr/lib/boost-1.81.0/lib/cmake/Boost-1.81.0")  #BoostConfig.cmake

project(solar_system LANGUAGES CXX)

add_subdirectory(asteroid)
add_subdirectory(mercury)
add_subdirectory(earth)

include(useful_funcs)
