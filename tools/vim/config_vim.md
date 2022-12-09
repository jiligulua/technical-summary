## vim添加markdown-preview

我使用Vundle作为vim的插件包管理器，操作如下：

Place this in your .vimrc or init.vim,
Plugin 'iamcco/markdown-preview.nvim'
... then run the following in vim (to complete the Plugin installation):

1. :source %
2. :PluginInstall
3. :call mkdp#util#install()

let g:mkdp_brower='chromium'

nmap :MarkdownPreviewToggle

操作

vim 1.md

Ctrl+P 在浏览器中展现文档内容
