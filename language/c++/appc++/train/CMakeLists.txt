cmake_minimum_required(VERSION 3.2)

project(review)

#aux_source_directory(. DIR_SRC)

message(${PROJECT_BINARY_DIR})		
message(${PROJECT_SOURCE_DIR})		

set(DIR_SRC main.cc testa.cc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIRY}/bin)

		
add_executable(test ${DIR_SRC})

include_directories(${PROJECT_SOURCE_DIR})


