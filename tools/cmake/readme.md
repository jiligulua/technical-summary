现代CMake是指CMake 3.x

# 命令行调用简化

## 古代CMake

1. mkdir -p build
2. cd build
3. cmake .. -DCMAKE_BUILD_TYPE=Release 
4. make -j4
5. make install
6. cd ..

## 现代CMake
1. cmake -B build -DCMAKE_BUILD_TYPE=Release  #  创建build目录，并执行release, -D只能在配置阶段才指定配置变量（又称缓存变量）。称为配置阶段，生成本地构建系统能识别的项目文件（Makefile或.sln）
2. cmake --build build --parallel 4  # --build表示在build下调用make,--parallel 4 表示用4个进程来构建。称为构建阶段（build），这时才实际调用编译器来编译代码

在配置阶段通过-D设置缓存变量，第二次配置时，之前的-D添加仍然保留，除非这个build目录删除掉

	-DCMAKE_INSTALL_PREFIX=opt/openvdb-8.0 表示安装目录
	-DCMAKE_BUILD_TYPE=Release 表示项目文件使用release来构建，开启全部优化，即gcc开启-O3还是-O0，通过这里的Release或Debug来完成

3. sudo cmake --build build --target install  # 调用本地的构建系统执行install这个目标，即安装


# 写法改进

## 古代版写法

	cmake_minimum_required(VERSION 2.8)
	project(MyProject)
	
	list(APPEND CMAKE_MODULE_PATH "<path to find TBB module>")

	find_package(TBB COMPONENTS tbb tbbmalloc)
	if (NOT TBB_FOUND)
		message(FATAL_ERROR "TBB not found")
	endif()

	add_executable(myapp myapp)
	target_include_directories(myapp ${TBB_INCLUDE_DIRS})
	target_compile_definitions(myapp ${TBB_DEFINITIONS})
	target_link_libraries(myapp ${TBB_LIBRARIES})


## 现代版写法


	cmake_minimum_required(VERSION 3.12)
	project(MyProject LANGUAGES CXX)
	
	find_package(TBB COMPONENTS tbb tbbmalloc REQUIRED)

	add_executable(myapp myapp)
	target_link_libraries(myapp TBB::tbb TBB::tbbmalloc)


# 配置阶段选项

## -D
设置配置阶段的缓存变量

## -G
指定要用的生成器

默认是Unix makefiles，一般比较常用的是Ninja，它比makefile更快

ninja可以从包管理器里安装，如pip install ninja

可以用-G参数改用别的生成器，例如cmake -GNinja会生成Ninja这个构建系统的构建规则。Ninja是一个高性能，跨平台的构建系统，Linux、Windows、MacOS上都可以用。

事实上，MSBuild是单核心的构建系统，没法利用多核构建，所以很慢
Makefile虽然是多核心但历史兼容原因效率一般，还要读取配置，也很慢
而Ninja则是专为性能优化的构建系统，他和CMake结合都是行业标准了。
性能上：Ninja > Makefile > MSBuild

	$cmake -GNinja -B build
	$time cmake --build build # 

