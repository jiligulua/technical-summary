# CMakeList.txt: Neptune 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


include_directories(${CMAKE_SOURCE_DIR})
include_directories("${CMAKE_SOURCE_DIR}/leetcode")

set(SRC_CODE "Neptune.cpp" "test_non_mutate.cpp" 
 "test_array.cpp"  "leetcode/test_algo_base.cpp" 
"test_shared_ptr.cpp"  "dynamic_program.cpp" "sequential_contain.cpp" )


add_executable (Neptune ${SRC_CODE})
