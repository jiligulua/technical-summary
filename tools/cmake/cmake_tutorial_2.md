# 0 CMake模块化项目管理指南（C/C++）

如何基于CMake的C/C++项目，优雅地模块化地组织大量源代码？
 
# 1 文件/目录组织规范 

## 1.1 推荐的目录组织方式

1. 目录组织格式
-	项目名/include/项目名/模块名.h 再套一层是为了避免与系统include中的头文件发生冲突
-	项目名/src/模块名.cpp

2. CMakeLists.txt中写
-	target_include_directories(项目名 PUBLIC include) 将目录include添加到头文件搜索目录中
include_directories已废弃，它是给所有的项目都赋予了一个目录搜索目录，这样很不优雅，不管有没有用。所以最好指定项目名字，改为带target的指令

3. 源码文件中写
-	#include <项目名/模块名.h>
-	项目名::函数名
函数也添加项目名的命名空间

4. 头文件中写
-	#pragma once
-	namespace 项目名 {
-	void 函数名();
-	}

5. 实现文件中写
-	#include <项目名/模块名.h>
-	namespace 项目名 {
-	void 函数名() { 函数实现 }
-	}

## 1.2 划分子项目

大型项目，往往会划分为几个子目录。即使只有一个子项目，也要先创建一个子目录，方便以后追加新的子项目。一般来说一个是可执行文件（main），其它的为库文件，而实际的代码都是在库文件里面，具体做功能逻辑。而在可执行文件里主要是和用户交互，前台接待员。分离的好处就是，库文件可以被其它可执行文件作为库文件而调用。若是可执行文件，那就不好被其它可执行文件调用了。

思想：实现全在库里，可执行文件只是入口

## 1.3 根项目的CMakeLists.txt配置

	.
	|——biology
	|  |——CMakeLists.txt	
	|  |——include
	|  |   |——biology
	|  |	 |——Animal.h
	|  |——src
	|	   |——Animal.cpp
	|—— cmake
	|
	|——CMakeLists.txt
	|——pybmain
    	  |—— CMakeLists.txt
    	  |—— include
    	  |     |——pybmain
    	  |			|—— myutils.h
    	  |
    	  |—— src
    		    |—— main.cpp
    
这样写的好处就是，最外层设置全局的配置，如CXX版本，编译类型，项目名，版本号等，而子项目只需关心自己的事情，只是创将biology这个静态对象，并通过GLOB_RECURSE为它批量添加所有位于src和include下的源码和头文件。根项目的CMakeLists.txt负责处理全局有效的设定，子项目仅考虑子项目的设定，如他的头文件，要链接的库等。这样就解耦了。

	top:
	cmake_minimum_required(VERSION 3.18)

	if (NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE Release)
	endif()

	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRE ON)
	set(CMAKE_CXX_EXTENSIONS OFF)
		
	project(CppCMakeDemo LANGUAGES CXX)

	add_subdirectory(pybmain)
	add_subdirectory(biology)

