2022.2.7  
[参考1](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html)  
[参考2](https://blog.csdn.net/yufm/article/details/107659452)

# 1基本代码
在CMakeLists.txt中，填写如下代码：


		cmake_minimum_required(VERSION 3.10)
		
		# set the project name
		project(Tutorial)
		
		# add the executable
		add_executable(Tutorial tutorial.cxx)


- 指定cmake最低版本
- 设定工程的名字为Tutorial
- 指定可执行文件为Tutorial，源代码为tutorial.cxx
- 执行流程  
在当前目录下执行cmake 给出CMakeLists.txt所在目录即可，生成Makefile文件，
然后执行make（前提是目录切换到在Makefile所在目录），就可生成可执行文件Tutorial。

## 问题和解决方案
- 存在的问题：中间文件和源文件在同一个目录中，目录结构混乱。
- 解决的方法：创建一个中间build文件夹，与源文件所在目录的`src_dir`处于等级目录，命名为`src_dir_build`，然后执行
`src_build$ cmake ../src_dir`，这样生成的中间文件就会在当前目录（`src_build`）下，并生成Makefile，然后执行make就会生成可执行文件。

		mkdir src_dir_build  
		cd src_dir_build   
		cmake ../src_dir # run CMake to configure the project and generate a native build system，即生成Makefile
		cmake --build . # Then call that build system to actually compile/link the project， 其功能等同于直接make  


# 2添加版本号和配置文件头文件

## 2.1命令解释
###  2.1.1 `configure_file`

#### 2.1.1.1概述

- 语法
	
				configure_file(<input> <output>
			               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
			               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])

- 将`<input>`文件里面的内容复制到`<output>`文件中；
- 根据参数规则，替换@VAR@或${VAR}变量；
- [参考](https://www.cnblogs.com/gaox97329498/p/10952732.html)


#### 2.1.1.2 参数解析

- COPYONLY：仅拷贝` <input> `文件里面的内容到 `<output>` 文件， 不进行变量的替换；
- ESCAPE_QUOTES：使用反斜杠（C语言风格）来进行转义；
- @ONLY：限制替换， 仅仅替换 @VAR@ 变量， 不替换 ${VAR} 变量
- NEWLINE_STYLE：指定输入文件的新行格式， 例如：Unix 中使用的是 \n, windows 中使用的 \r\n
- **注意: ** COPYONLY 和 NEWLINE_STYLE 是冲突的，不能同时使用；

#### 2.1.1.3 代码展现

- CMakeLists.txt 文件内容:

		cmake_minimum_required(VERSION 3.5)
		
		project(Tutorial VERSION 1.0) # 对应的宏为Tutorial_VERSION_MAJOR和Tutorial_VERSION_MINOR
		
		message(STATUS "PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})
		message(STATUS "PROJECT_BINARY_DIR " ${PROJECT_BINARY_DIR})
		
		set(CMAKEDEFINE_VAR1 1)
		set(CMAKEDEFINE_VAR2 0)
		
		set(DEFINE_VAR1 1)
		set(DEFINE_VAR2 0)
		
		configure_file(TutorialConfig.h.in TutorialConfig.h) # 默认是将源文件所在的TutorialConfig.h.in copy 到可执行文件所在的目录，也可以向下面那样，显示指出。
		
		configure_file (
		  "${PROJECT_SOURCE_DIR}/Config.h.in"
		  "${PROJECT_BINARY_DIR}/Config.h"
		  )
		
		include_directories("$PROJECT_SOURCE_DIR")
		
		add_executable(DEMO tutorial.cpp)


- Config.h.in 文件内容

		/**
		 * This is the configure demo  
		 *    - CMAKEDEFINE_VAR1 = @CMAKEDEFINE_VAR1@
		 *    - CMAKEDEFINE_VAR2 = @CMAKEDEFINE_VAR2@
		 *    - DEFINE_VAR1      = @DEFINE_VAR1@
		 *    - DEFINE_VAR2      = @DEFINE_VAR2@
		 */
		
		/**
		 *  cmakedefine 会根据变量的值是否为真（类似 if）来变换为 #define VAR ... 或  #undef VAR 
		 */
		#cmakedefine CMAKEDEFINE_VAR1 @CMAKEDEFINE_VAR1@
		#cmakedefine CMAKEDEFINE_VAR2 @CMAKEDEFINE_VAR2@
		
		
		/**
		 * define 会直接根据规则来替换
		 */
		#define DEFINE_VAR1 @DEFINE_VAR1@
		#define DEFINE_VAR2 ${DEFINE_VAR2}$

		#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@

		#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@ # 此处定义了Tutorial_VERION_MINOR宏变量，在真实的代码中会使用@Tutorial_VERSION_MINOR@，而在cmake时，@Tutorial_VERSION_MINOR@会被替换掉0，对应第二条代码，之后，若是源代码中包含了这个头文件，就可以使用其中的宏变量了。注意，头文件最好和Makefile文件在同一个目录下。


- **tutorial.cpp ** 文件内容

	
		// 计算平方根的简单程序。
		#include <stdio.h>
		#include <stdlib.h>
		#include <math.h>
		#include <iostream>
		#include "Config.h"
		
		using namespace std;

		int main (int argc, char *argv[]) {

		cout << "Project Version: " << Tutorial_VERSION_MAJOR << "." << Tutorial_VERSION_MINOR << endl;
   
		#ifdef CMAKEDEFINE_VAR1
		   fprintf(stdout,"CMAKEDEFINE_VAR1 = %d\n", CMAKEDEFINE_VAR1);
		#endif 
		
		#ifdef CMAKEDEFINE_VAR2
		   fprintf(stdout,"CMAKEDEFINE_VAR2 = %d\n", CMAKEDEFINE_VAR2);
		#endif 
		
		#ifdef DEFINE_VAR1
		   fprintf(stdout,"DEFINE_VAR1 = %d\n", DEFINE_VAR1);
		#endif 
		
		#ifdef DEFINE_VAR2
		   fprintf(stdout,"DEFINE_VAR2 = %d\n", DEFINE_VAR2);
		#endif 
		 
		  return 0;
		}




### 2.1.2 `target_include_directories`
#### 2.1.2.1 语法

指定编译目标时要使用的包含目录或目标。目标必须由 add_executable() or add_library()创建。意味着在它们之后，创建该语句。

		target_include_directories(<target> [SYSTEM] [BEFORE]
		  <INTERFACE|PUBLIC|PRIVATE> [items1...]
		  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])


		PUBLIC关键字大致装置PRIVATE + INTERFACE.


		
		因此,假设您正在创建一个A使用某些Boost标头的库.你会这样做:
		
		target_include_directories(A PRIVATE ${Boost_INCLUDE_DIRS})如果你只在源文件(.cpp)或私有头文件(.h)中使用那些Boost头.
		target_include_directories(A INTERFACE ${Boost_INCLUDE_DIRS})如果您不在源文件中使用这些Boost标头(因此,不需要它们进行编译A).我实际上无法想到一个现实世界的例子.
		target_include_directories(A PUBLIC ${Boost_INCLUDE_DIRS})如果你在公共头文件中使用那些Boost头文件,这些头文件包含在某些A源文件中,并且也可能包含在A库的任何其他客户端中.


#### 2.1.2.2 代码示例

		add_executable(main main.cpp)
		
		target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}")



