cmake_minimum_required(VERSION 3.2)
project(mars LANGUAGES CXX)

add_executable(test)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cc src/*.h)
target_sources(test PUBLIC ${sources})
