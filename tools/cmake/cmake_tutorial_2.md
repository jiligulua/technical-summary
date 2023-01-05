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

---
	
	pybmain:
	file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
	add_executable(pybmain ${src})
	target_link_directories(pybmain PUBLIC include)

	target_link_libraries(pybmain PUBLIC biology)


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


	extern只有一种情况，就是声明一个变量要用extern int a; 
	而定义一个变量要用int a; 本来函数也需要加extern，因为函数定义后面有花括号，而声明后面是;，
	就可以省略了。

	extern "C" int f(); 和原来的extern没有任何关系。两个关键字固定搭配，表示是用C编译器编译的。

通常会把cmake脚本文件放在顶层目录的cmake目录中,在该目录添加相应的宏和函数。就是说我不想把这部分内容放入等层CMakeLists.txt中，嫌这个东西厌烦。这个时候，我只要在顶层CMakeLists.txt中添加

	# CMAKE_CURRENT_LIST_DIR表示当前CMakeLists.txt所在目录
	set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PAHT}") 
	include(MyUsefulFuncs) # 不用加后缀.cmake


	macro (my_add_target name type)
	    # 用法： my_add_target(pybmain EXECUTABLE)
	    file(GLOB_RECURSE src CONFIGURE_DEPENDS src/*.cpp src/*.h)
	    if ("${type}" MATCHES "EXECUTABLE")
	        add_executable(${name} ${src})
	    else()
	        add_library(${name} ${type} ${src})
	    endif()
	
	    target_include_directories(${name} PUBLIC include)
	endmacro()
	
	set(SOME_USEFUL_GLOBAL_VAR ON)
	set(ANOTHER_USEFUL_GLOBAL_VAR OFF)



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

	find_package(OpenCV) 找不到该包不报错，可通过\${OpenCV_FOUND}查询是否找到  
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

- 安装在非标准路径的库
一般通过命令行指定：-DQt5_DIR="C:/Program Files/Qt5.12.1/lib/cmake/Qt5", 在该目录下有Qt5Config.cmake文件，这样就不用修改CMakeLists.txt


		举例：在Windows系统，Qt5，三种方法
		1. cmake -B build -DQt5_DIR="D:/Qt5.12.1/msvc2017/lib/cmake/Qt5"
		2. 设置环境变量
		3. set(Qt5_DIR "/opt/Qt5.2.1/lib/cmake/Qt5") # 一定放在最前面

	举例：在Linuxe  
	1.(推荐该方法，build有记忆，除非删除了build，才要重新指定) cmake -B build -DQt5_DIR="/opt/Qt5.12.1/lib/cmake/Qt5", (第二次就不用指定了，出如rm -rf build之后，才需要指定)  
	2. 全局使用，修改~/.bashrc文件添加环境变量
	export Qt5_DIR="/opt/Qt5.12.1/lib/cmake/Qt5" 然后重启终端，以后每次构建任何项目，find_package都能自动找到这个路径的Qt5包  
	3. 单项目生效, 在CMakeLists.txt最开头写一行
	set(Qt5_DIR "/opt/Qt5.12.1/lib/cmake/Qt5") 


- 科普：亲Unix软件从源码安装的通用套路

	Makefile构建系统  
	./configure --prefix=/usr --with-some-options # 生成Makefile（这个configure脚本由Autoconf生成）--prefix=用于指定安装目录    
	make -j 8 # 8核心编译，生成libtest.so  
	sudo make install # 安装，拷贝到/usr/lib/libtest.so
	
	CMake构建系统:  
	cmake -B build -DCMAKE_INSTALL_PREFIX=/usr -DWITH_SOME_OPTIONS=ON # 生成Makefile  
	cmake --build build --parallel 8 # 8核心编译，生成libtest.so  
	sudo cmake --build build --target install # 安装，拷贝到/usr/lib/libtest.so

	注：如果-DCMAKE_INSTALL_PREFIX=/usr/local则会拷贝到/usr/local/lib/libtest.so


- 如果第三方发懒，每提供Config文件怎么办？

	绝大多数常用C++库都提供了CMake支持（即使它们本身不一定是CMake构建）  
	/usr/lib/cmake/Boost-1.80.0/BoostConfig.cmake   
	/usr/lib/cmake/opencv4/OpenCVConfig.cmake  
	/usr/lib/cmake/Qt5/Qt5Config.cmake  

这些Config文件都是由第三方负责安装到/usr/lib/cmake下

如Python、CUDA、Jemalloc是热门库，但不提供Config文件，那么cmake发明了Find文件（FindXXX.cmake）来主动支持这些库，CMake自带的包搜索文件：  

	/usr/share/cmake/Modules/FindCUDAToolkit.cmake  
	/usr/share/cmake/Modules/FindPython.cmake  

若是冷门的库，没有Config，cmake也没有提供Find，就要自己提供包搜索文件了！别但心，GitHub上由很多志士已经写过了对应的包搜索伪呢间，搜一下FindXXX.cmake就能够找到。

	如FindJemalloc.cmake，是Google还是Facebook搞出来的内存分配器。
	在GitHub上，若：FindCppUnit.cmake, FindLog4cplus.cmake, FindJemalloc.cmake

CMAKE_MODULE_PATH不仅用于cmake（下载的FindXXX.cmake可以在放在该目录下），还可以用于find_package。 $/usr/share/cmake/Modules/由很多.cmake，所以

	include(CTest) # 就会在/usr/share/cmake/Modules下去查找CTest.cmake文件

### 举例： FindJemalloc.cmake  
	
**Config文件**通常风格统一，都是XXX::xxx格式，但是 **Find文件**，特别是网上志士写的文件，风格千差万别，很多是古代CMake用法，如： ${xxx_LIBRARIES}，具体细节打开FindXXX.cmake文件查看，都由注解，下载后放在cmake目录下，在CMakeLists.txt里最上面写一行：

	set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")
	这样find_package(XXX)就会用下载的这个FindXXX.cmake去找包了。

### 现代vs古代：用法上完全不同！

OpenCVCofnig.cmake（现代）

	add_executable(main main.cpp)

	find_package(OpenCV REQUIRED COMPONENTS core videoio)
	target_link_libraries(main PUBLIC OpenCV::core)
	target_link_libraries(main PUBLIC OpenCV::videoio)


FindCURL.cmake(古代)

	find_pakcage(CURL)

	add_executalbe(curltest curltest.cc)
	if (CURL_FOUND)
		target_include_directories(clib PRIVATE ${CURL_INCLUDE_DIR})
		target_link_libraries(curltest ${CURL_LIBRARY})
	else(CURL_FOUND)
		message(FATAL_ERROR "CURL library not found")
	endif(CURL_FOUND)

不管是Find类还是Config类，要打开相应的cmake文件看注释，才能明白是古代还是现代风格
古代CMake的命名规范高度不统一，有的是${XXX_LIBRARIES} or ${XXX_LIBRARY},要看注释才能确定具体是什么命名

现代CMake统一用 **包名::组件名**格式，具体组件名还是要查看cmake文件中的注释才能确定，如：CURL::libcurl OpenCV::core Qt5::core TBB::tbb等

### 现代和古代区别总结：

古代（仅用于伺候很老的库）

		find_package(XXX)
		if (NOT XXX_FOUND)
			message(FATAL_ERROR "XXX not found")
		endif()
		target_include_directories(youapp ${XXX_INCLUDE_DIRS})
		target_link_libraries(youapp ${XXX_LIBRARIES})

现代（小彭老师推荐）

		find_package(XXX REQUIRED COMPONENTS xxx)
		target_link_libraries(yourapp XXX::xxx)


大多数能同时兼容现代和古代

python只是调用libpython的入口，curl也只是调用libcurl的入口，现代程序都是这样，一个可执行程序，一个lib。

### 官方文档：find_package的两种模式

一种为Module模块模式，find_package(TBB MODULE REQUIRED)只会去寻找FindTBB.cmake，搜索路径为：
	${CMAKE_MODULE_PATH} (默认为/usr/share/cmake/Modules)

另一种为Config模式，find_package(TBB CONFIG REQUIRED)只会去寻找TBBConfig.cmake，搜索路径为：
	${CMAKE_PREFIX_PATH}/lib/cmake/TBB(默认为/usr/lib/cmake/TBB)
	${TBB_DIR}或$ENV{TBB_DIR} 


find_package(TBB REQUIRED) 不指定则两者都会尝试，先尝试FindTBB.cmake,再尝试TBBConfig.cmake。按历史出现顺训查找。

### 关于vcpkg的坑（不用vcpkg的同学可跳过这段）
有些懒惰的第三方库（如：Jemalloc）不通过Config文件，需要我们手写（或抄别人开源项目的）那个Find文件，用起来不方便。但vcpkg为所有第三方库都配置了一个Config文件方便我们find_package导入。所以，用vcpkg时，优先使用find_package(XXX **CONFIG** REQUIRED)避免被CMake自带的Find文件误导找到别的地方（而非vcpkg安装的那个）的库

另外需要注意vcpkg需要的CMAKE_TOOLCHAIN_FILE如果用set设置，必须在project命令前面，并且修改这个变量后，并且修改这个变量后要删除build目录重新cmake -B build一遍生效（否则在旧的环境里找，找不到vcpkg装的库）。如set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/buildsystemtest.cmake" CACHE FORCE) 是一个缓存变量不是普通变量，提供强制FORCE表示强制生效


### 科普：语义版本号（semantic versioning）系统
软件行业记录版本迭代普通采用一套所谓的 **语义版本号**系统，英文为semer  
格式:<major>.<minor>.<patch>，如：1.2.0 0.6.8 18.11.0  
major：主版本号，出现功能重大变更，以至于和旧API不兼容的时候会增加该号  
minor：次版本号，功能由所变更或增加，但依然和旧API兼容时会增加该号  
patch：补丁版本号，功能没有改变，只是修复一些bug就重新发布时会增加该号。  
CMake支持最多4个点分开的版本号：<major>.<minor>.<patch>.<tweak>。如果只写了0.6.8会自动把多余的tweak默认为0，也就是说：0.6.8==0.6.8.0 1.2 == 1.2.0 == 1.2.0。

比较版本号时，可以用


	if (${XXX_VERSION} VERSION_LESS 3.1.0)判断大小 
	if (CMAKE_VERSION VERSION_GRETAER_EQUAL 3.1.0)判断大小 >=, <=, >, <, ==等

### 小技巧：很多变量都要set到project前面

### find_package命令指定版本

	find_package(OpenCV REQUIRED) 不限版本，事后可通过${OpenCV_VERSION}查询找版本
	find_package(OpenCV 2.0.1 REQUIRED) >= 2.0.1
	find_package(OpenCV 2.0.1 EXACT REQUIRED) == 2.0.1
	find_package(OpenCV 2 REQUIRED)  # 以下没有写全，默认部分都为0，以下三者等价
	find_package(OpenCV 2.0 REQUIRED) 
	find_package(OpenCV 2.0.0 REQUIRED) 


## 总结
1. 安装TBB（比如使用这种方式，安装和使用boost库，练练手）

	源代码安装方式
	cd tbb
	./configure --prefix=/opt/tbbinstalldir
	make -j 8
	sudo make install


2. 在项目里使用TBB：

	cd yourapp
	cmake -B build -DTBB_DIR=/opt/tbbinstalldir/lib/cmake/TBB
	cmake --build build --parallel 8

3. CMakeLists.txt这样写

	project(yourapp)
	add_executable(yourapp yourmain.cpp)
	find_package(TBB CONFIG REQUIRED COMPONENTS tbb)
	target_link_libraries(yourapp PUBLIC TBB::tbb)


4. 古代CMake常见问题
第三方库太老了，它使用的是古代cmake。

		1. target_link_libraries(yourapp ${XXX_LIBRARIES})
		2. target_include_directories(yourapp ${XXX_INCLUDE_DIRS})

Q：我明明链接了XXX库，编译时报错“找不到头文件XXX.h”怎么办？  
A：漏了上面的2  
Q：我明明编译都通过了，链接却报错“undefined symbol：XXXfunc”怎么办？  
A：漏了上面的1

打印检查一下这两个变量是不是空：message("!!!! ${XXX_INCLUDE_DIRS}")，若空说明变量名打错了，CMake特色就是 **找不到变量不报错，而是视为空字符串**。这时去看一下 **FindXXX.cmake**里的注释（那就是文档），到底是什么名字。而用XXX::yyy找不到，就会报错。

5. 少见的add_subdirectory邪教

大部分第三方库都需要提前安装好，然后再find_package找到他，然后才能链接。也有少数第三方库为了方便，还支持作为子项目加到你的项目中来，这样就不需要::语法

	标准方法：
	find_package(spdlog REQUIRED)
	target_link_libraries(yourapp PUBLIC spdlog::spdlog)

	邪教方法:
	add_subdirectory(spdlog) # 需要下载好他们的源码放到你的根目录下
	target_link_libraries(yourapp PUBLIC spdlog)

- 小技巧：git clone ... --depth=1 会加快克隆，只获取最近的commit，不加的话会把所有的commit都下载下来


6. 实战：

	git clone ...  --depth=1  
	cmake -B build -DCMAKE_INSTALL_PREFIX=/tmp/test(出于测试目的，安装在该目录下，一关机就没有啦) 
	cmake --build build --parallel 8（有几个核就写几，速度快） 真正的build（vcpkg很吃网络）

	osg代码分析：  

		如果定义了微软的编译，或这模拟Linxu的CYGWIN或者MINGW32	  
		#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__)   
		  #if defined(OSGSIM_LIBRARY)  // 伺候微软，制作dll时，需要dllexport用来导出使用  
		  // target_compile_definitions(osgSim __PRIVATE -DOSGSIM_LIBRARY)   这样来定义
		  // PRIVATE：表示osgSim本身使用，不传播给别人
		  // target_link_libraries(yourapp PUBLIC osgSim) 
	  	  // 这个时候yourapp链接osgSim时，没有OSGSIM_LIBRARY这个宏     
		  #   define OSGSIM_EXPORT __declspec(dllexport) 
		  		// 编译osgSim使用这个定义，给自己模块用  
	    # else  // 使用dll的exe。当exe需要使用这个dll时，就需要dllimport，表示使用dll文件
		  #   define OSGSIM_EXPORT __declspec(dllimport)  
		  		// yourapp使用这个定义，给别人模块用。这就是宏的作用
	      # endif
		  # else
		  #  define OSGSIM_EXPORT // gcc编译器，就是空的，什么都没有
	     # endif


	导入编译好的库示例：  
	find_package(TBB CONFIG REQUIRED COMPONENTS tbb tbbmalloc tbbmalloc_proxy)  
	target_link_libraries(main PUBLIC TBB::tbb TBB::tbbmalloc TBB::	tbbmalloc_proxy)  
	
	这样源码中就可以使用了，如下：  
	#include <tbb/parallel_for.h>  
	#include <tbb/tbbmalloc_proxy.h>  
	#include <tbb/tbb_allocator.h>  

	std::vector<int, tbb::tbb_allocator<int>> v;  
	v.resize(100);

	// 打印0到100
	tbb::parallel_for(0, 100, [&](int i) {  
		printf("%d\n", i)  
		});  



# 3 实践
## 3.1 编译、引入和使用tbb库

## 3.2 编译、引入和使用boost库

## 3.3 通过cmake使用dbg调试源码

## 3.4 core dump能够跟踪出错处

## 3.5 完成归并代码



