### 2.1.3 'set'

#### 2.1.3.1 语法

[参考](https://www.jianshu.com/p/c2c71d5a09e9)

		set(<variable> <value>... [PARENT_SCOPE]) #设置普通变量
		set(<variable> <value>... CACHE <type> <docstring> [FORCE]) #设置缓存条目
		set(ENV{<variable>} [<value>]) #设置环境变量

		set命令可以设置普通变量、缓存条目、环境变量三种变量的值，分别对应上述三种命令格式。set的值<value>...表示可以给变量设置0个或者多个值，当设置多个值时（大于2个），多个值会通过分号连接符连接成一个真实的值赋值给变量，当设置0个值时，实际上是把变量变为未设置状态，相当于调用unset命令。

	

设置变量，获取该变量的值，使用`@@`或者`$$` 

### 2.1.4 设置C++11和标准库头文件
		
		#specify the C++ standard
		set(CMAKE_CXX_STANDARD 11)
		set(CMAKE_CXX_STANDARD_REQUIRED True)

		We will need to explicitly state in the CMake code that it should use the correct flags. The easiest way to enable support for a specific C++ standard in CMake is by using the CMAKE_CXX_STANDARD variable. For this tutorial, set the CMAKE_CXX_STANDARD variable in the CMakeLists.txt file to 11 and CMAKE_CXX_STANDARD_REQUIRED to True. Make sure to add the CMAKE_CXX_STANDARD declarations above the call to add_executable.



### 2.1.5 系统宏

		"${PROJECT_BINARY_DIR}" # 表示可执行文件所在目录
		"${PROJECT_SOURCE_DIR}" # 表示源文件所在目录
