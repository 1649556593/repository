# 基于 VSCode 和 CMake 进行 C/C++ 开发

## 第一章 GCC 编译器

### 01 编译过程

**预处理（Pre-processing）**
>展开宏，头文件，替换条件编译，删除注释、空行、空白
生成`.i`文件：

```bash
g++ -E test.cpp -o test.i
```

- `-E`：只进行预处理。

**编译（Compiling）**
>检查语法规范
生成`.s`汇编文件：

```bash
g++ -S test.i -o test.s
```

- `-S`：生成汇编文件。

**汇编（Assembling）**
>将汇编指令翻译成机器指令
生成`.o`目标文件：

```bash
g++ -c test.s -o test.o
```

- `-c`：把源代码编译为机器语言的目标代码文件。

**链接（Linking）**
>数据段合并，数据地址回填
生成可执行文件：

```bash
g++ test.o -o test
```
>-o是用来起名的
### 02 GCC 编译选项

**`-g`：生成调试信息**

`-g`选项告诉GCC生成可以被GNU调试器GDB使用的调试信息。

```bash
g++ -g test.cpp -o test
```

**`-O[n]`：优化源代码**

优化会省略代码中从未使用的变量、直接使用常量表达式的结果等，从而缩减目标文件中的代码量，提高可执行文件的运行效率。

| 选项 | 说明 |
| --- | --- |
| `-O0` | 不进行优化 |
| `-O` | 同时减小代码长度和执行时间，效果等价于`-O1` |
| `-O1` | 基本优化 |
| `-O2` | 在`-O1`基础上进行额外优化，如指令调整等 |
| `-O3` | 包括循环展开和其他与处理器特性相关的优化 |

优化等级越高，编译速度可能越慢，但通常生成的代码执行速度更快。

```bash
g++ -O2 test.cpp
```

**`-l`和`-L`：指定库与库文件路径**

```bash
# -l参数（小写）用于指定要链接的库，参数后紧接库名
# /lib、/usr/lib和/usr/local/lib中的库通常可以直接使用-l链接

# 链接glog库
g++ -lglog test.cpp

# 库文件不在默认目录时，使用-L参数（大写）指定库文件所在目录
# libmytest.so位于/home/bing/mytestlibfolder目录
g++ -L/home/bing/mytestlibfolder -lmytest test.cpp
```

**`-I`：指定头文件搜索目录**

`/usr/include`目录通常不需要指定。如果头文件不在默认目录中，则需要使用`-I`指定搜索路径，否则会出现`xxxx.h: No such file or directory`错误。`-I`也可以使用相对路径，例如用`-I.`指定当前目录。

```bash
g++ -I/myinclude test.cpp
```

**`-Wall`：打印警告信息**

```bash
g++ -Wall test.cpp
```

**`-w`：关闭警告信息**

```bash
g++ -w test.cpp
```

**`-std=c++11`：指定C++标准**

```bash
g++ -std=c++11 test.cpp
```

**`-o`：指定输出文件名**

不使用`-o`时，默认生成`a.out`。

```bash
g++ test.cpp -o test
```

**`-DDEBUG`：定义宏**

`-Dname`用于定义宏`name`，默认值为`1`。

```cpp
#include <stdio.h>

int main()
{
#ifdef DEBUG
    printf("DEBUG LOG\n");
#endif
    printf("in\n");
}
```

编译时定义`DEBUG`宏：

```bash
g++ -DDEBUG main.cpp
```

**查看GCC手册**

```bash
man gcc
```

## 第二章 GDB 调试器

### 01 启动调试

```bash
gdb 可执行文件名
```

调试的可执行文件应使用`-g`选项编译，以便包含调试信息。

### 02 常用调试命令

括号内为命令的简写，例如输入`r`等同于输入`run`。

