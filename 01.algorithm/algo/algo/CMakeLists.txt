# CMakeList.txt: algo 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE  cxx_file ./*.cxx)
file(GLOB_RECURSE  cxx_header ./*.h)

message("cxx file is ${cxx_file}")
message("cxx header is ${cxx_header}")

# 将源代码添加到此项目的可执行文件。
add_executable (algo ${cxx_file} ${cxx_header} "avl.cxx")



# TODO: 如有需要，请添加测试并安装目标。
