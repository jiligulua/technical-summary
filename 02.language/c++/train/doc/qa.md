# vscode锦集 #

##  Q&A

Q："终端将被任务重用，按任意键关闭"  
A：在task.json中，添加：  
	
	“presentation”: {
		"panel": "shared", // 这里shared表示共享，改成new之后每个进程创建新的端口
	}
 
Q: Failed to connect to github.com port 443: Timed out  
A: 本地设置代理，取消代理重新git clone，就可以获得代码了  

Q：Ubuntu下如何隐藏dash   
A：  
sudo apt update
sudo apt install gnome-tweaks
sudo apt install gnome-shell-extension-dash-to-panel
注销
gnome-tweaks
extension/Dash to panel 点击右侧按钮，完成隐藏或显示

Q：Ubuntu下如何安装vscode  
A：  
vscode官网上下载vscode，下载code_1.58.0-1625728071_amd64.deb
sudo dpkg -i code_1.58.0-1625728071_amd64.deb (-i表示本地安装)
如果安装过程中出现问题,可以先使用命令:
sudo apt-get update
更新后再执行上面的命令.

Q：如何查看安装的应用并启动应用   
A：点击左上角的Activities，然后就可以查看应用了  

Q：linux中whereis、which、find、location的区别和用法  
A：  
find：find <指定目录> <指定条件> <指定动作> find . -name "my*" -ls(列出详细信息)
locate：是find -name的另一种写法，但比后者快，是搜索数据库。每天更新一次；
whereis：只能用于程序名的搜索，而且只搜索二进制文件（参数-b），man说明文件（参数-m）和源代码文件（参数-s）。如果省略参数，则返回所有信息。
which：在PATH变量指定的路径中，搜索某个系统命令的位置，并且返回第一个搜索结果。也就说使用which命令，可以看到某一个系统命令是否存在，以及执行的到底是哪个位置的命令。

Q: vscode扩展宿主意外终止  
A：多个扩展发生冲突，禁用即可  

Q: gun++11与c++11的区别  
A：  
-std=c++11，支持C++11标准；
-std=gnu++11，支持C++11标准和GNU扩展特性；

1、sudo add-apt-repository ppa:ubuntu-desktop/ubuntu-make
2、sudo apt-get update
3、sudo apt-get install ubuntu-make
4、umake ide visual-studio-code

Q:vscode环境变量有哪些  
A:

	${workspaceFolder} :表示当前workspace文件夹路径，也即/home/Coding/Test
	${workspaceRootFolderName}:表示workspace的文件夹名，也即Test
	
	${file}:文件自身的绝对路径，也即/home/Coding/Test/.vscode/tasks.json
	${relativeFile}:文件在workspace中的路径，也即.vscode/tasks.json
	
	${fileBasenameNoExtension}:当前文件的文件名，不带后缀，也即tasks
	${fileBasename}:当前文件的文件名，tasks.json
	
	${fileDirname}:文件所在的文件夹路径，也即/home/Coding/Test/.vscode
	${fileExtname}:当前文件的后缀，也即.json
	
	${lineNumber}:当前文件光标所在的行号
	
	${env:PATH}:系统中的环境变量



## VSCode配置文件说明

### Windows配置

[参考链接](https://code.visualstudio.com/docs/cpp/config-msvc)


- tasks.json (build instructions)
- launch.json (debugger settings)
- c_cpp_properties.json (compiler path and IntelliSense settings)

## task

- task：可以设置多个，以便指定

- "command": 指定由谁来编译代码，如：g++.exe，需要填写全路径
- "args":指定了编译源代码的命令行，如：

		[
		  "-g", # 表示gdb调试
                "${workspaceFolder}/src/*.cpp", # 需明确指定文件类型
                "-o", # 表示g++的输出
                "${workspaceFolder}/bin/main.exe" # 表示输出内容
		]
- "presentation": 
	
		"panel": "shared", // 这里shared表示共享，
						  // 改成new之后每个进程创建新的端口

## c\_cpp\_properties

在哪个文件里设置includePath？

默认在用户主目录文件夹下的.vscode里面；

还有一种你自己设置了工作区的，在工作区文件夹下的.vscode；文件名是c_cpp_properties.json ,因为设置的是C和C++的include文件。includePath里面的项的写法是：includePath:[“绝对路径一”,“绝对路径二”,“绝对路径三”]