| 命令 | 说明 |
| --- | --- |
| `help`（`h`） | 查看命令帮助；使用`help 命令`查询具体命令 |
| `run`（`r`） | 重新开始运行文件 |
| `start` | 运行程序并停在第一行可执行语句 |
| `list`（`l`） | 查看源代码；`list 行号`从指定行开始查看，`list 函数名`查看指定函数 |
| `set` | 设置变量的值 |
| `next`（`n`） | 单步调试，不进入函数内部 |
| `step`（`s`） | 单步调试，进入自定义函数内部 |
| `backtrace`（`bt`） | 查看函数调用的栈帧和层级关系 |
| `frame`（`f`） | 切换函数栈帧 |
| `info`（`i`） | 查看相关信息，如函数内部局部变量的值 |
| `finish` | 运行至当前函数结束，返回函数调用点 |
| `continue`（`c`） | 继续运行到下一个断点 |
| `print`（`p`） | 打印值及地址 |
| `quit`（`q`） | 退出GDB |
| `break 行号`（`b 行号`） | 在指定行设置断点 |
| `info breakpoints` | 查看当前设置的所有断点 |
| `delete breakpoints 编号`（`d 编号`） | 删除指定编号的断点 |
| `display 表达式` | 持续显示指定变量或表达式的值 |
| `undisplay 编号` | 取消持续显示 |
| `watch 变量` | 变量发生修改时暂停并显示 |
| `info watchpoints` | 显示观察点 |
| `enable breakpoints` | 启用断点 |
| `disable breakpoints` | 禁用断点 |
| `x/20xw 地址` | 查看内存：显示20个单元，十六进制，每个单元4字节 |
| `run argv[1] argv[2]` | 调试时传递命令行参数 |
| `set follow-fork-mode child` | 程序调用`fork()`后跟踪子进程 |

## 第三章 CMake

### 01 CMake语法特性

- 基本语法格式：`指令(参数1 参数2 ...)`
- 参数使用括号括起。
- 参数之间使用空格或分号分开。
- 指令名称与大小写无关，参数和变量名称与大小写有关。
- 变量使用`${变量名}`取值，但在`if`控制语句中直接使用变量名。

```cmake
set(HELLO hello.cpp)
add_executable(hello main.cpp hello.cpp)
ADD_EXECUTABLE(hello main.cpp ${HELLO})
```

### 02 重要指令

**`cmake_minimum_required`：指定CMake最低版本**

```cmake
# 语法：cmake_minimum_required(VERSION versionNumber [FATAL_ERROR])
# CMake最低版本要求为2.8.3
cmake_minimum_required(VERSION 2.8.3)
```

**`project`：定义工程名称和支持的语言**

```cmake
# 语法：project(projectname [CXX] [C] [Java])
# 指定工程名为HELLOWORLD
project(HELLOWORLD)
```

**`set`：显式定义变量**

```cmake
# 语法：set(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
# 定义SRC变量，其值为main.cpp、sayhello.cpp和hello.cpp
set(SRC main.cpp sayhello.cpp hello.cpp)
```

**`include_directories`：添加头文件搜索路径**

相当于指定`g++`编译器的`-I`参数。

```cmake
# 语法：include_directories([AFTER|BEFORE] [SYSTEM] dir1 dir2 ...)
# 将/usr/include/myincludefolder和./include添加到头文件搜索路径
include_directories(/usr/include/myincludefolder ./include)
```

**`link_directories`：添加库文件搜索路径**

相当于指定`g++`编译器的`-L`参数。

```cmake
# 语法：link_directories(dir1 dir2 ...)
# 将/usr/lib/mylibfolder和./lib添加到库文件搜索路径
link_directories(/usr/lib/mylibfolder ./lib)
```

**`add_library`：生成库文件**

```cmake
# 语法：add_library(libname [SHARED|STATIC|MODULE] [EXCLUDE_FROM_ALL] source1 ... sourceN)
# 通过SRC变量生成libhello.so共享库
add_library(hello SHARED ${SRC})
```

**`add_compile_options`：添加编译参数**

```cmake
# 语法：add_compile_options(<option> ...)
# 添加编译参数-Wall、-std=c++11和-O2
add_compile_options(-Wall -std=c++11 -O2)
```

**`add_executable`：生成可执行文件**

```cmake
# 语法：add_executable(exename source1 source2 ... sourceN)
# 编译main.cpp，生成可执行文件main
add_executable(main main.cpp)
```

**`target_link_libraries`：为目标添加需要链接的库**

相当于指定`g++`编译器的`-l`参数。

```cmake
# 语法：target_link_libraries(target library1 <debug|optimized> library2 ...)
# 将hello动态库链接到可执行文件main
target_link_libraries(main hello)
```

