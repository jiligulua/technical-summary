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
							
install(TARGETS Tutorial 
	DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
	DESTINATION include)


# 开始进行单元测试
enable_testing()

# does the application run
add_test(NAME Runs COMMAND Tutorial 25)

# does the usage message work? 测试用例的名字为Usage
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# define a function to simplify adding tests
# 第一参数是函数，后面是函数的参数
function(do_test target arg result)

  # 添加测试用例，分别指明测试用例的名字，使用的可执行文件和参数
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  
  # 主要使用该方法，来确定测试结果，其中的PASS_REGULAR_EXPRESSION来验证cout输出时，是否有${result}字符串
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

# do a bunch of result based tests
do_test(Tutorial 4 "4 is 16")
do_test(Tutorial 9 "9 is 81")
do_test(Tutorial 5 "5 is 25")
do_test(Tutorial 7 "7 is 49")
do_test(Tutorial 25 "25 is 625")
do_test(Tutorial -25 "-25 is 625")
do_test(Tutorial 0.0001 "0.0001 is 0.01")