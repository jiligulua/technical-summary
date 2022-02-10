[参考](https://www.cnblogs.com/standardzero/p/10793746.html)
[参考](https://sqlpy.com/blogs/212533219)

# 1完整代码

		|-step2
		|--CMakeLists.txt
		|--tutorial.cxx
		|--MathFunctions
						|--CMakeLists.txt
						|--mysqrt.h
						|--mysqrt.cxx
		
		
		
		|--CMakeLists.txt
		
			cmake_minimum_required(VERSION 3.10)
			
			project(Tutorial)
			
			option(USE_MYMATH "Use tutorial provided math implementation" OFF)
			if(USE_MYMATH)
			  add_subdirectory(MathFunctions)
			  list(APPEND EXTRA_LIBS MathFunctions)
			  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
			endif()
			
			# 在执行cmake ../build时，会显示message信息
			if(USE_MYMATH)
				message("option USE_MYMATH is ${USE_MYMATH}")
			else()
				message("option USE_MYMATH not define")
			endif()

			
			add_executable(Tutorial tutorial.cxx)
			
			target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})
			
			target_include_directories(Tutorial PUBLIC 
										${PROJECT_BINARY_DIR}
										${EXTRA_INCLUDES}
										)
				
		
		|--MathFunctions
			|--CMakeLists.txt
		
		cmake_minimum_required(VERSION 3.10)
		
				#递归获取目录下所有的.cxx文件
				#file(GLOB_RECURSE cpp_files ./*.cxx)
				
				# 递归获取目录下所有的h文件
				#file(GLOB_RECURSE h_files ./*.h)
				
				project(MathFunctions)
				
				add_library(MathFunctions mysqrt.cxx)


# 2命令学习
- `add_library`

生成库文件，可以生成静态、动态等库文件，一般放在某一个子文件中。然后在主CMakeLists.text中，通过使用`add_subdirectory`来生成。

例如：
		## MathFunctions/CMakeLists.txt		

		add_library(MathFunctions mysqrt.cxx)

就是生成静态库MathFunctions，即libMathFunctions.a


		## CMakeLists.txt

		# add the MathFunctions library，执行子文件夹MathFunctions下的CMakeLists.txt
		add_subdirectory(MathFunctions)
		
		# add the executable，生成Tutorial可执行文件，源代码为tutorial.cxx
		add_executable(Tutorial tutorial.cxx)
		
		target_link_libraries(Tutorial PUBLIC MathFunctions)
		
		# add the binary tree to the search path for include files
		# so that we will find TutorialConfig.h
		target_include_directories(Tutorial PUBLIC
		                          "${PROJECT_BINARY_DIR}"
		                          "${PROJECT_SOURCE_DIR}/MathFunctions"
		                          )


[参考](https://blog.csdn.net/LaineGates/article/details/108242803)

- `target_link_libraries`: 设置要链接的库文件的名称，指出被依赖的库放在依赖它的库的后面

	-	语法
				
				target_link_libraries(<target>
				                      <PRIVATE|PUBLIC|INTERFACE> <item>...
				                     [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)



将被依赖的库放在依赖它的库的后面，上面中表示Tutorial依赖libMathFunctions.so

举例：


		target_link_libraries(myProjectExecutable A B.a C.so)


		在上面的命令中，libA.so可能依赖于libB.a和libC.so，如果顺序有错，链接时会报错。还有一点，B.a会告诉CMake优先使用静态链接库libB.a，C.so会告诉CMake优先使用动态链接库libC.so，也可直接使用库文件的相对路径或绝对路径。使用绝对路径的好处在 于，当依赖的库被更新时，make的时候也会重新链接。

[参考](https://blog.csdn.net/zhujianwei31415/article/details/50727952)

注意区分`target_link_libraries`和`link_libraries`的区别，请[参考](https://blog.csdn.net/u012483097/article/details/109066405)

- `link_libraries`：添加需要链接的库文件路径，注意这里是全路径

	- 例如
		- link_libraries("/opt/MATLAB/R2012a/bin/glnxa64/libeng.so")
		- link_libraries("/opt/MATLAB/R2012a/bin/glnxa64/libmx.so")
		- link_libraries("/opt/MATLAB/R2012a/bin/glnxa64/libeng.so"　"/opt/MATLAB/R2012a/bin/glnxa64/libmx.so")


-  `link_directories`：指定第三方库所在文件夹全路径

例如

		set(LINK_DIR  /Users/haoran/Downloads/wfdb/lib)
		link_directories({LINK_DIR})

这样在使用`target_link_libraries`时，只需要给出动态库的名字就行，如：


		target_link_libraries(myProjectExecutable eng mx)

		
- `include_directories`: 指定头文件所在文件夹全路径


完整的例子

		 
		cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
		include_directories("/opt/MATLAB/R2012a/extern/include")
		link_directories("/opt/MATLAB/R2012a/bin/glnxa64")
		add_executable(myProject main.cpp)
		target_link_libraries(myProject eng mx)
 
		#equals to below
		#target_link_libraries(myProject -leng -lmx)
		#target_link_libraries(myProject libeng.so libmx.so)


- `target_include_directories`

注意区分`target_include_directories`和`include_directories`


- option：添加开关宏

		option(USE_MYMATH "Use tutorial provided math implementation" ON)

		if(USE_MYMATH)
		  add_subdirectory(MathFunctions)
		  list(APPEND EXTRA_LIBS MathFunctions)
		  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
		endif()
- file: 可以递归搜索文件

		
		#递归获取目录下所有的.cxx文件
		file(GLOB_RECURSE cpp_files ./*.cxx)
		
		# 递归获取目录下所有的h文件
		file(GLOB_RECURSE h_files ./*.h)



# 