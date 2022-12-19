cmake_minimum_required(VERSION 3.2)

project(mars VERSION 1.0.0.0)

set(SOURCES main_dy.cc foo.cc str_vec.cc String.cc)



add_executable(dynamic_mem ${SOURCES})

include_directories(./)

message(${PROJECT_SOURCE_DIR})
message(${PROJECT_BINARY_DIR})

message(${mars_BINARY_DIR})
message(${mars_SOURCE_DIR})