---


	biology:
	file(GLOB_RECURSE src CONFIGURE_DEPENDS src/*.cpp include/*.h)
	add_library(biology STATIC ${src})
	target_link_directories(biology PUBLIC include)



- GLOB和GLOB_RECURSE的区别？
GLOB只能识别一级目录，而后者可以识别多级目录


		file(GLOB myvar CONFIGURE_DEPENDS src/*.cpp)
		file(GLOB_RECURSE myvar CONFIGURE_DEPENDS src/*.cpp)

- 加CONFIGURE_DEPENDS
在每次cmake --build时（真正构建时）会自动检测CMakeLists.txt是否有更新，若有更新，CMake会自动帮我重新运行cmake -B build更新myvar变量。就不会出现“undefined symbol”的问题，也不用删build大法。

## 1.4 子项目的头文件

这里给biology设置了头文件搜索路径include，因为子项目的CMakeLists.txt里指定的路径都是相对路径，所以这里指定的include实际上是：根/biology/include。注意用了PUBLIC修饰符，是为了让链接biology的pybmain也能够共享 **根/biology/include**这个头文件搜索路径。

## 1.5 子项目的源文件

为什么还要加include中的头文件呢？头文件又不参与编译，为啥呢？为了头文件也能被纳入VS的项目资源浏览器，方便编译。

## 1.6 头文件和源文件的一一对应关系	
通常每个头文件都有一个对应的源文件，两个文件名字相同（方便理解也方便IDE跳转），只是后缀不一样。如果是一个类，则文件名和类名相同，方便查找。头文件中包含函数和类的声明，源文件则包含它们的实现。

## 1.7 只有头文件，没有源文件的情况
通常每个头文件都由一个对应的源文件，若是头文件中包含函数的声明和实现，这个时候，头文件中的函数需要加上static（防止它重复定义）或inline关键字。C引入头文件是暴力复制。注意类可以不加static。


	mytutils.h
	#pragma once

	#include <ostream>

	namespace biology {
	
	struct Animal {
	  virtual void speak(std::ostream& os) const = 0;
	  virtual ~Animal() = default;
	};

	}


## 1.8 每新增一个功能模块（类），都需要创建两个文件 
## 1.9 一个模块依赖其它模块，应导入它的头文件
头文件采用<项目名/模块名.h>, 不要用“模块名.h”，这种表示当前路径的一种相对路径，避免模块名也系统已有头文件冲突。
""的头文件，是指找当前目录，而 **<>** 则是从CMakeLists.txt中搜索头文件目录。

因为是按照规范来编程，所以需要尖括号。有CMakeLists.txt指定。

## 1.10 前向声明
没有用到类的成员函数或变量，只用了指针，就用前向声明就可以了。好处：加快编译速度，防止循环引用。

## 1.11以项目名为命名空间，避免符号冲突。
C++都是全局可见的，若是由冲突，由于类符号都具有weak属性，链接器会随机选择一个覆盖掉，非常危险。

## 1.12 依赖另一个子项目，则需要链接它

- 让pybmain链接上biology：target_link_libraries(pybmain PUBLIC biology)
- 由于PUBLIC属性具有传染性，根/biology/include现在也加入pybmain的头文件搜索路径了，因此pybmain里可以#include到biology的头文件 
- 同理，若由一个target_link_libraries(zxxpig PUBLIC pybmain)那么zxxpig也有了pybmain和biology的所有头文件搜索路径了

## 1.13 CMake也有include功能


	extern只有一种情况，就是声明一个变量要用extern int a; 而定义一个变量要用int a; 本来函数也需要加extern，因为函数定义后面有花括号，而声明后面是;，就可以省略了。

	extern "C" int f(); 和原来的extern没有任何关系。两个关键字固定搭配，表示是用C编译器编译的。

通常会把cmake脚本文件放在顶层目录的cmake目录中,在该目录添加相应的宏和函数。就是说我不想把这部分内容放入等层CMakeLists.txt中，嫌这个东西厌烦。这个时候，我只要在顶层CMakeLists.txt中添加

	set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PAHT}") # CMAKE_CURRENT_LIST_DIR表示当前CMakeLists.txt所在目录
	include(MyUsefulFuncs) # 不用加后缀.cmake

就可以了，就会把相应的cmake脚本导入到这里，前提是把目录加到CMAKE_MODULE_PATH这个cmake环境变量中。
一般来说在.cmake中写函数，变量和宏，都可以的。

## 1.14 macro和function的区别

- macro相当于直接把代码粘贴过去，直接访问调用者的作用域。这里写的相对路径include和src，是基于调用者所在的路径

- function则是会创建一个闭包，优先访问定义者的作用域。这里写的相对路径include和src，则是基于定义者所在路径。


## 1.15 include和add_subdirectory的区别

include是直接复制代码过来，而function(如add_subdirectory）则是基于定义者所在路径，优先访问定义者的作用域。这里需要set(key val PARENT_SCOPE)才能修改外面的变量


# 2 第三方库/依赖项配置（最重要的部分）

用find_package寻找系统中安装的第三方库并链接它们

- find_package命令
常见参数列表一览

	find_package(<PackageName> [version] [EXACT] [QUIET] [CONFIG] [MODULE] [REQUIRED] 
			[[COMPONENTS] [components...]]
			[OPTIONAL_COMPONENTS componets...]
			)

	find_package(OpenCV) 找不到该包不报错，可通过${OpenCV_FOUND}查询是否找到
	find_package(OpenCV QUIET)  找不到不报错也不打印
	find_package(OpenCV REQUIRED)  找不到报错，并停止cmake进程
	find_package(OpenCV REQUIRED COMPONENTS core videoio)  找不到报错，若找到该包，但没有其中的组件，也报错
	find_package(OpenCV REQUIRED OPTIONAL_COMPONETS core videoio) 包找不到就报错，而组件找不到不报错，可通过${OpenCV_core_FOUND}查询是否找到core组件

- find_package是在找什么呢？

find_package(OpneCV)实践上是在找一个名为OpenCVConfig.cmake的文件（也兼容历史包名OpenCV-config.cmake）,即形如 **包名+Config.cmake**的文件，称之为包配置文件。如同理如Qt5，放在/usr/lib/cmake/Qt5/Qt5Config.cmake下,而实际的动态库文件位于/usr/lib/libQt5Core.so。都是固定的命名格式和路径。

这个包配置文件，可以找到该包的各种组件。效果从自己所在位置开始查找，是一种相对路径往上找的。Qt5需要指定组件，其它的若OpenCV不指明组件的话，会包含所有的组件。

- find_package说是找“包（package）”，到底是找什么呢？
并不是直接去找具体的 **动态库文件**和 **头文件**（如：libQt5Core.so），而是去找 **包配置文件**（如Qt5Config.cmake），这个配置文件里包含了包的具体信息，包括动态库文件的位置，头文件的目录，链接时需要开启的编译选项等。而且某些库都具有多个动态库，因此CMake要求所有第三方库作者统一包装成一个Qt5Config.cmake文件包含所有相关信息，比我单独一个个去找动态库文件要灵活的多。

包配置文件由第三方库的作者（Qt的开发团队）提供，在这个库安装时（Qt的安装程序或apt install等）会自动放在/usr/lib/cmake/XXXX/XXXXConfig.cmake这个路径（其中XXXX是包名），供CMake用户找到并了解该包的具体信息。

/usr/lib/cmake这个位置是CMake和第三方作者 **约定俗成**的，由第三方库的安装程序负责把包配置文件放到这里。如果第三方库的作者比较懒，没提供CMake支持（由安装程序提供XXXXConfig.cmake），那么得用另外的一套方法（FindXXXX.cmake）

