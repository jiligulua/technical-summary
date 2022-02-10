cmake_minimum_required(VERSION 3.10)

#递归获取目录下所有的.cxx文件
#file(GLOB_RECURSE cpp_files ./*.cxx)

# 递归获取目录下所有的h文件
#file(GLOB_RECURSE h_files ./*.h)

project(MathFunctions)

add_library(MathFunctions mysqrt.cxx)