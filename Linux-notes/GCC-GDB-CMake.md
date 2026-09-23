# GCC、GDB 与 CMake

## 一、GCC 编译器

### 1. 编译流程

| 阶段 | 作用 | 命令 | 产物 |
| --- | --- | --- | --- |
| 预处理 | 展开宏、头文件等 | `g++ -E test.cpp -o test.i` | `.i`文件 |
| 编译 | 将预处理文件转换为汇编代码 | `g++ -S test.i -o test.s` | `.s`文件 |
| 汇编 | 将汇编代码转换为机器码 | `g++ -c test.s -o test.o` | `.o`文件 |
| 链接 | 链接目标文件和库 | `g++ test.o -o test` | 可执行文件 |

### 2. 常用编译选项

| 选项 | 作用 | 示例 |
| --- | --- | --- |
| `-g` | 生成GDB所需的调试信息 | `g++ -g test.cpp -o test` |
| `-O0` | 不进行优化 | `g++ -O0 test.cpp` |
| `-O1`或`-O` | 基本优化 | `g++ -O1 test.cpp` |
| `-O2` | 在`-O1`基础上进行更多优化 | `g++ -O2 test.cpp` |
| `-O3` | 更激进的优化，如循环展开 | `g++ -O3 test.cpp` |
| `-I路径` | 添加头文件搜索路径 | `g++ -I/myinclude test.cpp` |
| `-L路径` | 添加库文件搜索路径 | `g++ -L/home/bing/mytestlibfolder test.cpp` |
| `-l库名` | 链接指定库 | `g++ test.cpp -lglog` |
| `-Wall` | 显示常用警告信息 | `g++ -Wall test.cpp` |
| `-w` | 关闭所有警告信息 | `g++ -w test.cpp` |
| `-std=c++11` | 使用C++11标准 | `g++ -std=c++11 test.cpp` |
| `-o 文件名` | 指定输出文件名 | `g++ test.cpp -o test` |
| `-D宏名` | 在编译时定义宏，默认值为`1` | `g++ -DDEBUG main.cpp` |

补充说明：

- `/usr/include`通常不需要通过`-I`指定；其他头文件目录需要手动添加。
- `/lib`、`/usr/lib`和`/usr/local/lib`中的库通常可以直接使用`-l`链接。
- 不使用`-o`时，G++默认生成`a.out`。
- 优化等级越高，编译可能越慢，但生成的程序通常运行得更快。

同时指定头文件、库目录和库：

```bash
g++ test.cpp -I./include -L./lib -lmytest -o test
```

条件编译示例：

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

查看GCC手册：`man gcc`。

## 二、GDB 调试器

### 1. 启动调试

先使用`-g`选项编译，再启动GDB：

```bash
g++ -g main.cpp -o main
gdb main
```

### 2. 常用命令

括号内是命令简写。

| 命令 | 作用 |
| --- | --- |
| `help`（`h`） | 查看帮助；`help 命令`查看指定命令的帮助 |
| `run`（`r`） | 从头运行程序，可在后面添加命令行参数 |
| `start` | 运行程序并停在第一行可执行语句 |
| `list`（`l`） | 查看源代码，可指定行号或函数名 |
| `next`（`n`） | 单步执行，不进入函数内部 |
| `step`（`s`） | 单步执行，进入自定义函数内部 |
| `continue`（`c`） | 继续运行到下一个断点 |
| `finish` | 运行到当前函数结束并返回调用点 |
| `break 行号/函数`（`b`） | 设置断点 |
| `info breakpoints` | 查看所有断点 |
| `delete 编号`（`d`） | 删除指定断点 |
| `enable 编号` | 启用断点 |
| `disable 编号` | 禁用断点 |
| `print 表达式`（`p`） | 打印变量、表达式或地址 |
| `display 表达式` | 每次暂停时自动显示表达式的值 |
| `undisplay 编号` | 取消自动显示 |
| `watch 变量` | 变量发生变化时暂停程序 |
| `info watchpoints` | 查看观察点 |
| `backtrace`（`bt`） | 查看函数调用栈 |
| `frame 编号`（`f`） | 切换栈帧 |
| `info locals` | 查看当前栈帧的局部变量 |
| `set variable 变量=值` | 修改变量值 |
| `x/20xw 地址` | 以十六进制查看20个4字节内存单元 |
| `set follow-fork-mode child` | `fork()`后跟踪子进程 |
| `quit`（`q`） | 退出GDB |

## 三、CMake

### 1. 基本语法

- 格式：`指令(参数1 参数2 ...)`。
- 参数使用括号括起，以空格或分号分隔。
- 指令名称不区分大小写，参数和变量名称区分大小写。
- 使用`${变量名}`取得变量值；在`if`语句中可以直接使用变量名。