**`add_subdirectory`：添加源文件子目录**

向当前工程添加存放源文件的子目录，也可以指定中间二进制文件和目标二进制文件的存放位置。子目录中需要包含一个`CMakeLists.txt`文件。

```cmake
# 语法：add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
# 添加src子目录，src中需要有一个CMakeLists.txt
add_subdirectory(src)
```

**`aux_source_directory`：收集目录中的源代码文件**

发现指定目录下的所有源代码文件，并将列表存储在变量中，常用于临时自动构建源文件列表。

```cmake
# 语法：aux_source_directory(dir VARIABLE)
# 定义SRC变量，其值为当前目录下所有源代码文件
aux_source_directory(. SRC)

# 编译SRC变量代表的源代码文件，生成main可执行文件
add_executable(main ${SRC})
```

### 03 CMake常用变量

**编译选项变量**

| 变量 | 说明 |
| --- | --- |
| `CMAKE_C_FLAGS` | GCC的C语言编译选项 |
| `CMAKE_CXX_FLAGS` | G++的C++编译选项 |

```cmake
# 在CMAKE_CXX_FLAGS编译选项后追加-std=c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
```

**编译类型**

`CMAKE_BUILD_TYPE`用于设置编译类型，如`Debug`或`Release`。

```cmake
# 调试时使用Debug
set(CMAKE_BUILD_TYPE Debug)

# 发布时使用Release
set(CMAKE_BUILD_TYPE Release)
```

**二进制目录变量**

| 变量 | 说明 |
| --- | --- |
| `CMAKE_BINARY_DIR` | CMake构建目录 |
| `PROJECT_BINARY_DIR` | 当前工程的构建目录 |
| `<projectname>_BINARY_DIR` | 指定工程的构建目录 |

- 这三个变量指代的内容通常一致。
- 内部构建（in-source build）时，指向工程顶层目录。
- 外部构建（out-of-source build）时，指向工程构建发生的目录。
- `PROJECT_BINARY_DIR`与其他变量稍有区别，当前可以先理解为一致。

**源代码目录变量**

| 变量 | 说明 |
| --- | --- |
| `CMAKE_SOURCE_DIR` | 顶层`CMakeLists.txt`所在的源代码目录 |

**编译器与输出路径变量**

| 变量 | 说明 |
| --- | --- |
| `CMAKE_C_COMPILER` | 指定C编译器 |
| `CMAKE_CXX_COMPILER` | 指定C++编译器 |
| `EXECUTABLE_OUTPUT_PATH` | 可执行文件输出的存放路径 |
| `LIBRARY_OUTPUT_PATH` | 库文件输出的存放路径 |

### 04 CMake工程目录结构

项目主目录中需要有一个`CMakeLists.txt`文件。包含源文件的子目录有两种组织方式：

1. 子目录包含自己的`CMakeLists.txt`文件，主目录通过`add_subdirectory`添加子目录。
2. 子目录不包含`CMakeLists.txt`文件，子目录的编译规则统一写在主目录的`CMakeLists.txt`中。

### 05 CMake编译流程

在Linux平台下使用CMake构建C/C++工程的基本流程：

1. 编写`CMakeLists.txt`。
2. 执行`cmake PATH`生成Makefile，其中`PATH`是顶层`CMakeLists.txt`所在目录。
3. 执行`make`进行编译。

路径说明：

```text
.   表示当前目录
./  表示当前目录
..  表示上级目录
../ 表示上级目录
```

### 06 两种构建方式

**内部构建（in-source build）**

不推荐使用。内部构建会在源代码目录中产生大量中间文件，使工程目录显得杂乱。

```bash
# 在当前目录中读取CMakeLists.txt，生成Makefile和其他文件
cmake .

# 执行编译并生成目标
make
```

**外部构建（out-of-source build）**

推荐使用。外部构建将编译输出文件与源文件放在不同目录中。

```bash
# 1. 在当前目录中创建build文件夹
mkdir build

# 2. 进入build文件夹
cd build

# 3. 读取上级目录的CMakeLists.txt，生成Makefile和其他文件
cmake ..

# 4. 执行编译并生成目标
make
```

也可以使用CMake的`-S`和`-B`参数完成外部构建：

```bash
cmake -S . -B build
cmake --build build
```
