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
		
		project(Tutorial)
		
		message(STATUS "PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})
		message(STATUS "PROJECT_BINARY_DIR " ${PROJECT_BINARY_DIR})
		
		set(CMAKEDEFINE_VAR1 1)
		set(CMAKEDEFINE_VAR2 0)
		
		set(DEFINE_VAR1 1)
		set(DEFINE_VAR2 0)
		
		
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
		#define DEFINE_VAR2 ${DEFINE_VAR2}


- **tutorial.cpp ** 文件内容

	
		// 计算平方根的简单程序。
		#include <stdio.h>
		#include <stdlib.h>
		#include <math.h>
		#include "Config.h"
		
		int main (int argc, char *argv[]) {
		  
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

	-



