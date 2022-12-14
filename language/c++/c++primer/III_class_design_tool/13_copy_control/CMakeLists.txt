cmake_minimum_required(VERSION 3.2)

project(mars VERSION 1.0.0.0)

set(SOURCES main_dy.cc str_vec.cc)

add_executable(dynamic_mem ${SOURCES})

include_directories(./)