```cmake
set(HELLO hello.cpp)
add_executable(hello main.cpp ${HELLO})
```

### 2. 常用指令

| 指令 | 作用 | 常用格式 |
| --- | --- | --- |
| `cmake_minimum_required` | 指定CMake最低版本 | `cmake_minimum_required(VERSION 2.8.3)` |
| `project` | 定义工程名和支持的语言 | `project(HELLOWORLD CXX)` |
| `set` | 定义变量 | `set(SRC main.cpp hello.cpp)` |
| `include_directories` | 添加头文件搜索路径，相当于`-I` | `include_directories(./include)` |
| `link_directories` | 添加库文件搜索路径，相当于`-L` | `link_directories(./lib)` |
| `add_library` | 生成静态库、共享库或模块库 | `add_library(hello SHARED ${SRC})` |
| `add_compile_options` | 添加编译参数 | `add_compile_options(-Wall -O2)` |
| `add_executable` | 生成可执行文件 | `add_executable(main main.cpp)` |
| `target_link_libraries` | 为目标链接库，相当于`-l` | `target_link_libraries(main hello)` |
| `add_subdirectory` | 添加包含`CMakeLists.txt`的子目录 | `add_subdirectory(src)` |
| `aux_source_directory` | 收集目录中的源代码文件 | `aux_source_directory(. SRC)` |

完整语法速查：

```cmake
cmake_minimum_required(VERSION versionNumber [FATAL_ERROR])
project(projectname [CXX] [C] [Java])
set(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
include_directories([AFTER|BEFORE] [SYSTEM] dir1 dir2 ...)
link_directories(dir1 dir2 ...)
add_library(libname [SHARED|STATIC|MODULE] [EXCLUDE_FROM_ALL] source1 ... sourceN)
add_compile_options(<option> ...)
add_executable(exename source1 source2 ... sourceN)
target_link_libraries(target library1 <debug|optimized> library2 ...)
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
aux_source_directory(dir VARIABLE)
```

### 3. 常用变量

| 变量 | 作用 |
| --- | --- |
| `CMAKE_C_FLAGS` | C语言编译选项 |
| `CMAKE_CXX_FLAGS` | C++编译选项 |
| `CMAKE_BUILD_TYPE` | 构建类型，如`Debug`或`Release` |
| `CMAKE_BINARY_DIR` | 顶层构建目录 |
| `PROJECT_BINARY_DIR` | 当前工程的构建目录 |
| `<projectname>_BINARY_DIR` | 指定工程的构建目录 |
| `CMAKE_SOURCE_DIR` | 顶层`CMakeLists.txt`所在目录 |
| `CMAKE_C_COMPILER` | C编译器 |
| `CMAKE_CXX_COMPILER` | C++编译器 |
| `EXECUTABLE_OUTPUT_PATH` | 可执行文件输出目录 |
| `LIBRARY_OUTPUT_PATH` | 库文件输出目录 |

常用设置：

```cmake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)
```

`CMAKE_BINARY_DIR`、`PROJECT_BINARY_DIR`和`<projectname>_BINARY_DIR`通常指向同一位置：内部构建时指向工程顶层目录，外部构建时指向构建目录。

### 4. 工程目录

项目主目录需要包含`CMakeLists.txt`。源文件子目录有两种组织方式：

1. 子目录有自己的`CMakeLists.txt`，主目录使用`add_subdirectory`添加子目录。
2. 子目录没有`CMakeLists.txt`，所有编译规则都写在主目录的`CMakeLists.txt`中。

简单工程示例：

```text
project/
├── CMakeLists.txt
├── include/
│   └── hello.h
└── src/
    ├── CMakeLists.txt
    ├── main.cpp
    └── hello.cpp
```

主目录的`CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 2.8.3)
project(HELLOWORLD CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)
```

`src/CMakeLists.txt`：

```cmake
set(SRC main.cpp hello.cpp)
add_library(hello SHARED hello.cpp)
add_executable(main main.cpp)
target_link_libraries(main hello)
```

### 5. 构建工程

基本流程：编写`CMakeLists.txt`，使用`cmake`生成Makefile，再使用`make`编译。

内部构建（in-source build）会在源码目录产生大量中间文件，不推荐使用：

```bash
cmake .
make
```

外部构建（out-of-source build）将源码和编译产物分开，推荐使用：

```bash
mkdir build
cd build
cmake ..
make
```

也可以直接指定源码目录和构建目录：

```bash
cmake -S . -B build
cmake --build build
```

路径中`.`和`./`表示当前目录，`..`和`../`表示上级目录。
