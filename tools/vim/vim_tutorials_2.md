使用小彭老师的vimrc和vim，git为：https://github.com/archibate/vimrc/releases

F7:运行，下面出现终端，按Ctrl+t就可以退出终端，重复执行就打开
Ctrl+\ Ctrl+n : 终端编程普通模式，可以复制然后粘贴到代码中
Ctrl+r：退出普通模式

同样适用于python，也可以F7运行，若只是运行而不编译，可以直接使用:AsyncTask file-run
:AsyncTasks file-build file-run 可以连续执行多个命令

F7:单文件构建
F5:多文件构建

可在本地创将 .tasks 
[+]
build_generator=Unix Makefiles   # 表示本地文件使用该编译工具

