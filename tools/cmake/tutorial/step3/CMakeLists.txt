cmake_minimum_required(VERSION 3.10)

project(Tutorial)

message("Hello World")
option(USE_MYMATH "Use tutorial provided math implementation" ON)
if(USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
  
  # MathFunctions所在库已经定义了使用该库的头文件，通过INTERFACE来定义
  # 因为子库自己已经指明，若调用子库，就可以使用子库的头文件
  # list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

if(USE_MYMATH)
	message("option USE_MYMATH is ${USE_MYMATH}")
else()
	message("option USE_MYMATH not define")
endif()

configure_file(TutorialConfig.h.in TutorialConfig.h)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_executable(Tutorial tutorial.cxx)

target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

target_include_directories(Tutorial PUBLIC 
							${PROJECT_BINARY_DIR}
							# ${EXTRA_INCLUDES} 因为子库自己已经指明，若调用子库，就可以使用子库的头文件
							)