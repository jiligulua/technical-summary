在命令模式下，使用数字+hjkl,实现跳跃o

:set mouse=a,可实现在命令模式下使用鼠标。

命令模式、输入模式，普通模式

可使用:w 文件名，可以保存到指定文件，保存并退出，wqa,还可以使用shift + zz来退出，会保存之后退出。还可以使用shift+zq，不保存的退出。

启动vim中，自动执行命令，点开头的文件，是隐藏文件。ls -a出现带点文件。

.vimrc自启动前，都会先执行里面的命令。
:set mouse=a 开启鼠标
:set nu	开启行号
:set nonu 关闭行号

0：行首 ^:行首不包含空格  $:行尾， 3+：下3行，3-：上3行
3$, 下3行的行尾 

## 单词跳
w:一次跳一个单词，还可以加上数字，
Shift+w：无视特殊符号，包括逗号

b就是回跳,若想无视标点符号，就用Shift+b。Shift上档，跳得更起劲。

e：跳到下个单词的末尾，Shift+e：

## 修改单词
先按下b，达到开始处，再按下v，再按下e，就可以选择整个单词了。若想删除，就选中x就是删除。或者dw，而v可以让我们可以看到选中。

也可以数字+x来删除，也可以用ved和vex，等价的。

在普通模式下x和d的区别是：x直接删除，而d等待进一步的操作，如：de,dw。

还可以db，最后一个单词不删除，还可以d$等价于shift+d。大写的D，删除当前到尾的内容。

cw：当前单词删除的时候，立即进入插入模式，方便！== dwi
或者当前单词选中后，按c，也是一样的。

c2w:修改2个单词
cW:修改符号在内的一串字符.
cw: change word

ciw：可以在单词中的任意位置，修改该单词

## 跳转行
66gg:跳转到66行

## 查找
/chrome : 查找chrome
?chrome： 自动往上找
n和N：往下往上。
/和？相反，n和N也是相反，通常用/而不用？。

#：停在某一个单词上，进行向上查找
\*：停在某一个单词上，进行向下查找
以上两个都是高亮光标所在的单词，之后按n或N进行向下或向上，查找。
也可以一直按住#或*号，进行上下跳转

查找第一个b，可以用fb再加；可以自动跳到下一个。还可以cfb，可以直接改掉当前到fb的内容。这样可以指定当前光标到指定字符之间的内容都改掉。好方便阿。

cf=修改等号本身：forward to 当前字符
ct=不修改等号本身：to 到这个字符前面

## 插入

I:自动到行首插入，这个行首不带空格。这样就可以添加注释符号了
i a 插入，还可以用A后面插入。insert和append

## 宏
什么是宏，就是录制一个操作，之后，就可以用这个宏来替代这个操作。
如：qu：这个时候，就往u里面录入宏，xj，删除一个字符后向下移动一位，之后再输入q，标识宏录制完成。之后，输入@u，就可以重复执行，就是执行寄存器u里面的操作。比如：4@u，就执行4次，也可以用4@@表示上一次执行的宏。

@@:表示上一次刚刚执行过的宏

推荐使用：按v之后，选中内容，再按：norm 0x，就可以去掉选中内容的第一列的字符。

eg：v 选行:norm 0x
v 选行 :norm I# 表示在首行加入#
如C语言注释可以是：norm I// 回车，就加上注释符号了。

norm之前还可以输入行号，如对23,34norm I//表示对23行到34行做注释
而`'<,'>`表示选中的范围

norm指令是编辑器命令，可以做多行统一联合处理多个指令。

大写的V：按行选中
而小写的v：从选中开始

## 翻页
标准的滚页是Ctrl+d和Ctrl+u，就是page down和page up
ctrl+y 和 ctrl+e只滚动一行，这个是光标不动
都是在普通模式，输入模式那是输入用的

## 替换
`:s/debian/ubuntu/g`  只是一行
也可以在前面选择行或返回，也可以用v选中，或用%表示对每一行替换
输入\可以转义

