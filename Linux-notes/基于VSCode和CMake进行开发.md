# GCC编译器
## 编译过程
1. 预处理pre-processing      //.i文件
g++ -E test.cpp -o test.i   //-E预处理
2. 编译Compiling             //.s文件
g++ -S test.i -o test.s     //-S生成汇编文件
3. 汇编Assembling            //.o文件
g++ -c test.s -o test.o     //-c把源代码编译为机器语言的目标代码文件
4. 链接-Linking
g++ test.o -o test          //生成可执行文件

## GCC 编译选项
1. -g 编译带调试信息的可执行文件
 -g 选项告诉 GCC 产生能被 GNU 调试器GDB使用的调试信息，以调试程序。
 产生带调试信息的可执行文件test
g++ -g test.cpp -o test
2. -O[n] 优化源代码
 所谓优化，例如省略掉代码中从未使用过的变量、直接将常量表达式用结果值代替等等，这些操作会缩减目标文件所包含的代码量，提高最终生成的可执行文件的运行效率。
 -O1 选项告诉 g++ 对源代码进行基本优化。这些优化在大多数情况下都会使程序执行的更快。 -O2 选项告诉 g++ 产生尽可能小和尽可能快的代码。 如-O2，-O3，-On (n 常为0-3)
 -O 同时减小代码的长度和执行时间，其效果等价于-O1
 -O0 表示不做优化
 -O1 为默认优化
 -O2 除了完成-O1的优化之外，还进行一些额外的调整工作，如指令调整等。
 -O3 则包括循环展开和其他一些与处理特性相关的优化工作。
 选项将使编译的速度比使用 -O 时慢， 但通常产生的代码执行速度会更快。

 使用 -O2优化源代码，并输出可执行文件
g++ -O2 test.cpp
3. -l和-L指定库文件|指定库文件路径
```bash
# -l参数(小写)就是用来指定程序要链接的库，-l参数紧接着就是库名
# 在/lib和/usr/lib和/usr/local/lib里的库直接用-l参数就能链接

# 链接glog库
g++ -lglog test.cpp

# 如果库文件没放在上面三个目录里，需要使用-L参数(大写)指定库文件所在目录
# -L参数跟着的是库文件所在的目录名

# 链接mytest库，libmytest.so在/home/bing/mytestlibfolder目录下
g++ -L/home/bing/mytestlibfolder -lmytest test.cpp
```

4. -I 指定头文件搜索目录
```bash
# -I
# /usr/include目录一般是不用指定的，gcc知道去那里找，但是如果头文件不在/usr/icnclude里我们就要
# 用-I参数指定了，比如头文件放在/myinclude目录里，那编译命令行就要加上-I/myinclude 参数了，如果不加
# 你会得到一个"xxxx.h: No such file or directory"的错误。-I参数可以用相对路径，比如头文件在当前 目
# 录，可以用-I.来指定。上面我们提到的-cflags参数就是用来生成-I参数的。
g++ -I/myinclude test.cpp
```

5. -Wall 打印警告信息
```bash
# 打印出gcc提供的警告信息
g++ -Wall test.cpp
```

6. -w 关闭警告信息
```bash
# 关闭所有警告信息
g++ -w test.cpp
```

7. -std=c++11
```bash
# 使用c++11标准编译test.cpp
g++ -std=c++11 test.cpp
```

8. -o指定输出文件名
```bash
# 指定即将产生的文件名
# 如果不写默认生成a.out
g++  test.cpp -o test
```

9. -DDEBUG定义宏
```C
// .-Dname 定义宏name,默认定义内容为字符串"1"

#include <stdio.h>

int main()
{
    #ifdef DEBUG
        printf("DEBUG LOG\n");
    #endif
        printf("in\n");
}

// 1. 在编译的时候，使用gcc -DDEBUG main.cpp
// 2. 第七行代码可以被执行
```

10. 可以输入man gcc就可以查看gcc英文使用手册


# GDB调试器
## 常用调试命令参数
调试开始：执行 gdb [exefilename]，进入 gdb 调试程序，其中 exefilename 为要调试的可执行文件名。
```bash
## 以下命令后括号内为命令的简化使用，比如run（r），直接输入命令 r 就代表命令run

$(gdb)help(h)        # 查看命令帮助，具体命令查询在gdb中输入help + 命令

$(gdb)run(r)         # 重新开始运行文件（run-text：加载文本文件，run-bin：加载二进制文件）

$(gdb)start          # 单步执行，运行程序，停在第一行执行语句

$(gdb)list(l)        # 查看源代码（list-n，从第n行开始查看代码。list+ 函数名：查看具体函数）

$(gdb)set            # 设置变量的值

$(gdb)next(n)        # 单步调试（逐过程，函数直接执行）

$(gdb)step(s)        # 单步调试（逐语句：跳入自定义函数内部执行）

$(gdb)backtrace(bt)  # 查看函数的调用的栈帧和层级关系

$(gdb)frame(f)       # 切换函数的栈帧

$(gdb)info(i)        # 查看函数内部局部变量的数值

$(gdb)finish         # 结束当前函数，返回到函数调用点

$(gdb)continue(c)    # 继续运行

$(gdb)print(p)       # 打印值及地址

$(gdb)quit(q)        # 推出gdb

$(gdb)break+num(b)              # 在第num行设置断点

$(gdb)info breakpoints          # 查看当前设置的所有断点

$(gdb)delete breakpoints num(d) # 删除第num个断点

$(gdb)display                   # 追踪查看具体变量值

$(gdb)undisplay                 # 取消追踪观察变量

$(gdb)watch                     # 被设置观察点的变量发生修改时，打印显示

$(gdb)i watch                   # 显示观察点

$(gdb)enable breakpoints        # 启用断点

$(gdb)disable breakpoints       # 禁用断点

$(gdb)x                         # 查看内存 x/20xw 显示20个单元，16进制，4字节每单元

$(gdb)run argv[1] argv[2]       # 调试时命令行传参

$(gdb)set follow-fork-mode child # Makefile项目管理：选择跟踪父子进程（fork()）
```