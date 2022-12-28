cmake_minimum_required(VERSION 3.15) 
project(mars)

add_subdirectory(mylib)
set_property(TARGET mylib PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#set_property(TARGET mylib PROPERTY ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}) 
add_executable(main src/main.cc)
set_property(TARGET main PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#set_property(TARGET main PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_DIR})

message("binary directory is : ${PROJECT_BINARY_DIR}")

target_link_libraries(main PUBLIC mylib)

include_directories(mylib)
