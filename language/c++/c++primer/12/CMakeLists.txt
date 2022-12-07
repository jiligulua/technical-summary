cmake_minimum_required(VERSION 3.0)

project(DSO)

aux_source_directory(. SOURCE)

add_executable(test ${SOURCE})

include_directories(./)

