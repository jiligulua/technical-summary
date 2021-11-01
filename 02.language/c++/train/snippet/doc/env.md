# Windows

在Windows下，vscode要调试仅支持Cygwin和Mingw(MinimalistGNUforWindows)，这里使用Mingw。

[Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)

[C++各版本与各编译器版本之间的关系](https://en.cppreference.com/w/cpp/compiler_support)


## vscode操作

### 重要的

1. 设定源代码编译任务

输入：Ctrl + Shift + P
搜索：Tasks: Config Default Build Task

tasks.json指定源代码编译任务


2. 设定调试任务

launch.json指定调试任务


### 次要的
1. 切换语言

    1.Ctrl+Shift+P 打开命令
    2.搜索 Configure Display Language




