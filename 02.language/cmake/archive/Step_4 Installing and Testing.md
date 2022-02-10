# 1安装和测试

Now we can start adding install rules and testing support to our project.

## 1.1安装规则

- install

install用于指定在安装时运行的规则。它可以用来安装很多内容，可以包括目标二进制、动态库、静态库以及文件、目录、脚本等：

通过执行 `cmake --install . --config release`可以将可执行文件，安装到Linux系统中。这样就可以在任何目录下，都可以执行可执行文件啦

语法
		
		# 安装可执行文件和库文件，destination一般为lib和bin
		install(TARGETS <target>... [...])	

		# 安装文件，一般为头文件，destinations一般为include
		install({FILES | PROGRAMS} <file>... [...])

		install(DIRECTORY <dir>... [...])
		install(SCRIPT <file> [...])
		install(CODE <code> [...])
		install(EXPORT <export-name> [...])


the installation prefix can be overridden via the --prefix argument. For example:

		# 修改安装目录，从默认的/usr/local/改为/home/chris/installdir
		cmake --install . --prefix /home/chris/installdir

-  --prefix

		#执行结果
		chris@d:~/c++/demo/step4/build$ cmake --install . --prefix /home/chris/installdir/
		-- Install configuration: ""
		-- Installing: /home/chris/installdir/bin/Tutorial
		-- Installing: /home/chris/installdir/include/TutorialConfig.h
		-- Installing: /home/chris/installdir/lib/libMathFunctions.a
		-- Installing: /home/chris/installdir/include/mysqrt.h
		

举例：
		#MathFunctions/CMakeLists.txt
		# 将静态库MathFunctions安装到lib下
		install(TARGETS MathFunctions DESTINATION lib)

		# 将头文件MathFunctions.h安装到include下，即/usr/lcoal/include下
		install(FILES MathFunctions.h DESTINATION include)

		
		# CMakeLists.txt
		# 将Tutorial可执行文件安装到bin下，即usr/local/bin下
		install(TARGETS Tutorial DESTINATION bin)

		# 将静态库所需要的头文件安装到include下，即usr/local/include下
		install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
		  DESTINATION include
		  )
		
		
		chris@d:~/c++/demo/step4/build$ sudo cmake --install .
		-- Install configuration: ""
		-- Up-to-date: /usr/local/bin/Tutorial
		-- Up-to-date: /usr/local/include/TutorialConfig.h
		-- Up-to-date: /usr/local/lib/libMathFunctions.a
		CMake Error at MathFunctions/cmake_install.cmake:45 (file):
		  file INSTALL cannot find
		  "/home/chris/c++/demo/step4/MathFunctions/MathFunctions.h": No such file or
		  directory.
		Call Stack (most recent call first):
		  cmake_install.cmake:62 (include)

		从中可以看到执行sudo cmake --install .，就会将可执行文件、库文件已经头文件安装到系统中
		这里有个问题，就是没有找到/home/chris/c++/demo/step4/MathFunctions/MathFunctions.h这个头文件
		
		原因：本来就没有这个头文件，而是mysqrt.h，修改就可以

		

## 1.2 支持测试


cmake ../build   
cmake --build .   
make test #就开始执行测试用例了   

- `enable_testing()`:可以开启项目的测试功能。tips：一定要在根目录下的CMakeLists.txt中开启，不然执行make test时会报错。

随后项目的cmake配置文件中可以添加add_test指令

- `add_test()`

语法：

		add_test(NAME <name> COMMAND <command> [<arg>...]
			         [CONFIGURATIONS <config>...]
			         [WORKING_DIRECTORY <dir>]
			         [COMMAND_EXPAND_LISTS])