# 源代码

	add_executable(main main.cpp)

	或者
	add_executable(main)
	target_sources(main PUBLIC main.cc other.cc)  # 会产生源文件列表

	或者,使用变量来存储，最好把头文件也加上
	add_executable(main)
	set(sources main.cc other.cc other.h) 
	target_sources(main PUBLIC ${sources})

	或者，用file, 使用GLOB值令自动查找当前目录下的指定扩展名的文件，实现批量添加源文件。
	若是又添加文件了，但是此时GLOB并没有真正的添加，还有原来的所指定的文件，但是添加上
	CONFIGURE_DEPENDS之后，添加新的文件就会自动更新，就会重新刷新sources内部的值。就是第二边build时会刷新sources的值
	add_executable(main)
	file(GLOB sources *.cc *.h)
	file(GLOB sources CONFIGURE_DEPENDS *.cc *.h)
	target_sources(main PUBLIC ${sources})
	

	在cmake看来，编译和链接是在一起的。

	若果源码放在子文件夹里怎么办？出于管理源码的需要，如
	mylib/
		other.cc
		other.h
	CMakeLists.txt
	main.cc


	如下写：
	file(GLOB sources CONFIGURE_DEPENDS *.cc *.h mylib/*.cc mylib/*.h)
	大可不必！用aux_source_directory,自动搜索需要的文件名后缀名，如下：

	add_executable(main)
	aux_source_directory(. sources) # 把当前目录下的文件都包括进到sources
	aux_source_directory(mylib sources) # 把mylib目录下的文件都包括进sources
	target_sources(main PUBLIC ${sources})

	进一步，还可以把GLOB换乘GLOB_RECURSE，能自动包含所有子文件夹下的文件
	add_executable(main)
	file(GLOB_RECUrSE sources CONFIGURE_DEPENDS *.cpp *.h) # 这样mylib下的文件也能够找到啦，它是递归地去搜索
	target_sources(main PUBLIC ${sources})

	GLOB_RECURSE的问题：会把build目录下的临时cpp文件也会加进来
	因为cmake为了测试编译器，会生成一些临时的cpp文件，而build显然也在同一个目录下。那么里面的main函数就和我的main函数冲突了

	解决方案：要么把源码统一放在src目录下，要么要求使用者不要把build放到和源码同一个目录里，大牛建议是把源代码放到src目录下。

#2 项目配置变量

- CMAKE_BUILD_TYPE
构建的类型是调试模式还是发布模式。

C++编译有一个优化的功能。
CMAKE_BUILD_TYPE是CMake中一个特殊的变量，用于控制构建类型，它的值可以是如下4中：
1. Debug调试模式，完全不优化，生成调试信息，方便调试程序
2. Release发布模式，优化程度最高，性能最佳，但是编译比Debug慢。体积会变大，为了达到最佳的运行速度而牺牲大小。
3. MinSizeRel最小体积发布，生成的文件比Release更小，不完全优化，加少二进制体积；为了达到最小的生成大小，而上面的优化目标不同
4. RelWithDebInfo带调试信息发布，生成的文件比Release更大，因为带有调试的符号信息

默认情况下CMAKE_BUILD_TYPE为空字符串，这时相当于Debug构建类型

编写方法：
set(CMAKE_BUILD_TYPE Release)

- 各种构建模式在编译器选项上的区别

在Release模式下，追求的是程序的最佳性能表现，此时编译器会对程序做最大的代码优化以达到最快运行速度，同时由于代码优化后不与源代码一致，此模式下一般会丢失大量的调试信息。

1. Debug: '-O0 -g'
2. Release: '-O3 -DNDEBUG' # -NDEBUG宏会使assert被去除掉
3. MinSizeRel: '-Os -DNDEBUG'
4. RelWithDebInfo: '-O2 -g -DNDEBUG'

- 小技巧：设定一个变量的默认值

因为默认生成的是Debug，效率很低，那么如何让CMAKE_BUILD_TYPE在用户没有指定的时候为Release，而用户指定的时候保持用户指定的值不变呢？

就是说CMake默认情况下CMAKE_BUILD_TYPE是一个空字符串，因此这里通过if (NOT CMAKE_BUILD_TYPE)判断是否为空，如果空则自动设定为Release模式。

大多数CMakeLists.txt的开头会有这三行，为的是让默认的构建类型为发布模型（高度优化）而不是默认的调试模式（不会优化）

	
	if (NOT CMAKE_BUILD_TYPE) 
      set(CMAKE_BUILD_TYPE Release)
	endif()

	以上可以说是标准模板


- project

初始化项目信息，并把当前CMakeLists.txt所在位置作为根目录

		
	project(hellocmake) # 创将一个hellocmake的项目

	message("PROJECT_NAME: ${PROJECT_NAME}")
	message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}") 当前项目的源码目录
	message("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}") 当前项目的可执行文件所在目录
	message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}") 
	message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINANRY_DIR}")


- 和子模块的关系：PROJECT_X_DIR和CMAKE_CURRENT_X_DIR的区别


	PROJECT_SOURCE_DIR: 表示最近一次调用project的CMakeLists.txt所在的源码目录
	CMAKE_CURRENT_SOURCE_DIR：表示当前CMakeLists.txt所在的源码目录
	CMAKE_SOURCE_DIR：表示最外层CMakeLists.txt的源码根目录
	利用PROJECT_SOURCE_DIR可以实现从子模块里获得外层目录的路径
	不建议用CMAKE_SOURCE_DIR，那样会让我的项目无法被人作为子模块使用


- 其他相关变量

		
	PROJECT_SOURCE_DIR:当前项目源码路径	
	PROJECT_BINARY_DIR:当前项目输出路径
	CMAKE_SOURCE_DIR:根项目源码路径
	CMAKE_BINARY_DIR:根项目输出路径
	PROJECT_IS_TOP_LEVEL:BOOL类型，表示当前项目是否是（最顶层的）根项目
	PROJECT_NAME:当前项目名
	CMAKE_PROJECT_NAME: 根项目的项目名
	详见：https://cmake.org/cmake/help/latest/command/project.html


- 流行
现在CMake动不动就可以将当前的项目作为子模块，就可以用PROJECT_IS_TOP_LEVEL来判断是否需要配置依赖

- 子模块里也可以使用project命令
将当前目录作为一个独立的子项目，这样一来，PROJECT_SOURCE_DIR就会是子模块的源码目录而不是外层了。
这个时候，CMake会认为这个子模块是个独立的项目，会额外做一些初始化。他的构建目录PROJECT_BINARY_DIR也会变成build/<源码相对路径>。
这样在MSVC上也会看到build/mylib/mylib.vcxproj的生成


- project的初始化

1. LANGUAGES字段
project(项目名 LANGUAGES 使用的语言列表...)  指定了该项目使用了哪些编程语言
目前支持的语言包括：

1. C：C语言
2. CXX：C++语言
3. ASM： 汇编语言
4. Fortran：老年人的编程语言
5. CUDA： 英伟达的CUDA（3.8版本新增）
6. OBJC：苹果的Objective-C(3.16版本新增)
7. OBJCXX：苹果的Objective-C++(3.16版本新增)

如果不指定LANGUAGES，默认为C和CXX
		
	project(hellocmake LANGUAGES C CXX) # 表示两种语言都启用，就是说源码中有C和C++语言

	还可这么设置：
	project(hellocmake LANGUAGES NONE)
	enable_language(CXX) # 逐一启动语言，这样就把它放在if语句里，从而只在某些选项开启才启用某语言之类的情况

	add_executable(main main.cc)
		

- 设置C++标注：CMAKE_CXX_STANDARD变量

它是一个整数，表示要用的C++标准，比如：C++17，那就设为17，需要C++23就设为23。
CMAKE_CXX_STANDARD_REQUIRED是BOOL类型，可以为ON或OFF，默认为OFF。它表示是否一定要支持你指定的C++标准。如果为OFF则CMake检测到编译器不支持C++17时不报错，而是默默调低到C++14给我用；为ON时则发现不支持报错，更安全。

	set(CMAKE_CXX_STARDARD 17)
	set(CMAKE_CXX_STARDARD_REQUIRED ON) #通常都设置为ON
	set(CMAKE_CXX_EXTENSIONS ON) # 对应 g++ -std=c++17， 还有一个g++ -std=gnu++17,就是带了gcc的一些私货，若是要兼容其他编译器（如MSVC）的项目，就会设为OFF，防止不小心用来GCC才有的特征。若是有msvc的项目，就一般设置为OFF，否则在MSVC上就会出错。OFF就是不让它启用gcc特有的特性。否则，就可以设置为ON。
	这些变量要设置在project之前，这样在project时，编译就会检测这些特性，就不容易出错。


- 常见误区：手动添加-std=c++17

请勿直接修改CMAKE_CXX_FALGS来添加-std=c++17，必须使用CMake帮我封装好的CMAKE_CXX_STARDARD(从业人员告诉你的正确用法)。
用GCC的用户手动指定了-std=c++17，让MSVC的用户怎么办？

此外CMake已自动根据CMAKE_CXX_STANDARD的默认值11添加-std=c++11选项，再添加个-std=c++17选项不就冲突了码？所以，请用CMAKE_CXX_STANDARD。

- project的初始化：VERSION字段

project(项目名 VERSION x.y.z)可以把当前项目的版本号设定为x.y.z，之后就可以通过PROJECT_VERSION来获得当前项目的版本，如：project(hellocmake VERSION 0.2.3)

1. PROJECT_VERSION_MAJOR: 获取x（主版本号）
2. PROJECT_VERSION_MINOR: 获取y（次版本号）
3. PROJECT_VERSION_PATCH: 获取z（补丁版本号）

- 一些没什么用，但CMake官方不知为何就是提供了项目的字段

1. DESCRIPTION "A free ..."
2. HOMEPAGE_URL https://github.com/seeside-play/course

若是有很多个project，就可以通过这两个变量来获得目录
1. ${hellomake_VERSION}
2. ${hellomake_SOURCE_DIR}
3. ${hellomake_BINARY_DIR}

- 小技巧： CMake的${}表达式可以嵌套
如：${PROJECT_NAME}求值结果是hellocmake，那么${${PROJECT_NAME}_VERSION}相当于${hellocmake_VERSION},进一步求值的结果就是刚刚指定的0.2.3

- cmake_minimum_required指定最低所需版本
我所写的CMakeLists.txt包含了最低版本所具有的语法，若是用户的CMake小于指定版本，会出现“CMake版本不足”的提示
官方建议加上：cmake_minimum_required(VERSION 3.15),还可通过3.15...3.20来表示最高版本不超过3.20。这会对cmake_policy有所影响。若是指定的版本太低，有些policy就不会启用。

- 其他变量

https//blog.csdn.net/fuyajun01/article/details/8891749

##3 链接库文件

### 改进mylib作为一个静态库

add_library(mylib STATIC mylib.cpp)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC mylib)


### 动态库

在运行时动态查找
add_library(mylib SHARED mylib.cpp)
add_executale(main main.cc)
target_link_libraries(main PUBLIC mylib)

### 改进：mylib作为对象库

对象库类似于静态库，但是不生成.a文件，只由CMake记住该库生成了哪些对象文件。对象库是CMake自创的，绕开了编译器和操作系统的各种繁琐规则，保证了跨平台统一性。在自己的项目中，大佬推荐全部用对象库（OBJECT）替代静态库避免跨平台的麻烦。对象库仅仅作为组织代码的方式，而实际生成的可执行文件只有一个，减轻了部署的困难。不需要拷贝很多文件到目标机器上，它是一种代码的组织结构，轻量级。
add_library(mylib OBJECT mylib.cpp)
add_executale(main main.cc)
target_link_libraries(main PUBLIC mylib)
对象库可以指定不同的编译选项，还可绕开编译器的规则保证跨平台是统一的


静态库的麻烦：GCC编译器自作聪明，会自动删除没有引用符号的那些对象。就是在没有人引用相应的静态库文件时（如该文件中有一个static声明），就会将这个cpp的.o文件删除，而我就想静态初始化。不引用但也能静态初始化。而对象库可以绕开编译器的不统一，保证不会自动删除没有引用到的对象文件。 这样就可以在静态库里定义一个总类，而这个总类没有出现在头文件里。这样就可以在静态初始化过程中，注册一些信息，而头文件又不用添加。
mylib.cpp
#include <cstdio>
static int unused = printf("mylib initialized\n");

main.cpp
#include <cstdio>
int main() {
  printf("main function\n");
}

mylib initialized
main function

add_library无参数时，是静态库还是动态库？
add_library(mylib mylib.cpp) # 没有指定STATIC还是SHARED，它默认是根据BUILD_SHARED_LIBS这个变量的值来决定是动态库还是静态库。ON则表示SHARED，OFF相当于STATIC，若未指定BUILD_SHARED_LIBS，默认是STATIC。如是看到这个定义，就可通过命令行 cmake -B build -DBUILD_SHARED_LIBS:BOOL=ON来让他全部生成动态库。

小技巧：设定一个变量的默认值
if (NOT DEFINED BUILD_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ON)
endif()

常见坑点：动态库无法链接静态库
设置为静态库，误以为会让静态库链接到可执行文件上，若描述静态库链接到动态库上，而动态库在内存中的地址是会变化的，它在编译时会指定一个-fPIC选项，但是静态库就没有这个选项，它不想变化这个地址，而动态库却需要变化这个地址。就会出现 relocate...这类的错误提醒。

解决方法：要么把静态库变成对象库，要么让静态库编译时也生成位置无关的代码（PIC），这样才能装在动态库里，代码如下：
set(CMAKE_POSITION_INDEPENDENT_CODE ON) // 表示在它后面所有创建的对象都启动位置无关（PIC）
add_library(otherlib STATIC otherlib.cpp)

add_library(mylib SHARED mylib.cpp)
target_link_libraries(mylib PUBLIC otherlib)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC mylib)

也可以只针对一个库，只对他启动位置无关的代码（PIC）
add_library(otherlib STATIC otherlib.cpp) // 如果不出现IDE中，可以不用指定.h头文件，最好指定
set_proprety(TARGET otherlib PROPRETY POSITION_INDEPENDENT_CODE ON) // 只针对otherlib库启动PIC

# 4对象的属性 

可以只对一个目标启动某一种属性,除了POSITION_INDEPENDENT_CODE还有哪些这样的属性？
如：
add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17) # 这里没有CMAKE_前缀，其实是一样的

target_compile_options(main PUBLIC "-std=c++17") # 不可取，会与CMake内置变量冲突，使用上面的定义更加可取。就说直接用字符串，“XXX=XX”的形式不可取，要用CMAKE定义的变量来指定

	set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED ON)
	set_property(TARGET main PROPERTY WIN32_EXECUTABLE ON)
	set_property(TARGET main PROPERTY LINK_WHAT_YOU_USE ON)
	set_property(TARGET main PROPERTY LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)  # 设置动态链接库的输出路径（默认${CMAKE_BINARY_DIR}）
	set_property(TARGET main PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)  # 设置静态链接库的输出路径（默认${CMAKE_BINARY_DIR}）
	set_property(TARGET main PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)  # 设置可执行文件的输出路径（默认${CMAKE_BINARY_DIR}）

这样若是觉得麻烦，可以用如下设置，带来极大的方便：

	set_target_properties(main PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	WIN32_EXECUTABLE ON
	LINK_WHAT_YOU_USE ON
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	)

还可以全局设置，那么所有的对象都共享相同的属性，如下所示

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
...其他的类似,需要在执行生成可执行文件之前先定义好
add_executable(main main.cpp)

# 链接子模块mylib

cmake_minimum_require(VERSION 3.15)
add_subdirectory(mylib) #  链接子模块的mylib,在目录的CMakeLists.txt内容为：add_library(mylib SHARED mylib.cpp mylib.h)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC mylib)

在Windows下因dll和exe不在同一个目录，为出错弹窗。那能不能让CMake把dll和exe放在同一个目录中呢?当然可以，就可以通过set_property来给目标的可执行文件设置输出属性，如下：
add_library(mylib SHARED mylib.cpp mylib.h)
set_prorperty(TARGET mylib PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set_prorperty(TARGET mylib PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set_prorperty(TARGET mylib PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set_prorperty(TARGET mylib PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})
set_prorperty(TARGET mylib PROPERTY ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})
set_prorperty(TARGET mylib PROPERTY LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})

set_prorperty(TARGET mylib PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEAE ${PROJECT_BINARY_DIR}) 
set_prorperty(TARGET mylib PROPERTY ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}) set_prorperty(TARGET mylib PROPERTY LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}) 

设置这么多，还挺麻烦的，这是为了伺候微软的window系统

### 不懂就问，为什么说Linux系统是永远的神？
Linux系统支持RPATH，CMake会让生成出来可执行文件的RPATH字段指向它链接了的.so文件所在目录，运行时会优先从RPATH里找链接库，所以即时不在同目录也能找到。

第三种方案，写在微软全家通，安装Arch Linux系统。

需要手动修改或查看一个ELF文件的RPATH，可以用chrpath或pathelf命令

# 5 链接第三方库

链接操作系统或第三方的库，是指链接/usr/lib/cmake下的某包的一个组件或多个组件。比如使用tbb这个库文件，它在/usr/lib/cmake/TBB下，根据TBBConfig.cmake来指定配置信息

	add_executable(main main.cpp)
	target_link_libraries(main PUBLIC tbb)

	在源码中需要包含头文件，之后就可以调用对应的接口。如要文件连接/usr/lib下的库文件，在该文件下有如下文件，如： libttb.so libtbb.so.12 libtbb.so.12.5，会先连接libtbb.so，进而连接libtbb.so.12，最后连接到libtbb.so.12.5。这也是Linux的特色。

## 直接链接tbb的缺点

如果这样直接指定tbb，CMake会让链接器在系统的库目录里查找tbb，它会找到/usr/lib/libtbb.so这个系统自带的，但这对于没有一个固定库安装位置的Windows系统并不适用。此外，它还要求tbb的头文件就在/usr/include这个系统默认的头文件目录，这样才能#include  <tbb/parallel_for.h>不会出错，如果tbb的头文件在其它地方就需要再加一个 target_include_directories 设置额外的头文件查找目录。所以，直接使用tbb，对Window不友好。

也可以直接写出全部路径，就是太硬核了，如： target_link_libraries(main PUBLIC C:/User/.../tbb.dll) ，这样没法跨平台。
CMake的路径分割符始终是/，也可以使用${x}/bin。/是正斜杠

### 更通用的方式：find_package

	find_package(TBB REQUIRED) 会在安装目录下查找/usr/lib/cmake/TBB/TBBConfig.cmake这个配置文件，并根据里面的配置信息创建TBB::tbb这个伪对象（它实际指向真正的tbb库文件路径/usr/lib/libtbb.so），之后通过target_link_libraries链接TBB::tbb就可以正常工作了。为啥用TBB::是模仿C++，表示在TBB包下面的tbb库，可能不止tbb这个组件，还有其它组件，而TBB是一个包

TBB::tbb是一个伪对象（imported），除了它会指向/usr/lib/libtbb.so之外，TBBConfig.cmake还会给TBB::tbb添加一些PUBLIC属性，用于让链接了它的对象带上一些flag之类的。比如，TBB安装在/opt/tbb目录下，头文件在/opt/tbb/include里， 那么这时TBBConfig.cmake里就会有：target_include_directories(TBB::tbb PUBLIC /opt/tbb/include)，这样main在链接了TBB::tbb的时候，也会被“传染”上/opt/tbb/include这个目录上，不用调用者手动添加了。再比如，TBB::tbb链接了另一个库Blosc::blosc,那这个库也会自动链接到main上，无需手动添加。只有一些特别老的库，才会自己写FindCMake

### 为什么现代CMake的PUBLIC属性的传播机制如此便利？
现代CMake：

	find_package(TBB COMPONTES tbb tbbmalloc REQUIRED) # 自动查找包中的组件，并在下面的链接处链接。确实很方便，且不用关心tbb所依赖的库，因为tbb中的.cmake已经是指定了的，并且是PUBLIC，可以继承到当前target中
	find_package(TBB REQUIRED) # 可使用该命令替代上面的命令
	add_executable(myapp myapp.cpp)
	target_link_libraries(myapp TBB::tbb TBB::tbbmalloc)

	注意在/usr/lib/cmake/TBB/下有TBBConfig.cmake，而我们用的就是TBB这个包，它的组件在.cmake中有所描述。

	须在add_library之后设置库属性set_target_properties


    其实更好的是使用find_package(TBB CONFIG REQUIREED)，添加了CONFIG选项，会优先查找TBBConfig.cmake（系统自带）而不是FindTBB.cmake(项目作者常把它塞在cmake/目录里并添加到CMAKE_MODULE_PATH)。这样能保证寻找包的这个.cmake脚本是和系统自带的tbb版本是适配的，而不是项目作者当前下载的哪个版本的.cmake脚本。

	add_executable(main main.cpp)
	find_package(TBB CONFIG REQUIRED) # 目前的包都使用CONFIG，若是老的CMake不支持CONFIG，而是使用FIND的脚本
	target_link_libraries(main PUBLIC TBB::tbb)


/usr/lib/cmake/TBB/TBBConfig.cmake长啥样子？
不论是TBBConfig.cmake还是FindTBB.cmake，这个文件通常由库的作者提供，在Linux的包管理器安装tbb后，也会自动安装这个文件。少部分对CMake不友好的第三方库，需要自己写FindXXX.cmake才能使用。

	如：
	# Create imported target TBB::tbb
	add_library(TBB::tbb SHARED IMPORTED) # IMPORTED表示什么？表示伪目标

	现代版已经使用Config而不用自己写Find的.cmake脚本


## QA find_package(Qt5 REQUIRED)出错了

	find_package(Qt5 REQUIRED)
	target_link_libraries(main PUBLIC Qt5::Widgets Qt5::Gui)

出现错误：
CMake Error at CMakeLists.txt:6 (find_pakcage):
  Found pakcage configuration file:
  /usr/lib64/cmake/Qt5/Qt5Config.cmake
  but is set Qt5_FOUND to FALSE so package "Qt5" is considered to be NOT FOUOND. Reason given by package:
  The Qt5 pakcage required at least one component

  Qt对CMake支持很好，所以它们自己写了Config.cmake，至少需要一个组件，那么可以这样写：
  find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)
  target_link_libraries(main PUBLIC Qt5::Widgets Qt5::Gui)

find_package生成的伪对象（imported target）都按照“包名::组件名”的格式命名。我可以在find_package中通过COMPONENTS选项后面跟随一个列表表示需要用的组件。   

常见问题：windows上找不到Qt5包怎么办？我明明安装了！
因为linux有固定的安装目录（/usr/lib）之类的默认路径可以搜索，而Window系统的安装目录却不是该目录 

Linux有时候也会安装在/opt下，不想暴露到全局的默认路径下。CMake只会找/usr/lib之类的目录，不会找/opt，\\program files这类的目录，那怎么办呢？如若假设Qt5安装在C:\Qt\Qt5.14.2\msvc2019_64\lib\cmake\，有4种办法，如下：

     	第1种：就是在CMAEKE_MODULE_PATH中新增一个目录，这是CMake的模块默认查找目录集。必须用正斜杠，因为CMake是“亲Unix”的构建系统
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} C:/Qt/Qt5.14.2/msvc2019_64/lib/cmake)
	
	第2种：设置Qt5_DIR这个变量
	set(Qt5_DIR C:/Qt/Qt5.14.2/msvc2019_64/lib/cmake) # 这样的话只有Qt5这个包会去这个目录里搜索Qt5Config.cmake,更有针对性。之后就可使用find_package指令了
	这是一个固定模板：包名_DIR，这样可以设定具体包的路径，这是一个更好的办法。即：设置<包名>_DIR变量指向<包名>Config.cmake所在位置

	第3种（推荐）：直接在命令行通过-DQt5_DIR="XXX"指定，这样就不用修改CMakeLists.txt
	cmake -B build -DQt5_DIR="Qt5_DIR C:/Qt/Qt5.14.2/msvc2019_64/lib/cmake"，即通过缓存变量来指定	

	第4种，还是通过设置环境变量Qt5_DIR也是可以的，就是对Windows用户比较困难
	export Qt5_DIR="/opt/Qt5.14.2/lib/cmake" # 这里的export就是添加环境变量已经相应的值
	cmake -B build


### 不指定REQUIRED
表示找不到不报错，只会设置TBB_FOUND为FALSE

	find_package(TBB)
	if (TBB_FOUND)
	  message(STATUS "TBB found at: ${TBB_DIR}")
	  target_link_libraries(main PUBLIC TBB::tbb)
	  target_compile_definitions(main PUBLIC WITH_TBB) # 定预处理宏，以便在码源中控制不同的执行路径
	else()
	   message(WARNING "TBB not found! using serial for")
	endif()
	可用于添加一些可选的依赖，若没有也不要紧的那种，这时我会抛出一个警告。找到会把TBB_FOUND设置为TRUE，TBB_DIR设置为TBBConfig.cmake所在路径。找不到会把TBB_FOUND设为FALSE，TBB_DIR为空。这里我在找到TBB时定义WITH_TBB宏，稍后.cpp里就可以根据这个判断。若果找不到TBB就可以fallback到保守的实现。

	这样在.cpp里可以根据WITH_TBB宏，找不到TBB时退化到串行for循环
	main.cpp
	#ifdef WIHT_TBB
	#include <tbb/parallel_for.h>
	#endif

	int main() {
	
	#ifdef WIHT_TBB
	  tbb::parallel_for(0, 4, [&](int i)) {
	#else
	  for (int i = 0; i < 4; ++i) {
	#endif
		  printf("hello world %d!\n", i);
	#ifdef WIHT_TBB
		});
	#else
	    }
	#endif
	}


也可以用TARGET判断是否存在TBB::tbb这个伪对象，实现同样的效果

	find_package(TBB)
	if (TARGET TBB::tbb) # TARGET命令，若是找到了TBB::tbb就是TRUE
		message(STATUS "TBB found at: ${TBB_DIR}")
		target_link_libraries(main PUBLIC TBB::tbb)
		target_compile_definitions(main PUBLIC WIHT_TBB)
	else()
		message(WARNING "TBB not found! using serial for")
	endif()

也可以复合if的各种判断语句，例如： NOT TARGET TBB::tbb AND TARGET Eigen3::eigen表示找不到TBB但是找得到Eigen3的情况也可以

# 6 输出与变量
在运行cmake -B build时，打印字符串（用于调试）。可以用message指令，打印到控制台上。   

	message("Hello World") # 输出时没有--符号，cmake认为这个是调试信息
	message(STATUS "Hello World") # 输出时会有--符号，表示状态信息，告诉你做了这件事情，你也可以不看
	message(WARNING "This is a warning sign!") # 表示警告信息，会有黄色的字体显示出来，还会告诉我在CMakeLists.txt中的第几行，还会和下面的信息拉开一段距离。
	message(AUTHOR_WARNING "...") 表示仅给项目作者看的警告信息，上一个关不掉，而这个可以通过-Wno-dev来关闭
	即通过cmake -B build -Wno-dev 就可以关闭
	message(FATAL_ERROR "...") 表示错误信息，会终止CMake的运行，之后的指令都不会被执行。红色字体显示，支持脚本代码行以及提示信息。若是还是想让它运行，而不终止，可以使用SEND_ERROR
	message(SEND_ERROR "...") 表示是错误信息，但之后的语句仍继续执行。它不终止执行，只是报错。 


### message 可以用于打印变量

	set(myvar "Hello World")
	message("my var is: ${myvar}") # 使用${}来获取变量的值

	如果set没加引号会怎么样？会变成分号分割的列表
	set(myvar hello world) 等价于 set(myvar "hello;world"),这是一种语法糖,是cmake中的一种列表

	如果message没加引号会怎么？会把列表里的字符串当成它的关键字，那问题就大啦。除非确实需要列表，否则大佬建议在不确定的地方打上引号，同时在set中也打上引号，这样对于列表元素若有空格也是一个完整的列表项，也没有关系，如下：
	set(sources "main.cpp" "mylib.cpp" "C:/Program Files/a.cpp")
	message("${sources}")


# 7 变量和缓存
这是CMake的最大看点

- 重复执行cmake -B build 会有什么区别？
可以看到第二次的输出少了很多，这是因为CMake第一遍需要检测编译器和C++特性等比较耗时，检测完会把结果存储到 **缓存**中，这样第二遍运行cmake -B build时就可以直接用缓存的值，就不需要再检测一遍了。

本来是好意，让我在下次配置时，变得更快些。但也会带来一些问题，如

- 如何清除缓存？删build大法了解一下
比如说外部的编译器卸载了，CMake里还指缓存的却是旧的值（编译器原来的路径），就会导致一系列问题。这时需要清除缓存，最简单的办法就是删除build文件夹，然后重新运行cmake -B build。缓存是很多CMake出错的根源，因此如果出现诡异的错误，可以试试看删除build全部重新构建。经典CMake笑话：“99%的cmake错误可以用删除build解决” “删build大法好” rm -fr build  cmake -B build

缺点就是，会导致编译的中检结果（.o文件）都没了，重新编译要花费很长实践。如果只想清除缓存，不想从头重新编译，可以只删除build/CMakeCache.txt这个文件。这个文件里面装的就是缓存的变量，删除了它，就可以让CMake强制重新检测一遍所有库和编译器。

- 清除缓存，其实只需删除build/CMakeCache.txt就可以了
若不是缓存的问题，而是中间文件有问题，还是需要删除build文件，大部分时间只要删除CMakeCache.txt就够了，就不用重新编译了嘛，那多快阿。

- build/CMakeCache.txt的内容
CMAKE_BUILD_TYPE:STRING=Release   变量名：类型=值

- find_package就用到了缓存机制
变量缓存的意义在于能够把find_package找到库文件位置等信息，储存起来。这样下次执行find_package时，就会利用上次缓存的变量，直接返回。避免重复执行cmake -B时速度变慢的问题。如：

	Qt5_DIR:PATH=/usr/lib54/cmake/Qt5

缓存起来，下次就不会变慢了。但也会有一个问题，比如cmake -B build之后，发现没有安装，等安装上之后，直接使用cmake --build build仍然会有问题。因为即便安装上了库，但是上一次配置时是FOUND false，缓存了没有找到库所留下的缓存标记。这个时候只需要rm -fr build/CMakeCache.txt，删除缓存文件，在执行以便cmake -B build就会再去找相应的库（如tbb）


- 设置缓存变量
我自己来设置缓存，不让cmake来设置。这样缓存的变量就会出现在build/CMakeCache.txt里

	语法： set(变量名 "变量值" CACHE 变量类型 "注释")
	如：
	set(myvar "hello" CACHE STRING "this is the docstring.") // 注释就是在定义在变量上面的解释，特别注意，这里的hello是默认值，类似于C++中的static变量初始值。
	message("myvar is ${myvar}")

这个缓存的变量，如myvar在前面加上-D就是参数啦，和参数的语法一样。

- 常见问题：我修改了CMakeLists.txt里的set的值，却没有更新？
为了更新缓存变量，直接修改CMakeLists.txt里的值，没有用。因为set(...CACHE...)缓存变量已经存在，不会更新缓存的值。CMakeLists.txt里set的被认为是“默认值”，因此不会在第二次set的时候更新。

	set(myvar "world" CACHE STRING "this is the docstring.") // 注释就是在定义在变量上面的解释
	message("myvar is ${myvar}")

这时，cmake -B build之后，还是原来的hello。最简单的办法就是删除文件文件，官方推荐cmake -B build -Dmyvar=world,使用-D参数来更新缓存。就是说，由用户来修改该变量

- 命令行-D参数修改太硬核了，有没有图形化的缓存编辑器呢？
在Linux中，运行ccmake -B build来启动基于终端的可视化缓存编辑菜单,上下键选择，回车确认修改。使用ccmake图形化编辑器修改变量，这样就比较轻松。按空格可以在ON和OFF之间切换，可以设置很多变量。在Windows下是cmake-gui -B build来启动图形编辑器编辑各个缓存选项，当然直接打开build/CMakeCache.txt修改后保存也是可以的。CMakeCache.txt保存为文本存储数据，就是可供用户手动编辑或第三方软件打开解析的。

- 缓存变量到底该如何更新？暴力解决：删build大法
更好的办法就是-D或ccmake -B build启动可视化编辑器，还有就是强制更新缓存

	set(myvar "world" CACHE STRING "this is the docstring." FORCE) // 注释就是在定义在变量上面的解释

### 缓存变量类型
STRING:字符串，如“hello， Wrold”
FILEPATH：文件路径，如“C:/vcpkg/scripts/buildsystems/vcpkg.cmake”
PATH：目录路径，例如：“C:/Qt/Qt5.14.2/msvc2019_64/lib/cmake/”
BOOL:布尔值，只有两个取值，ON或OFF
注意：TRUE和ON等价，FALSE和OFF等价；YES和ON等价，NO和OFF等价。因为历史原因才保留TRUE和YES


案例：添加一个BOOL类型的缓存变量，用于控制要不要开启某些特征

	add_executalbe(main main.cpp)
	set(WITH_TBB ON CACHE BOOL "set to ON to enable TBB, OFF to disable TBB")
	if (WITH_TBB)
		target_compile_definitions(main PUBLIC WITH_TBB)
		find_package(TBB REQUIRED)
		target_link_libraries(main PUBLIC TBB::tbb)
	endif()
	
	那么使用：cmake -B build -DWITH_TBB:BOOL=ON(用户这样做就会开启，而OFF就会关闭)，默认是ON，这样用户就不用开启了

CMake对BOOL类型缓存的set指令提供了一个简写：option

	option(变量 “描述” 变量值) 等价于 set(变量名 CACHE BOOL 变量值 “描述”)和set一样，一旦定义不会去更新哦，它的本质就是set，例子如下所示：
	option(WITH_TBB "set to ON to enable TBB, OFF to disable TBB", ON)	以下部分和上面一致
	set(WITH_TBB ON CACHE BOOL "set to ON to enable TBB, OFF to disable TBB")

	那么经典问题：option设为OFF了，为什么它还是ON呀？一旦定义后，就会放到CMakeCache.txt缓存中，再修改不会生效。
	要改就通过命令：cmake -B build -DWITH_TBB:BOOL=OFF(这是官方推荐方法，当然也可以通过ccmake和直接修改CMakeCache.txt文件，或者说不用option，而是用set加FORCE即可始终强制更新缓存，还就是删build大法，它可以把缓存变量强制初始化为CMakeLists.txt里的值)

- 绕开缓存的方法	
使用普通变量，但仅当没有定义时设定为默认值。一般来说CMake自带的变量（如：CMAKE_BUILD_TYPE）都会这样设置。这样项目的使用者还是可以用-D来指定参数，不过会在ccmake里看不到，因为ccmake是查找缓存变量而不是普通变量

	if (NOT DEFINED WITH_TBB)
		set(WITH_TBB ON)
	endif()
	message("WITH_TBB: ${WITH_TBB}")
	if (WITH_TBB)
		...
	endif()

option的好处，是能让ccmake看到，这样设置就比较方便了，不让，就都用上面的if语句啦

缓存比较坑爹，但也是有它的优点。

# 8 跨平台与编译器
如何判断不同的平台，判断不同的编译器。
C++可以在代码中定义宏，如：#define  MY_MACRO 233，相当于在CMakeLists.txt中定义如下指令：target_compile_definitions(main PUBLIC MY_MACRO=233),它也相当于 gcc -DMY_MACRO=233，原理是一样的。

- 根据不同的操作系统，把宏定义成不同的值
使用变量：CMAKE_SYSTEM_NAME，可以为Windows，Linux，Darwin等，代码如下：

	if (CMAKE_SYSTEM_NAME MATCHS "Windows")
		target_compile_definitions(main PUBLIC MY_NAME="Bill Gates")
	elseif (CMAKE_SYSTEM_NAME MATCHS "Linux")
		target_compile_definitions(main PUBLIC MY_NAME="Linux Torvalds")
	elesif (CMAKE_SYSTEM_NAME MATCHS "Darwin")
		target_compile_definitions(main PUBLIC MY_NAME="Steve Jobs")
	endif()

CMake还提供了一些简写变量：WIN32，APPLE，UNIX，ANDROID， IOS等。虽然叫WIN32，实际上对32位Windows和64位Widnows都适用，APPLE对于所有苹果产品(MacOS或i)都为真，UNIX对于所有Unix类系统（FreeBSD, Linux, Android, MacOS, iOS）都为真，脚本如下：

	if (WIN32)
		target_compile_definitions(main PUBLIC MY_MACRO="...")
	elseif (UNIX AND NOT APPLE)
		target_compile_definitions(main PUBLIC MY_MACRO="...")
	elseif (APPLE)
		target_compile_definitions(main PUBLIC MY_MACRO="...")
	endif()
		

- 使用生成器表达式，简化成一条指令
语法： $<$<类型:值>:为真时的表达式>，自动进行了if判断。比如：$<$<PLATFORM_ID:Windwos>:MY_NAME="Bill Gates">,在Windows平台上会为：MY_NAME="Bill Gates"，其它平台上表现为空字符串。如下，在一行里完成上面的所有判断：
	
	target_compile_definitions(main PUBLIC
		$<$<PLATFORM_ID:Windwos>:MY_NAME="Bill Gates">			
		$<$<PLATFORM_ID:Linux,FreeBSD >:MY_NAME="Linus Torvalds">
		$<$<PLATFORM_ID:Darwin>:MY_NAME="Steve Jobs">
		)

	如需多个平台，可以用逗号分割开


- 判断当前用的是哪一款C++编译器

	if (CMAKE_CXX_COMPILER_ID MATCHS "GNU")
		target_compile_definitions(main PUBLIC MY_NAME="gcc")
	elseif (CMAKE_CXX_COMPILER_ID MATCHS "NVIDIA")
		target_compile_definitions(main PUBLIC MY_NAME="nvcc")
	if (CMAKE_CXX_COMPILER_ID MATCHS "Clang")
		target_compile_definitions(main PUBLIC MY_NAME="clang")
	if (CMAKE_CXX_COMPILER_ID MATCHS "MSVC")
		target_compile_definitions(main PUBLIC MY_NAME="msvc")
	endif()

也可以用生成器表达式判断编译器
	
	target_compile_definitions(main PUBLIC
		$<$<CXX_COMPILER_ID:GNU,Clang>:MY_NAME="Open-source">			
		$<$<CXX_COMPILER_ID:MSVC,NVIDIA>:MY_NAME="Commercial">			
		)

生成器表达式也可以做复杂的逻辑判断：
	$<$<AND:$<CXX_COMPILER_ID:GNU,Clang>, $<PLATFORM_ID:Linux,FreeBSD>>:MY_NAME="Open-source">

CMAKE还提供了一些简写变量：MSVC，CMAKE_COMPILER_IS_GNUCC 布尔变量

	if (MSVC)
		target_compile_definitions(main PUBLIC MY_NAME="MSVC")
	elseif (CMAKE_COMPILER_IS_GNUCC)
		target_compile_definitions(main PUBLIC MY_NAME="GCC")
	else()
		target_compile_definitions(main PUBLIC MY_NAME="Other compiler")
	elseif()

也可以将CMAKE_CXX_COMPILER_ID直接作为字符串变量，就是将它作为宏的一部分，这样C++代码中就可以知道了。如下：
	target_compile_definitions(main PUBLIC MY_NAME="The ${CMAKE_CXX_COMPILER_ID} Compiler")
	这样就实现了cmake中的变量值的内容可以通过宏定义的方式，导入到源码中，太强大了，实现了cmake和源码之间的信息通信。

- 从命令行参数指定编译器
cmake -B build -DCMAKE_CXX_COMPILER="/usr/bin/clang++", 这个必须是第一次配置build时定义才有效

也可以通过环境变量CXX指定: $CXX='which clang' cmake -B build 

- CMAKE_GENERATOR也可以了解一下
message("Generator: ${CMAKE_GENERATOR}")
message("c++ compiler: ${CMAKE_CXX_COMPILER}")
message("c compiler: ${CMAKE_C_COMPILER}")

- 分享：小彭老师使用的vimrc分享
github.com/archibate/vimrc
如何让vim支持cmake呢？因为使用了插件cmake4vim，输入CMake就可以完成config配置，输入CMakeBuild就能完成构建呢，CMakeRun就能够运行可执行程序。


# 9 分支与判断
BOOL类型的变量只有ON/OFF两种取值
if的特点：不需要加${},会自动尝试作为变量名求值，若没有变量，就将该值当做字符串。若加上了${}，则递归将该值当变量继续展开，若找不到，就以此为值,这样就会有隐患。最好不要加 ${},防止递归展开。若使用${},需要加一个引号，防止被当作变量名,if就不会帮助自动求值。所以，还是直接写上变量名最好。
	set(MYVAR Hello)
	if (MYVAR MATCHES "Hello") // MATCHES表示等于的意思，
	  message("MYVAR is Hello")
	else()
	  message("MYVAR is not Hello")
	endif()

# 10 变量与作用域

cmake对变量的大小写敏感，cmake区分大小写。cmake指令不分大小写，但是变量名，文件名是分大小写的
cmake除了括号之前的不分大小写，其它都分大小写。

变量的传播规则：父会传给子，但子模块定义的变量，父模块是感觉不到的。子模块中的定义的同名变量会覆盖父模块。若是要将子模块中的定义的变量也能够影响到父模块，需要加PARENT_SCOPE, eg. set(MYVAR ON PARENT_SCOPE)
缓存变量是真正的全局变量，如：set(MYVAR ON CACHE BOOL "" FORCE)，这样虽然子模块中定义了这个变量，但是父类及以上都可见，不推荐使用。
除了父子模块之外还有哪些是带独立作用域的？
include的XXX.cmake没有独立作用域
add_subdirectory的CMakeLists.txt有独立作用域
macro没有独立作用域，是因为直接插入执行的，它里面的变量会直接暴露出来。
function有独立作用域
（因此PARENT_SCOPE也可用于function的返回值）

环境变量的访问方式： $ENV{XX}
用${XX}访问的是局部变量，局部变量服从父子模块传播规则，还有就是访问系统的环境变量，若$ENV{PATH}就是获取PATH这个环境变量的值。

缓存变量的访问方式：$CACHE{xx},缓存变量和环境变量是不论父子模块都公用的，没有域一说。eg：$CACHE{CMAKE_BUILD_TYPE}

${xx}:找不到局部变量时，会自动去找缓存变量。
因此当CMAKE_BUILD_TYPE每出现在代码里，没有被设置为set，但被-D参数固定在缓存里了。所以${CMAKE_BUILD_TYPE}自动变成$CACHE{CMAKE_BUILD_TYPE}从而找到变量。

if (DEFINED XX) 判断某局部或缓存变量是否存在，eg if (DEFINED MYVAR)，还有就是要注意的，空字符串不代表变量不存在，也就是说变量可以定义空字符串，eg: set(MYVAR "") if (DEFINED MYVAR)  这里就是ON；而用 if (XX)，则表示变量有定义且不为空字符串，空字符串等价与FALSE。


if (DEFINED ENV{xx}) 判断某环境变量是否存在，因为$ENV{XXX}代表环境变量，因此在set和if中可以用ENV{XX}来表示环境变量。eg：if (DEFINED ENV{MYVAR}),来判断是否存在MYVAR这个环境变量。还有就是set(ENV{MYVAR} "hello"),也不需要$符号。就是说用set设置变量或if判断变量时，不需要使用$符号。环境变量是分大小写的，比如：$export MYVAR=world,还有一个bash小技巧，使用env查看所有环境变量。

# 11 其它小建议
CCache：编译加速器，进行编译加速缓存，方法如下：
把gcc -c main.cpp -o main  改为： ccache gcc -c main.cpp -o main 即可
在CMake中可以这样启用ccache（就是给每个编译和链接的命令前面加上ccache）会缓存到/tmp/ccache中	
CCache就是解决一改头文件，要全部重新编译的问题，哦有很麻烦的，大佬牛。

find_program(CCACHE_PROGREAM ccache)
if (CCACHE_PROGREAM)
	message(STATUS "Found CCache: ${CCACHE_PROGREAM}")
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGREAM})
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGREAM})


- 添加一个run伪目标，用于启动主程序（可执行文件）
创建一个run伪目标，其执行main的可执行文件
add_executable(main main.cpp)
add_custom_target(run COMMAND $<TARGET_FILE:main>) 添加一个目标名字为run，COMMAND后面代表需要运行的命令，TARGET_FILE就是获取main可执行文件的路径
用了生成器表达式$<TARGET_FILE:main>,会自动让run依赖与main。如是不放心有没有自动依赖，手动添加一个add_dependencies(run main)也是可以的。
这样就可以在命令行运行cmake --build build  --target run来启动main.exe,而不必根据不同的平台，手动写出build/main或者build\main.exe

- 再加一个configure伪目标，用于可视化地修改缓存变量
CMAKE_EDIT_COMMADN即是ccmake
这样就可以用cmake --build build --target configure来启动ccmake修改缓存了。这在Linux上相当与ccmake -B build，Windows则是cmake-gui -B build

add_custom_target(run COMMAND $<TARGET_FILE:main>)
if (CMAKE_EDIT_COMMAND)
	add_custom_target(configure COMMAND ${CMAKE_EDIT_COMMAND} -B ${CMAKE_BINARY_DIR})


再此，衷心感谢小彭老师的讲解。













