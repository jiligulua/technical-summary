cmake_minimum_required(VERSION 3.10)

#递归获取目录下所有的.cxx文件
#file(GLOB_RECURSE cpp_files ./*.cxx)

# 递归获取目录下所有的h文件
#file(GLOB_RECURSE h_files ./*.h)

project(MathFunctions)

add_library(MathFunctions mysqrt.cxx)

# 添加该脚本之后，主CMakeLists.txt就可以不包含该库的头文件啦
# 因为使用该库（MathFunctions）的用户，可以使用该库所在文件的
# 所以，使用INTERFACE接口
# 子库自己已经指明，若调用该子库，就可以使用该子库的头文件
# 这个方法好啊
target_include_directories(MathFunctions INTERFACE
						${CMAKE_CURRENT_SOURCE_DIR})
						
						
install(TARGETS MathFunctions DESTINATION lib)
install(FILES mysqrt.h DESTINATION include)