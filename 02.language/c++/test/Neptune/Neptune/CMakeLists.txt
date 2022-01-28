# CMakeList.txt: Neptune 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (Neptune "Neptune.cpp" "Neptune.h" "non_mutate.h" "test_non_mutate.cpp" 
"test_non_mutate.h" "test_array.h" "test_array.cpp"  "leetcode/test_algo_base.cpp" "leetcode/test_algo_base.h"
"test_shared_ptr.cpp" "test_shared_ptr.h" "dynamic_program.cpp" "dynamic_program.h" "sequential_contain.cpp" 
"sequential_contain.h")
