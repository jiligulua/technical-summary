# 1添加库的使用规范

# 2具体脚本
## 2.1`target_compile_definitions()`

向工程中加入预处理定义

语法：
		
		target_compile_definitions(<target>
		  <INTERFACE|PUBLIC|PRIVATE> [items1...]
		  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])


- cmake --build . --config release : 可以生成release版本，默认为debug版本


举例

		
		cmake_minimum_required(VERSION 3.15)
		
		project ( hello_world_prj )
		
		set( EXE_SOURCES
		    src/main.cpp
		    src/Hello.cpp
		)
		
		add_executable( hello_world_exe  ${EXE_SOURCES} )
		
		target_include_directories( hello_world_exe
		    PRIVATE 
		        ${PROJECT_SOURCE_DIR}/include
		)
		
		target_compile_definitions( hello_world_exe PRIVATE MY_DEF1 )
		target_compile_definitions( hello_world_exe PRIVATE MY_DEF2 )
		target_compile_definitions( hello_world_exe PRIVATE MY_DEF3 )
		target_compile_definitions( hello_world_exe
		                            PRIVATE 
		                                  MY_DEF4
		                                  MY_DEF5
		                                  MY_DEF6
		                                  )
		
		# 到此，向工程hello_world_prj中添加了如上的预处理


		add_executable( hello_world_exe_1024  ${EXE_SOURCES} )
		
		target_include_directories( hello_world_exe_1024
		    PRIVATE 
		        ${PROJECT_SOURCE_DIR}/include
		)
		
		target_compile_definitions( hello_world_exe_1024 PRIVATE HELLO_DEF1 )
		target_compile_definitions( hello_world_exe_1024 PRIVATE HELLO_DEF2 )

		# 到此，向工程hello_world_exe_1024中添加了如上的预处理


[参考](https://zhuanlan.zhihu.com/p/392942067)   
[参考](https://www.zhihu.com/people/jia-fei-miao-18-13)


## 2.2 `target_compile_options()`

向工程中添加编译选项，target目标文件必须已经存在啦

		Adds options to the COMPILE_OPTIONS or INTERFACE_COMPILE_OPTIONS target properties. These options are used when compiling the given <target>, which must have been created by a command such as add_executable() or add_library() and must not be an ALIAS target.

		在编译给定目标文件时，指定要用到的编译选项。target目标文件必须已经存在（由命令add_executable()或add_library()创建）且不能被IMPORTED修饰。

语法

		target_compile_options(<target> [BEFORE]
		  <INTERFACE|PUBLIC|PRIVATE> [items1...]
		  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])


###举例1

在cmake脚本中，设置编译选项可以通过`add_compile_options`命令，也可以通过set命令修改`CMAKE_CXX_FLAGS`或`CMAKE_C_FLAGS`。
使用这两种方式在有的情况下效果是一样的，但请注意它们还是有区别的：
`add_compile_options`命令添加的编译选项是针对所有编译器的(包括c和c++编译器)，而set命令设置`CMAKE_C_FLAGS`或`CMAKE_CXX_FLAGS`变量则是分别只针对c和c++编译器的。


		#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持
		if(CMAKE_COMPILER_IS_GNUCXX)
		    add_compile_options(-std=c++11)
		    message(STATUS "optional:-std=c++11")   
		endif(CMAKE_COMPILER_IS_GNUCXX)



使用add_compile_options添加-std=c++11选项，是想在编译c++代码时加上c++11支持选项。但是因为add_compile_options是针对所有类型编译器的，所以在编译c代码时，就会产生如下warning，消除的方法为：

		#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持，在Linux可以跑通
		if(CMAKE_COMPILER_IS_GNUCXX)
		    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
		    message(STATUS "optional:-std=c++11")   
		endif(CMAKE_COMPILER_IS_GNUCXX)



[参考1](https://blog.csdn.net/10km/article/details/51731959?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&utm_relevant_index=1)



###举例2

		cmake_minimum_required ( VERSION 3.15 )

		project ( COMPILE_OPTIONS_PRJ CXX )
		
		set ( PRJ_SRC_LIST )
		set ( PRJ_HEADER_LIST )
		set ( PRJ_LIBRARIES )
		set ( PRJ_INCLUDE_DIRS )
		
		file ( GLOB root_header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )
		file ( GLOB root_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
		
		list ( APPEND PRJ_HEADER_LIST ${root_header_files} )
		list ( APPEND PRJ_SRC_LIST ${root_src_files} )
		
		add_executable ( ${PROJECT_NAME} ${PRJ_SRC_LIST} ${PRJ_HEADER_LIST} )
		
		target_include_directories ( ${PROJECT_NAME}
			PRIVATE
				${PRJ_INCLUDE_DIRS}
		)
		
		target_compile_options ( ${PROJECT_NAME}
			PRIVATE
				-MY_OP1
		)
		
		target_compile_options ( ${PROJECT_NAME}
			PRIVATE
				-MY_OP2
		)
		
		target_compile_options ( ${PROJECT_NAME}
			PRIVATE
				-MY_OP3
		)
		
		get_target_property ( MY_COMPILE_OPTIONS ${PROJECT_NAME} COMPILE_OPTIONS )
		
		message ( STATUS "MY_COMPILE_OPTIONS  = ${MY_COMPILE_OPTIONS}" )
		
		target_compile_features ( ${PROJECT_NAME} 
			PUBLIC 
				cxx_std_14
		)
		
		target_link_libraries ( ${PROJECT_NAME} 
		    PRIVATE 
		        ${PRJ_LIBRARIES}
		)



[参考2](https://zhuanlan.zhihu.com/p/410979446)




## 2.3 `target_include_directories()`

举例

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

## 2.4 `target_link_libraries()`

详见 **Step1**

## 2.5 `target_compile_features`

Add expected compiler features to a target. 如cxx_std_14(就是添加C++14的编译特征，可以对C++14进行编译)

语法

		target_compile_features(<target> <PRIVATE|PUBLIC|INTERFACE> <feature> [...])

[参考](https://cmake.org/cmake/help/v3.1/command/target_compile_features.html)

最佳实践：参考**#2.2**中的举例2


Q：在ubuntu系统下，使用cmake编译jsoncpp的时候，执行cmake后，出现错误，关键信息为：target_compile_features specified unknown feature cxx_std_11 for target...

A：cmake版本太低，找不到cxx_std_11等相关宏的定义。解决方法：升级cmake版本到最新版。


# 3参考
[参考](https://cmake.org/cmake/help/latest/guide/tutorial/Adding%20Usage%20Requirements%20for%20a%20Library.html)

[参考](https://www.jianshu.com/p/8abf754654c4)