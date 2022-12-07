cmake_minimum_required(VERSION 3.0)

project(Template)


aux_source_directory(. SOURCES)

add_executable(test ${SOURCES})

include_directories(./)
