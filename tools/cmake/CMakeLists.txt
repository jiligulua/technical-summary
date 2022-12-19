cmake_minimum_required(VERSION 3.2)
project(hello VERSION 1.0.0.0)
aux_source_direcotry(路径 变量)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.CC)
file(GLOB_RECURSE NATIVE_SRC ${PROJECT_SOURCE_DIR}/lib/*.cpp)
set(变量名 文件名/路径/...) # 取变量内容，dollar钱阿: ${变量名}
add_definitions(-DFOO -DBAR...) # 用在#ifdef #else #endif中
add_compile_definitions(MG_ENABLE_OPENSSSL=1)
message(消息)
add_subdirectory(子文件夹名称)
add_subdirectory(子文件名称 [binary_dir] [EXCLUDE_FROM_ALL])
binary_dir:可选参数，指定存放文件的输出目录，可以是相对目录也可以是绝对目录，相对目录是指相对于当前输出目录的一个相对路径，若是没有的话，就使用默认输出目录，名称为“子文件夹名称”
EXCLUDE_FROM_ALL:可选参数，若指定，则该子目录下的目标不会被父目录下的目标文件包含进去，即父目录的CMakeLists.txt不会构建子目录的目标文件，必须在子目录下显示去构建。例外情况：当父目录的目标依赖于子目录的目标，仍会被构建出来，例如使用了target_link_libraries()
add_subdirectory(src ./bin)
add_subdirectory(libhello ./bin) # 生成的可执行文件和lib都在在build/bin中

add_library(库文件名称xxx STATIC 文件) # 库文件生成的名称通常是libxxx.so或libxxx.a，在这里只需要写xxx即可
add_library(库文件名称xxx SHARED ${LIB_SRC})
add_executable(可执行文件名称 文件) # 将.cpp/.c/.cc文件生成可执行文件

预定义的变量，可以重复修改，以指定新的输出路径
EXECUTABLE_OUTPUT_PATH 通过set来更新这个变量的新路径,用于库文件的输出目录和可执行文件的输出目录
LIBRARY_OUTPUT_PATH # 注意这两个输出的路径为PATH结果，而PROJECT开头的两个变量以DIR结尾
PROJECT_BINARY_DIR # 表示可执行文件的默认输出目录，通过make来执行的所在目录，而通过cmake ../ 表示的是参数表示CMakeLists.txt所在目录，通过CMake将在当前目录下执行make，编译生成的中间文件和最终的可执行文件。
PROJECT_SOURCE_DIR # 表示顶层CMakeLists.txt所在的目录

include_directories(路径)
include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2]) # 将指定目录添加到编译器的头文件搜索路径下，指定的目录被解释称当前源代码路径的相对路径
link_directories(路径) // 规定.so/.a库文件路径

option(TEST_DEBUG "option for debug" OFF) # 设置编译选项及默认值，用在CMakeLists.txt中。该可选项用于CMake脚本以及执行CMake时所添加的命令，如-DTEST_DEBUG=ON,关闭或打开-D是参数类型 if(TEST_DEBUG) 
add_definitions(-DTEST_DEBUG) # add_definitions的功能和C/C++中的#define是一样的，但不能有参数。通过CMake的编译选项，在CMakeLists.txt中来定义来c或cc中的源代码中的预编译开关，以便源代码中可以使用#ifdef来达到源代码的不同选择。
else()
add_definitions(_DBUILD_SHARED)
endif()

if(BUILD_SHARED)
  add_library(hello SHARED ${LIB_SRC})
else()
  add_library(hello STATIC ${LIB_SRC})
endif()

target_link_libraries(库文件名称/可执行文件名称 链接的库文件名称)
target_link_libraries(<target> [item0][item1][itme2] [[debug|optimized|general] <item>] ...)
target_link_libraries(hello A B.a C.so) # libA.so可能依赖于libB.a and libC.so，如果顺序有错，链接时会报错。还有一点，B.a会告诉CMake优先使用静态链接库libB.a, C.so则告诉CMake优先使用libC.so，也可直接使用库文件的相对路径或绝对路径。使用绝对路径好处，在于当依赖库被更新时，make的时候会重新链接

set_target_properties(libhello PROPERTIES OUTPUT_NAME "hello") # 允许设置多个目标的多个属性
set_target_properties(Thirdlib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/jniLibs/libThirdlib.so) # cmakelist 添加依赖库
set_target_properties(tet PROPERTIES LINKER_LANGUAGE CXX) // 指定编译器链接语言为C++
set_target_properties(tet PROPERTIES LINKER_LANGUAGE C) // 指定编译器链接语言为C

采用cmake out-of-source方式来构建（生成中间产物与源代码分离），并坚持使用这种方法，单独建立build目录，在该build中进行：mkdir build & cd build & cmake .. & make 就可以生成hello可执行文件
由默认的变量：PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, hello_SOURCE_DIR, hello_BINARY_DIR

cmake .. -DBUILD_SHARED=1 # 生成动态库
cmake .. -DTEST_DEBUG=ON # main.c中的“DEBUG”会打印
