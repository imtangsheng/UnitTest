## WinDbg 调试使用测试

- [程序下载](https://developer.microsoft.com/zh-cn/windows/downloads/windows-sdk/)
- 选择安装调试工具,第二个debug tool

### WinDbg使用教程

1. 设置pdb路径：File ->Symbol File Path
1. 设置exe路径：File -> Image File Path
1. 设置源代码路径：File -> Source File Path(源代码所在顶级目录)
1. 打开dmp文件：File ->Open Crash Dump
1. 执行命令 !analyze –v (命令显示界面中有命令说明点击即可指向)

### VS2022

用VisualStudio打开dmp文件。测试时 dmp文件时本地产生的，因此VS会依据dmp文件自行找到exe，pdb和源代码的路径。因此直接点击调试，程序会出错代码行中断。

但若dmp文件是exe在另一台机器上产生的，则我们最好把exe,pdb,dmp放到同一文件夹下，必须保证pdb与出问题的exe是同一时间生成的，用VS打开dmp文件后还需要设置符号表文件路径和源代码路径

1. 当把pdb文件与dmp文件放入同一目录下时，就不需设置其路径，否则需要设置:工具->选项->调试->符号
1. 还需设置源代码路径：属性->调试源代码.这样点击“使用仅限本机进行调试”，即可在出错代码行中断.



## 参考资料
1. [Windows下dump文件生成与分析](https://cloud.tencent.com/developer/article/2073174)