[参考 cmake命令之add_test和set_tests_properties使用案例](https://blog.csdn.net/weixin_42108533/article/details/119220713?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&utm_relevant_index=1)

[参考 Cmake add_testCmake add_test](https://blog.csdn.net/sun_ashe/article/details/104527591/)
[参考 【CMake】cmake的install指令](https://blog.csdn.net/qq_38410730/article/details/102837401)


- `set_tests_properties`: 设置若干个测试的属性值。

语法

		set_tests_properties(test1 [test2...] PROPERTIES prop1 value1 prop2 value2)
		test1：为测试函数名
		为若干个测试设置一组属性。若属性未被发现，CMake将会报告一个错误。
		这组属性包括：
			WILL_FAIL， 如果设置它为true，那将会把这个测试的“通过测试/测试失败”标志反转。
			PASS_REGULAR_EXPRESSION，如果它被设置，这个测试的输出将会被检测是否违背指定的正则表达式，并且至少要有一个正则表达式要匹配；否则测试将会失败。


举例

		# 源代码

				#include "TutorialConfig.h"
				#ifdef USE_MYMATH
					#include "mysqrt.h"
				#endif
				
				#include <iostream>
				#include <math.h>
				#include <string>
				
				using namespace std;
				
				
				int main(int argc, char* argv[])
				{
					
					if (argc < 2){
						cout << "Usage: " << argv[0] << " number";
						return 0;
					}
					
					long baseNum = stol(argv[1]);
					
					if (argc == 2)
						cout << "tips: " << argv[1] << endl;
					
				#ifdef USR_MYMATH
					cout << "use mymath: the squre of " << baseNum <<" is " << myquare(baseNum)) << endl;
				#else
					cout << "use system: the squre of " << baseNum <<" is " << pow(baseNum, 2) << endl;
				#endif
				
					cout << "Usage: " << argv[0] << " number" << endl;
					
					return 1;
				}


		# top CMakeLists.txt
			# 开始进行单元测试
			enable_testing()
			
			# does the application run
			add_test(NAME Runs COMMAND Tutorial 25)
			
			# does the usage message work? 测试用例的名字为Usage
			add_test(NAME Usage COMMAND Tutorial)
			set_tests_properties(Usage  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")
			
			# define a function to simplify adding tests
			# 第一参数是函数，后面是函数的参数
			function(do_test target arg result)
			
				  # 添加测试用例，分别指明测试用例的名字，使用的可执行文件和参数
				  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
				  
				  # 主要使用该方法，来确定测试结果，其中的PASS_REGULAR_EXPRESSION来验证cout输出时，是否有${result}字符串
				  set_tests_properties(Comp${arg}
				    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
				    )
			endfunction()
			
			# do a bunch of result based tests
			do_test(Tutorial 4 "4 is 16")
			do_test(Tutorial 9 "9 is 81")
			do_test(Tutorial 5 "5 is 25")
			do_test(Tutorial 7 "7 is 49")
			do_test(Tutorial 25 "25 is 625")
			do_test(Tutorial -25 "-25 is 625")
			do_test(Tutorial 0.0001 "0.0001 is 0.01")
	

		# 结果

			chris@d:~/c++/demo/step4/build$ make test
			Running tests...
			Test project /home/chris/c++/demo/step4/build
			    Start 1: Runs
			1/9 Test #1: Runs .............................***Failed    0.00 sec
			    Start 2: Usage
			2/9 Test #2: Usage ............................   Passed    0.00 sec
			    Start 3: Comp4
			3/9 Test #3: Comp4 ............................   Passed    0.00 sec
			    Start 4: Comp9
			4/9 Test #4: Comp9 ............................   Passed    0.00 sec
			    Start 5: Comp5
			5/9 Test #5: Comp5 ............................   Passed    0.00 sec
			    Start 6: Comp7
			6/9 Test #6: Comp7 ............................   Passed    0.00 sec
			    Start 7: Comp25
			7/9 Test #7: Comp25 ...........................   Passed    0.00 sec
			    Start 8: Comp-25
			8/9 Test #8: Comp-25 ..........................   Passed    0.00 sec
			    Start 9: Comp0.0001
			9/9 Test #9: Comp0.0001 .......................***Failed  Required regular expression not found. Regex=[0.0001 is 0.01
			]  0.00 sec
			
			78% tests passed, 2 tests failed out of 9
			
			Total Test time (real) =   0.03 sec
			
			The following tests FAILED:
			          1 - Runs (Failed)
			          9 - Comp0.0001 (Failed)
			Errors while running CTest
			make: *** [Makefile:130: test] Error 8



# 2参考
[参考0 Step 4: Installing and Testing](https://cmake.org/cmake/help/latest/guide/tutorial/Installing%20and%20Testing.html)

[参考1 CMake 系列 - 分模块编译&安装项目](https://www.cnblogs.com/standardzero/p/10793746.html)

[参考2 cmake 2 指定头文件目录](https://sqlpy.com/blogs/212533219)

[参考3【CMake】cmake的install指令](https://blog.csdn.net/qq_38410730/article/details/102837401)

[参考4 CMake教程－Step4（调试和安装）](https://blog.csdn.net/yufm/article/details/107692194?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_aa&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_aa&utm_relevant_index=1)

[参考5 CMake 手册详解（二十二）](https://www.cnblogs.com/coderfenghc/archive/2012/10/20/2712806.html)