o:向下输入，若是3o，表示向下输入，推出之后，就有3行相同的输入，这个对于重复输入很有帮助。

同理，对于i和a，都可以在前面指定数字，当输入内容之后退出，就会出现循环的指定次数。确实很收益。

d$和c$,后面删除并插入，可以用大写的D和C代替前面的命令


vi<选中尖括号中的内容； va<就是把尖括号也选中， 也可以用vi"选中引号的内容， va"选中包括引号的内容，即便在引号外面，也可以选中，这样改起来很方便，但尖括号不能。当然也可以直接ci"直接把引号的内容修改了。

vi和ci中的i是in的意思。同理ciw可以修改当前单词，而caw会把字符周围的空格也修改掉
ce:从当前光标到单词结尾处e进行修改
## 进入正题

### 缩进

set cindent
按%可以在{}两边互换，那么就可以使用上面的va{选中花括号中的内容，或者vi{选择花括号中的内容。

按(或)会在空行和段落的首位之间跳转
按[]会在多个函数之间跳转
按{或}会在多个段落之间跳转，就是在空行之间跳转
那么，在这三个之间，就可以进行vi(, va(, ci(, ca(进行相应的操作。

tab：是8，就是8个字节。
set ts=4 这样tab就只有4个字节了，此时换行时还是固执的为8，这时候也可设置软件大小
set sw=4 让软件生成的大小也为4, set width 为4
 set et 这个非常非常方便，把tab换成空格 让生成的tab为空格，这样手打出来的tab也会被转换为空格。在python时可以去掉很多麻烦。
若是不喜欢把tab换成空格，可以为 set noet  empty tab
若还有硬tab，可以V选中行后=，就可以转换为=，编程规定的tab样式。若是没有缩进，全选中之后，ggVG=，就可以格式化缩进。
>>自己手动设置tab，可以用这个

>i{将是当前括号内缩进：缩进插入到{中。通常都是选中，按一下右键>就可以，那么左键<就是减少缩进
					
缩进也可以自己不设置，而在vimrc中设置

	filetype on
	filetype plugin on
	filetype indent on
	就会自动根据文件类型，进行缩进，建议打开

vim用引号表示注释

小彭老师的.vimrc在github.com/archibate

Q：代码中有空格
A：%s/\s*$//g  代表以空格0个或多个并与行为链接的$的，更改为空格。s表示whitespace。或者全部选中:ggVG，然后执行,s/\s*$//，也可以全部替换。
那么s/^\s*//删除前导空格


## 复制粘贴
从vim外面复制之后，如何插入vim呢？
使用Shift+Insert，或Ctrl+Shift+V
有CCBY协议。
Shift+Insert是使用系统的剪切板，Vim有自己的剪切板。

自己的剪切板：
copy，用y表示复制选中的字符，
用p（past）就是粘贴在当前光标后面。
大写V是复制行。
等价：Vy，Y，yy，最经典的用法就是yyp，就是复制一行，
而yyP，就是复制到前面一行。很经典

D:相当与d$
ddp:删除一行之后再复制该行，目的就是交换两行。
x或dd是到vim的剪贴板上的。

s：删除并插入
xi1:修改某字符为1，
s等价与xi，删除之后再插入insert。
还可以用5s（删除5个并进入），不如ciw方便。
r：当前光标下替换 5r：替换多次。
f*：找下一个*，F*往前找第一个*，特别好用。
Vim让你可以让键盘可以移动光标，而不是鼠标！！！
用f和F的时候，也可以用t或T：forward， toward。
都是查找，前者在目标上，后者在目标前一个

vim分为命令和插入两个模式，各个模式下做相应的事情。

## 运行程序
$sh 启动临时的shell
$g++ ..
$./a.out
$exit 或 ctrl+d返回
这样执行命令并返回代码，方便。建议把sh绑定到快捷键上。

		绑定快捷键
		一般把F8绑定到sh上。如 :nnoremap <F8> :sh<CR>   <CR>表示换行

除了使用sh之外，还可以用!g++ test.cc -o main 直接运行
还有，可以用%号代替当前的文件名：!g++ % -o main，会自动将%替换成test.cc

建议也将当前的编译命令!g++ test.cc -o main 绑定到某一个键，如F5

	:noremap <F5> :wa<CR> :!g++ % -o a.out && ./a.out<CR> 先保存，之后运行g++，之后执行a.out运行可执行文件。太方便啦！

	还有就是<F4>绑定到wa上，如是:noremap <F4> :wa<CR>

以上方法特方便

可用：nnoremap绑定多个映射。nmap会递归，而nnoremap不会递归。

建议将nnoremap放到.vimrc中，如下：

	nnoremap <F4> :wa<CR>
	nnoremap <F5> :wa<CR> :!g++ % -o /tmp/a.out && /tmp/a.out<CR>
	nnoremap <F8> :sh<CR> 


我们还可以使用Makefile管理工程文件：

	Makefile
	run: hello
		./hello
	hello: hello.cpp
		g++ hello.cpp -o hello
 
	make就可以运行./hello文件了

	进入代码后，当然可以用!make运行。
	!是执行外部命令，最好用vim内置的make命令，好处是若有错误，会报错。而且用:cw可以给出调错窗口，双击的话，会自动跳转到出错的代码处。

建议将F5映射为：:nnoremap <F5> :wa<CR> :make<CR><CR>,这样F5之后，就会执行make，同时将出错信息显示在最下面的一行中，然后:cw，就可以显示出错调试框，点击出错处，定位到代码处。还有在头文件处，点击
gf(goto file)可以跳转到对应的头文件，按Ctrl+o(original)回到原来的地方，按Ctrl+i，再跳转过去。

:ls 查看缓存区的文件, 
#表示编辑， 
%a表示刚刚操作的文件，或者说当前处理的文件
=表示ctrl+o上一个打开的文件，目前没有看到过=
还可以:ls之后用b1跳转到缓存区的1号文件

gd：还可以跳转到定义

## 插件
 
在shell中执行：export https_proxy=192.168.1.103:8889表示设置https代理
这个时候执行：curl github.com 这个时候执行git会非常快，为什么呢？以后再说
有了vimrc之后，再创建.vim文件夹，之后执行切换到.vim文件夹里面，把`` `https://github.com/junegunn/vim-plug/blob/master/plug.vim` 这个文件下载下来,直接在～文件夹下，执行：

	curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
下载之后，就算成功安装这个插件，那如何使用呢？

在.vimrc中：

call plug#begin()
Plug 'scrooloose/nerdtree' "Plug表示要安装，第一次进入，还需要安装：PlugInstall，它会在github这个目录下载这个插件，实际上是clone github.com/scrooloose/nerdtree 这个工程文件到本地，这个.vim/plugged就安装了nerdtree这个工程。:NERDTree,就可以展现文件浏览器
顺便说一下：vim .可以打开目录,可以打开任何一个文件，甚至是zip文件，当vim打开多个文件之后，并不显示所有文件，可以用bn和bp切换文件，通常可以使用<F2><F3>映射bp和bn

以后新增一个插件时，就运行:PlugInstall。
call plug#end()

### 使用vim-plug插件
推荐使用插件如下：
'vim-scripts/vim-airline' 可以显示buffer，有一堆设置，还可以用这个命令：
autocmd BufReadpost * tab ball, 这个时候就可以使用vim内部的:tabn :tabp进行切换

'preservim/nerdtree', {'on': 'NERDTreeToggle'}
'bfrg/vim-cpp-modern', {'for': 'cpp'}
	
:terminal 可以启动内嵌的终端,是8.1版本新增功能。可以用Ctrl+d退出，在Ctrl+w和Ctrl+w之间切换，或Ctrl+w hjkl进行切换 +- 增减高度

由于我是使用Vundle进行插件管理，将来有待进一步优化。
