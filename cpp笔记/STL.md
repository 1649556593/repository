# C++ STL 容器学习笔记

> 来源：`text3.cpp`。  
> 范围：STL 初识、迭代器、`string`、`vector`、`deque`、`stack`、`queue`、`list`、`set` / `multiset`、`pair`。  
> 当前容器部分还没有学完，本篇先整理到 `set` / `multiset`。

## 目录

1. STL 初识
2. 迭代器
3. `vector` 基础遍历
4. `vector` 存放自定义类型
5. 容器嵌套容器
6. `string` 容器
7. `vector` 容器详解
8. `deque` 容器
9. 案例：评委打分
10. `stack` 容器
11. `queue` 容器
12. `list` 容器
13. `set` / `multiset` 容器
14. 容器选择速查

## 1. STL 初识

C++ 中提高复用性的两条重要路线：

- 面向对象：封装、继承、多态。
- 泛型编程：模板。

STL 是 Standard Template Library，即标准模板库。STL 几乎所有代码都采用模板类和模板函数实现。

STL 广义上分为：

| 部分 | 作用 |
| --- | --- |
| 容器 | 存放数据 |
| 算法 | 操作数据 |
| 迭代器 | 连接容器和算法 |

容器和算法之间通过迭代器进行连接。

```cpp
vector<int> v;
sort(v.begin(), v.end());
```

这里：

- `vector<int>` 是容器。
- `sort` 是算法。
- `v.begin()`、`v.end()` 返回迭代器。

### 1.1 STL 六大组件

| 组件 | 作用 | 例子 |
| --- | --- | --- |
| 容器 | 各种数据结构，用来存放数据 | `vector`、`list`、`deque`、`set`、`map` |
| 算法 | 常用算法 | `sort`、`find`、`copy`、`for_each` |
| 迭代器 | 容器和算法之间的桥梁 | `vector<int>::iterator` |
| 仿函数 | 行为类似函数，可以作为算法策略 | 重载 `operator()` 的类 |
| 适配器 | 修饰容器、仿函数或迭代器接口 | `stack`、`queue` |
| 空间配置器 | 负责空间配置和管理 | `allocator` |

### 1.2 容器分类

| 分类 | 特点 | 例子 |
| --- | --- | --- |
| 序列式容器 | 强调元素顺序，每个元素有固定位置 | `vector`、`deque`、`list` |
| 关联式容器 | 常用树结构组织元素，元素按规则排序 | `set`、`multiset`、`map`、`multimap` |

序列式容器强调“位置”。  
关联式容器强调“排序规则、查找规则”。

### 1.3 算法分类

常见算法：

```cpp
sort
find
copy
for_each
```

算法可以分为：

- 质变算法：会改变容器内容或顺序，例如 `sort`、`copy`。
- 非质变算法：不改变容器内容，例如 `find`、`for_each` 中只打印时。

## 2. 迭代器

迭代器是容器和算法之间的胶合剂。算法需要通过迭代器访问容器中的数据。

每个容器都有自己的迭代器类型：

```cpp
vector<int>::iterator
deque<int>::iterator
list<int>::iterator
set<int>::iterator
```

### 2.1 `begin()` 和 `end()`

```cpp
v.begin(); // 指向第一个元素
v.end();   // 指向最后一个元素的下一个位置
```

`end()` 不指向有效元素，不能解引用。

正确遍历：

```cpp
for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
{
    cout << *it << endl;
}
```

### 2.2 迭代器种类

| 迭代器类型 | 能力 |
| --- | --- |
| 输入迭代器 | 只读，只能向前 |
| 输出迭代器 | 只写，只能向前 |
| 前向迭代器 | 读写，只能向前 |
| 双向迭代器 | 读写，可以向前向后 |
| 随机访问迭代器 | 可以跳跃访问，支持 `+ n`、`- n` |

今天涉及的容器：

| 容器 | 迭代器类型 |
| --- | --- |
| `vector` | 随机访问迭代器 |
| `deque` | 随机访问迭代器 |
| `list` | 双向迭代器 |
| `set` | 双向迭代器 |

标准算法 `sort` 要求随机访问迭代器，所以：

```cpp
sort(v.begin(), v.end()); // vector 可以
sort(d.begin(), d.end()); // deque 可以
```

`list` 不支持随机访问，因此不能使用标准 `sort`：

```cpp
// sort(l.begin(), l.end()); // 错误
l.sort();                    // 正确
```

## 3. `vector` 基础遍历

头文件：

```cpp
#include <vector>
#include <algorithm>
```

`vector` 是一个模板类：

```cpp
vector<int> v;
```

### 3.1 插入数据

```cpp
vector<int> v;

v.push_back(10);
v.push_back(20);
v.push_back(30);
v.push_back(40);
v.push_back(50);
v.push_back(60);
```

`push_back` 表示尾部插入。

### 3.2 使用迭代器遍历

```cpp
vector<int>::iterator itBegin = v.begin();
vector<int>::iterator itEnd = v.end();

while (itBegin != itEnd)
{
    cout << *itBegin << endl;
    itBegin++;
}
```

常见写法：

```cpp
for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
{
    cout << *it << endl;
}
```

### 3.3 使用 `for_each`

```cpp
void myPrint(int val)
{
    cout << val << endl;
}

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    for_each(v.begin(), v.end(), myPrint);
}
```

`for_each(v.begin(), v.end(), myPrint)` 的底层逻辑可以理解为：

```cpp
for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
{
    myPrint(*it);
}
```

因此，函数参数类型要能接收 `*it` 的类型。

## 4. `vector` 存放自定义类型

### 4.1 存放对象

```cpp
class Person
{
public:
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }

    string m_name;
    int m_age;
};
```

```cpp
void test01()
{
    vector<Person> v;

    Person p1("aaa", 10);
    Person p2("baa", 10);
    Person p3("caa", 10);
    Person p4("daa", 10);
    Person p5("eaa", 10);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);

    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << (*it).m_name << "\t" << (*it).m_age << endl;
    }
}
```

也可以写成：

```cpp
cout << it->m_name << "\t" << it->m_age << endl;
```

### 4.2 `for_each` 打印对象

```cpp
void myPrint(const Person& p)
{
    cout << p.m_name << "\t" << p.m_age << endl;
}

for_each(v.begin(), v.end(), myPrint);
```

参数写成 `const Person&` 可以避免拷贝，并且表示函数不修改对象。

### 4.3 存放对象指针

```cpp
void test02()
{
    vector<Person*> v;

    Person p1("aaa", 10);
    Person p2("baa", 10);
    Person p3("caa", 10);
    Person p4("daa", 10);
    Person p5("eaa", 10);

    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    v.push_back(&p5);

    for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->m_name << "\t" << (*it)->m_age << endl;
    }
}
```

类型关系：

```text
it       是 vector<Person*>::iterator
*it      是 Person*
(*it)->  通过 Person* 访问成员
```

如果容器中存的是局部对象地址，不能在对象生命周期结束后继续使用这些指针。

## 5. 容器嵌套容器

`vector<vector<int>>` 表示外层 `vector` 中的每个元素都是一个 `vector<int>`。

```cpp
void myPrint(const vector<int>& v)
{
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test01()
{
    vector<vector<int>> v;

    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;

    for (int i = 0; i < 4; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 1);
        v3.push_back(i + 2);
        v4.push_back(i + 3);
    }

    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);

    for_each(v.begin(), v.end(), myPrint);
}
```

外层容器：

```cpp
vector<vector<int>> v;
```

外层每个元素：

```cpp
vector<int>
```

`for_each` 底层是：

```cpp
myPrint(*it);
```

所以 `myPrint` 的参数类型应为 `vector<int>` 或 `const vector<int>&`。

## 6. `string` 容器

`string` 是一个类，内部封装了字符序列，可以理解为封装了 `char*` 的容器。

头文件：

```cpp
#include <string>
```

### 6.1 字符串赋值

常用函数：

```cpp
string& operator=(const char* s);
string& operator=(const string& s);
string& operator=(char c);
string& assign(const char* s);
string& assign(const char* s, int n);
string& assign(const string& s);
string& assign(int n, char c);
```

示例：

```cpp
void test01()
{
    string str1 = "helloworld";
    string str2 = str1;

    string str3;
    str3 = 'a';

    string str4;
    str4.assign("helloworld");

    string str5;
    str5.assign("helloworld", 5);

    string str6;
    str6.assign(str5);

    string str7;
    str7.assign(10, 'w');
}
```

说明：

- `assign("helloworld", 5)` 取前 5 个字符。
- `assign(10, 'w')` 得到 10 个字符 `w`。

### 6.2 字符串拼接

常用函数：

```cpp
string& operator+=(const char* str);
string& operator+=(const char c);
string& operator+=(const string& str);
string& append(const char* s);
string& append(const char* s, int n);
string& append(const string& s);
string& append(const string& s, int pos, int n);
```

示例：

```cpp
void test01()
{
    string str1 = "我";
    str1 += "爱玩游戏";
    str1 += ':';

    string str2 = "地下城";
    str1 += str2;

    string str3 = "I";
    str3.append(" LOVE");
    str3.append("023415230156410.015", 10);

    string str4 = "abcdef";
    str3.append(str4, 1, 3); // 从下标 1 开始取 3 个字符，即 bcd
}
```

### 6.3 查找和替换

常用函数：

```cpp
int find(const string& str, int pos = 0) const;
int find(const char* s, int pos = 0) const;
int find(const char* s, int pos, int n) const;
int find(const char c, int pos = 0) const;

int rfind(const string& str, int pos = npos) const;
int rfind(const char* s, int pos = npos) const;
int rfind(const char* s, int pos, int n) const;
int rfind(const char c, int pos = 0) const;

string& replace(int pos, int n, const string& str);
string& replace(int pos, int n, const char* s);
```

示例：

```cpp
void test01()
{
    string str1 = "abcdefg";

    cout << str1.find("de") << endl;
    cout << str1.rfind("de") << endl;
}
```

区别：

- `find` 从左往右查找第一次出现的位置。
- `rfind` 从右往左查找最后一次出现的位置。
- 找不到返回 `string::npos`。

判断是否找到：

```cpp
if (str.find("de") != string::npos)
{
    cout << "找到了" << endl;
}
```

替换：

```cpp
string str = "abcdefg";
str.replace(1, 3, "111");
cout << str << endl; // a111efg
```

### 6.4 字符串比较

常用函数：

```cpp
int compare(const string& s) const;
int compare(const char* s) const;
```

返回值：

| 返回值 | 含义 |
| --- | --- |
| `0` | 两个字符串相等 |
| 正数 | 当前字符串大于参数字符串 |
| 负数 | 当前字符串小于参数字符串 |

示例：

```cpp
void test01()
{
    string str1 = "helloworld";
    string str2 = "hello";

    if (str1.compare(str2) == 0)
    {
        cout << "str1 = str2" << endl;
    }
}
```

### 6.5 字符存取

常用函数：

```cpp
char& operator[](int n);
char& at(int n);
```

示例：

```cpp
void test01()
{
    string str = "hello";

    for (int i = 0; i < str.size(); i++)
    {
        cout << str[i] << endl;
        cout << str.at(i) << endl;
    }
}
```

区别：

- `[]` 不做越界检查。
- `at()` 做越界检查，越界会抛异常。

### 6.6 插入和删除

常用函数：

```cpp
string& insert(int pos, const char* s);
string& insert(int pos, const string& str);
string& insert(int pos, int n, char c);
string& erase(int pos, int n = npos);
```

示例：

```cpp
void test01()
{
    string str1 = "hello";

    cout << str1.insert(1, "333") << endl; // h333ello
    cout << str1.erase(1, 3) << endl;      // hello
}
```

### 6.7 子串

常用函数：

```cpp
string substr(int pos, int n = npos) const;
```

示例：

```cpp
void test01()
{
    string str = "abc";
    cout << str.substr(1, 2) << endl; // bc

    string str2 = "zhangsan@sina.com";
    string username = str2.substr(0, str2.find("@"));
    cout << username << endl; // zhangsan
}
```

`substr(pos, n)` 表示从 `pos` 开始取 `n` 个字符。  
如果省略 `n`，默认取到字符串末尾。

## 7. `vector` 容器详解

`vector` 是单端数组，可以动态扩展。

特点：

- 支持随机访问。
- 尾部插入、尾部删除效率高。
- 头部和中间插入删除效率低。
- 迭代器支持随机访问。

动态扩展的过程：

```text
原空间不够
申请更大的新空间
把原数据拷贝或移动到新空间
释放原空间
更新内部指针
```

因此 `vector` 扩容后，原来保存的迭代器、指针、引用可能失效。

### 7.1 构造函数

常用函数：

```cpp
vector<T> v;
vector(v.begin(), v.end());
vector(n, elem);
vector(const vector& vec);
```

示例：

```cpp
void printVector(const vector<int>& v)
{
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << endl;
    }
}

void test01()
{
    vector<int> v1;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    vector<int> v2(v1.begin(), v1.end());
    vector<int> v3(10, 100);
    vector<int> v4(v2);
}
```

同一作用域中不能重复定义同名变量：

```cpp
vector<int> v3(10, 100);
vector<int> v4(v2);
```

### 7.2 赋值

常用函数：

```cpp
vector& operator=(const vector& vec);
assign(beg, end);
assign(n, elem);
```

示例：

```cpp
void test01()
{
    vector<int> v1;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    vector<int> v2;
    v2 = v1;

    vector<int> v3;
    v3.assign(v2.begin(), v2.end());

    vector<int> v4;
    v4.assign(10, 100);
}
```

### 7.3 容量和大小

常用函数：

```cpp
empty();
capacity();
size();
resize(int num);
resize(int num, elem);
```

区别：

| 函数 | 含义 |
| --- | --- |
| `empty()` | 判断容器是否为空 |
| `capacity()` | 容器容量，即已分配空间最多能容纳多少元素 |
| `size()` | 容器当前元素个数 |
| `resize(num)` | 重新指定元素个数，变长时默认填充 |
| `resize(num, elem)` | 重新指定元素个数，变长时用 `elem` 填充 |

示例：

```cpp
void test01()
{
    vector<int> v1;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    if (v1.empty())
    {
        cout << "v1为空" << endl;
    }

    cout << v1.capacity() << endl;
    cout << v1.size() << endl;

    v1.resize(15);      // 新位置默认填 0
    v1.resize(20, 100); // 新位置填 100
    v1.resize(3);       // 末尾超出长度的元素被删除
}
```

`resize` 改变 `size`。  
`reserve` 只预留 `capacity`，不改变 `size`。

### 7.4 插入和删除

常用函数：

```cpp
push_back(ele);
pop_back();
insert(const_iterator pos, ele);
insert(const_iterator pos, int count, ele);
erase(const_iterator pos);
erase(const_iterator start, const_iterator end);
clear();
```

示例：

```cpp
void test01()
{
    vector<int> v1;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    v1.pop_back();
    v1.insert(v1.begin(), 3, 100);
    v1.erase(v1.begin(), v1.begin() + 3);
    v1.clear();
}
```

区间规则：

```cpp
[start, end)
```

包含 `start`，不包含 `end`。

### 7.5 数据存取

常用函数：

```cpp
at(int idx);
operator[];
front();
back();
```

示例：

```cpp
void test01()
{
    vector<int> v1;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << endl;
        cout << v1.at(i) << endl;
    }

    cout << v1.front() << endl;
    cout << v1.back() << endl;
}
```

区别：

- `[]` 不做越界检查。
- `at()` 做越界检查。
- `front()` 返回第一个元素。
- `back()` 返回最后一个元素。

### 7.6 互换 `swap`

基本使用：

```cpp
void test01()
{
    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    vector<int> v2;
    for (int i = 10; i > 0; i--)
    {
        v2.push_back(i);
    }

    v1.swap(v2);
}
```

`swap` 会交换两个容器管理的数据。

### 7.7 使用 `swap` 收缩内存空间

`resize` 变短后，`size` 会变小，但 `capacity` 通常不会立刻变小。

```cpp
void test02()
{
    vector<int> v;

    for (int i = 0; i < 1000000; i++)
    {
        v.push_back(i);
    }

    cout << v.capacity() << endl;
    cout << v.size() << endl;

    v.resize(3);

    cout << v.capacity() << endl;
    cout << v.size() << endl;

    vector<int>(v).swap(v);

    cout << v.capacity() << endl;
    cout << v.size() << endl;
}
```

`vector<int>(v).swap(v)` 的过程：

1. `vector<int>(v)` 通过拷贝构造创建临时匿名对象。
2. 临时对象只保存当前有效元素，容量通常接近当前 `size`。
3. 临时对象和 `v` 交换底层空间。
4. 当前语句结束后，临时匿名对象析构。
5. 原来 `v` 中的大量冗余空间被释放。

核心理解：

```text
swap 交换的是容器内部管理的资源，不只是一个个交换元素。
```

### 7.8 预留空间 `reserve`

常用函数：

```cpp
reserve(int len);
```

作用：

- 预留 `len` 个元素的容量。
- 预留空间不初始化。
- 元素不可以直接访问。
- 减少动态扩容次数。

示例：

```cpp
void test01()
{
    vector<int> v;
    v.reserve(100000);

    int num = 0;
    int* p = NULL;

    for (int i = 0; i < 100000; i++)
    {
        v.push_back(i);

        if (p != &v[0])
        {
            p = &v[0];
            num++;
        }
    }

    cout << num << endl;
}
```

`&v[0]` 表示底层数组首元素地址。  
如果地址变化，说明发生过重新分配。

错误写法：

```cpp
vector<int> v;
v.reserve(10);
v[0] = 100; // 错误，size 仍然是 0
```

正确写法：

```cpp
vector<int> v;
v.reserve(10);
v.push_back(100);
```

## 8. `deque` 容器

`deque` 是双端数组，可以对头端和尾端进行插入删除操作。

头文件：

```cpp
#include <deque>
```

### 8.1 `deque` 和 `vector` 的区别

| 对比 | `vector` | `deque` |
| --- | --- | --- |
| 结构 | 单端数组 | 双端数组 |
| 头部插入删除 | 效率低 | 效率较高 |
| 尾部插入删除 | 效率高 | 效率高 |
| 随机访问 | 快 | 支持，但通常比 `vector` 慢 |
| 容量接口 | 有 `capacity()` | 没有常用 `capacity()` |

`vector` 访问元素速度通常比 `deque` 快。  
`deque` 对头部插入删除速度通常比 `vector` 快。

### 8.2 构造

```cpp
deque<T> deqT;
deque(beg, end);
deque(n, elem);
deque(const deque& deq);
```

示例：

```cpp
deque<int> d1;

for (int i = 0; i < 10; i++)
{
    d1.push_back(i);
}

deque<int> d2(d1.begin(), d1.end());
deque<int> d3(10, 100);
deque<int> d4(d3);
```

### 8.3 赋值

常用函数：

```cpp
deque& operator=(const deque& deq);
assign(beg, end);
assign(n, elem);
```

示例：

```cpp
deque<int> d1;

for (int i = 0; i < 10; i++)
{
    d1.push_back(i);
}

deque<int> d2;
d2 = d1;

deque<int> d3;
d3.assign(d1.begin(), d1.end());

deque<int> d4;
d4.assign(10, 100);
```

### 8.4 大小操作

常用函数：

```cpp
empty();
size();
resize(num);
resize(num, elem);
```

`deque` 没有 `capacity()`。

### 8.5 插入和删除

两端插入删除：

```cpp
push_back(elem);
push_front(elem);
pop_back();
pop_front();
```

指定位置操作：

```cpp
insert(pos, elem);
insert(pos, n, elem);
insert(pos, beg, end);
clear();
erase(beg, end);
erase(pos);
```

示例：

```cpp
void test01()
{
    deque<int> d1;

    for (int i = 0; i < 10; i++)
    {
        d1.push_back(i);
        d1.push_front(i);
    }

    d1.pop_back();
    d1.pop_front();

    d1.insert(d1.begin(), 1000);
    d1.insert(d1.begin(), 2, 1000);

    d1.erase(d1.begin());
    d1.clear();
}
```

### 8.6 数据存取

常用函数：

```cpp
at(int idx);
operator[];
front();
back();
```

示例：

```cpp
void test01()
{
    deque<int> d1;

    for (int i = 0; i < 10; i++)
    {
        d1.push_back(i);
    }

    for (int i = 0; i < d1.size(); i++)
    {
        cout << d1[i] << " ";
        cout << d1.at(i) << " ";
    }

    cout << endl;
    cout << d1.front() << endl;
    cout << d1.back() << endl;
}
```

### 8.7 排序

`deque` 支持随机访问迭代器，因此可以使用标准算法 `sort`。

```cpp
void test01()
{
    deque<int> d1;

    d1.push_back(100);
    d1.push_back(600);
    d1.push_back(300);
    d1.push_back(900);

    sort(d1.begin(), d1.end()); // 默认从小到大
}
```

支持随机访问迭代器的容器，可以使用标准 `sort` 排序。  
例如 `vector`、`deque`。

## 9. 案例：评委打分

需求：

1. 创建选手，存入 `vector<Person>`。
2. 每名选手有 10 个评委打分。
3. 分数存入 `deque<int>`。
4. 排序后去掉最高分和最低分。
5. 剩余分数求平均值。
6. 平均分写入选手对象。

### 9.1 选手类

```cpp
class Person
{
public:
    Person(string name, int score)
    {
        this->m_name = name;
        this->ave_score = score;
    }

    string m_name;
    int ave_score;
};
```

### 9.2 创建选手

```cpp
void createPerson(vector<Person>& v)
{
    string str = "ABCDE";

    for (int i = 0; i < 5; i++)
    {
        string name = "选手";
        name += str[i];

        Person p(name, 0);
        v.push_back(p);
    }
}
```

### 9.3 设置分数

```cpp
void setScore(vector<Person>& v)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < v.size(); i++)
    {
        deque<int> d;

        for (int j = 0; j < 10; j++)
        {
            int score = rand() % 41 + 60; // 60 到 100
            d.push_back(score);
            cout << score << " ";
        }

        cout << endl;

        sort(d.begin(), d.end());

        d.pop_back();  // 去掉最高分
        d.pop_front(); // 去掉最低分

        int sum = 0;
        for (int j = 0; j < d.size(); j++)
        {
            sum += d[j];
            cout << d[j] << " ";
        }

        cout << endl;

        v[i].ave_score = sum / d.size();
        cout << v[i].m_name << "\t" << v[i].ave_score << endl;
    }
}
```

头文件：

```cpp
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cstdlib>
```

循环变量不要重复使用同一个名字，外层用 `i`，内层用 `j`，可读性更好。

## 10. `stack` 容器

`stack` 是栈，特点是先进后出。

```text
先入栈的后出栈
后入栈的先出栈
```

头文件：

```cpp
#include <stack>
```

常用接口：

```cpp
stack<T> stk;
stack(const stack& stk);

stack& operator=(const stack& stk);

push(elem);
pop();
top();

empty();
size();
```

示例：

```cpp
void test01()
{
    stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);

    if (s.empty())
    {
        cout << "栈为空" << endl;
    }

    cout << s.size() << endl;
    cout << s.top() << endl;

    s.pop();
}
```

注意：

- `top()` 返回栈顶元素。
- `pop()` 删除栈顶元素，但不返回被删除的元素。
- `stack` 只能访问栈顶，不允许遍历。

## 11. `queue` 容器

`queue` 是队列，特点是先进先出。

```text
先入队的先出队
后入队的后出队
```

头文件：

```cpp
#include <queue>
```

常用接口：

```cpp
queue<T> que;
queue(const queue& que);

queue& operator=(const queue& que);

push(elem);
pop();
back();
front();

empty();
size();
```

示例：

```cpp
class Person
{
public:
    Person(string name, int age)
    {
        this->m_age = age;
        this->m_name = name;
    }

    int m_age;
    string m_name;
};

void test01()
{
    queue<Person> q;

    Person p1("tangseng", 18);
    Person p2("shaseng", 18);
    Person p3("sunwukong", 18);
    Person p4("bailongma", 18);
    Person p5("xiaolongnv", 18);

    q.push(p1);
    q.push(p2);
    q.push(p3);
    q.push(p4);
    q.push(p5);

    if (!q.empty())
    {
        cout << q.front().m_name << "\t" << q.front().m_age << endl;
        cout << q.back().m_name << "\t" << q.back().m_age << endl;
    }

    cout << q.size() << endl;
}
```

注意：

- `front()` 返回队头元素。
- `back()` 返回队尾元素。
- `pop()` 删除队头元素。
- `queue` 只有队头和队尾可以访问，不允许遍历。

## 12. `list` 容器

`list` 是双向链表容器。

头文件：

```cpp
#include <list>
```

特点：

- 可以对任意位置进行快速插入和删除。
- 插入删除不会造成大量元素移动。
- 不会像 `vector` 那样因为预留空间造成较多空间浪费。
- 遍历速度相对慢。
- 每个节点需要额外保存前后指针，占用空间较大。
- 不支持随机访问。

### 12.1 构造

常用函数：

```cpp
list<T> lst;
list(beg, end);
list(n, elem);
list(const list& lst);
```

示例：

```cpp
void test01()
{
    list<int> l;

    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    l.push_back(50);
    l.push_back(60);

    list<int> l2(l);
    list<int> l3(l.begin(), l.end());
    list<int> l4(10, 1000);
}
```

### 12.2 赋值和交换

常用函数：

```cpp
assign(beg, end);
assign(n, elem);
list& operator=(const list& lst);
swap(lst);
```

示例：

```cpp
void test01()
{
    list<int> l;

    l.push_back(10);
    l.push_back(20);
    l.push_back(30);

    list<int> l2 = l;

    list<int> l3;
    l3.assign(l2.begin(), l2.end());

    list<int> l4;
    l4.assign(10, 100);

    l3.swap(l4);
}
```

### 12.3 大小操作

常用函数：

```cpp
size();
empty();
resize(num);
resize(num, elem);
```

规则：

- 容器变长：新位置默认填充，或用指定元素填充。
- 容器变短：末尾超出长度的元素被删除。

### 12.4 插入和删除

常用函数：

```cpp
push_back(elem);
pop_back();
push_front(elem);
pop_front();

insert(pos, elem);
insert(pos, n, elem);
insert(pos, beg, end);

clear();
erase(beg, end);
erase(pos);
remove(elem);
```

示例：

```cpp
void test01()
{
    list<int> l;

    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);

    l.push_front(100);
    l.push_front(300);

    l.pop_back();
    l.pop_front();

    l.insert(l.begin(), 1000);
    l.insert(l.end(), 3, 1000);

    l.remove(1000);
}
```

`remove(elem)` 删除容器中所有值等于 `elem` 的元素。

### 12.5 数据存取

常用函数：

```cpp
front();
back();
```

`list` 内存空间不连续，因此不存在：

```cpp
operator[]
at()
```

`list` 迭代器支持双向访问：

```cpp
++it;
--it;
```

不支持随机访问：

```cpp
// it + 5; // 错误
```

### 12.6 反转和排序

常用函数：

```cpp
reverse();
sort();
```

示例：

```cpp
bool myCompare(int v1, int v2)
{
    return v1 > v2;
}

void test01()
{
    list<int> l;

    l.push_back(10);
    l.push_back(40);
    l.push_back(20);
    l.push_back(80);

    l.reverse();

    l.sort();          // 默认从小到大
    l.sort(myCompare); // 从大到小
}
```

所有不支持随机访问迭代器的容器，不可以使用标准排序算法 `sort`。  
不支持随机访问迭代器的容器，如果需要排序，通常会提供适合自身结构的成员函数。`list` 使用 `list::sort()`。

### 12.7 `list` 自定义类型排序

```cpp
class Person
{
public:
    Person(string name, int age, int height)
    {
        this->m_age = age;
        this->m_height = height;
        this->m_name = name;
    }

    string m_name;
    int m_age;
    int m_height;
};
```

排序规则：年龄升序；年龄相同时，身高升序。

```cpp
bool myCompare(const Person& p1, const Person& p2)
{
    if (p1.m_age != p2.m_age)
    {
        return p1.m_age < p2.m_age;
    }
    else
    {
        return p1.m_height < p2.m_height;
    }
}
```

比较函数的含义：

```text
如果 p1 应该排在 p2 前面，返回 true。
```

因此：

```cpp
return p1.m_age < p2.m_age;
```

表示年龄小的排前面，即从小到大。

完整使用：

```cpp
void test01()
{
    list<Person> l;

    l.push_back(Person("liubei", 24, 180));
    l.push_back(Person("guanyu", 20, 190));
    l.push_back(Person("caocao", 23, 183));
    l.push_back(Person("zhangfei", 20, 172));
    l.push_back(Person("zhugeliang", 25, 189));
    l.push_back(Person("zhouyu", 20, 180));

    l.sort(myCompare);
}
```

比较函数应返回 `bool`。

`"\t"` 是制表符，会把后续文本移动到下一个预设对齐位置，通常相当于跳到 8 个字符宽度的对齐点。

## 13. `set` / `multiset` 容器

头文件：

```cpp
#include <set>
```

`set` / `multiset` 属于有序关联式容器，常见底层结构是红黑树。

特点：

- 插入时自动排序。
- `set` 不允许重复元素。
- `multiset` 允许重复元素。
- 插入使用 `insert`，没有 `push_back`。

“插入时自动排序”指的是 `set` / `multiset` 这类有序关联容器，不是所有容器。

### 13.1 构造和赋值

常用函数：

```cpp
set<T> st;
set(const set& st);
set& operator=(const set& st);
```

示例：

```cpp
void test01()
{
    set<int> s1;

    s1.insert(10);
    s1.insert(60);
    s1.insert(40);
    s1.insert(90);
    s1.insert(1000);
    s1.insert(789);
    s1.insert(488);

    set<int> s2(s1);

    set<int> s3;
    s3 = s2;
}
```

遍历：

```cpp
void printSet(const set<int>& s)
{
    for (set<int>::const_iterator it = s.begin(); it != s.end(); it++)
    {
        cout << *it << endl;
    }
}
```

### 13.2 大小和交换

常用函数：

```cpp
size();
empty();
swap(st);
```

`set` 中的数据不能重复，因此没有 `resize`。

### 13.3 插入和删除

常用函数：

```cpp
insert(elem);
clear();
erase(pos);
erase(beg, end);
erase(elem);
```

示例：

```cpp
void test01()
{
    set<int> s1;

    s1.insert(10);
    s1.insert(80);
    s1.insert(30);
    s1.insert(40);
    s1.insert(5);

    s1.erase(s1.begin());
    s1.erase(30);
    s1.clear();
}
```

删除某个位置的后一个元素时，可以拆开写：

```cpp
set<int>::iterator it = s1.begin();
++it;
s1.erase(it);
```

### 13.4 查找和统计

常用函数：

```cpp
find(key);
count(key);
```

`find(key)`：

- 找到返回该元素迭代器。
- 找不到返回 `set.end()`。

示例：

```cpp
void test01()
{
    set<int> s1;

    s1.insert(10);
    s1.insert(80);
    s1.insert(30);
    s1.insert(40);
    s1.insert(5);

    set<int>::const_iterator it = s1.find(5);

    if (it == s1.end())
    {
        cout << "没找到" << endl;
    }
    else
    {
        cout << "找到了：" << *it << endl;
    }
}
```

`count(key)`：

- 对 `set`，结果只能是 `0` 或 `1`。
- 对 `multiset`，结果可以大于 `1`。

### 13.5 `set` 和 `multiset` 的区别

| 对比 | `set` | `multiset` |
| --- | --- | --- |
| 是否允许重复 | 不允许 | 允许 |
| 插入是否检查重复 | 检查 | 不阻止重复 |
| `insert` 返回值 | `pair<iterator, bool>` | 迭代器 |

`set` 插入数据时会返回插入结果：

```cpp
void test01()
{
    set<int> s;

    pair<set<int>::iterator, bool> ret = s.insert(10);

    if (ret.second)
    {
        cout << "第一次插入成功" << endl;
    }

    ret = s.insert(10);

    if (ret.second)
    {
        cout << "第二次插入成功" << endl;
    }
    else
    {
        cout << "第二次插入失败，元素重复" << endl;
    }
}
```

`pair<set<int>::iterator, bool>` 中：

- `first` 是迭代器。
- `second` 是布尔值，表示插入是否成功。

`multiset` 允许重复：

```cpp
void test02()
{
    multiset<int> s1;

    s1.insert(10);
    s1.insert(10);
    s1.insert(10);
    s1.insert(40);
    s1.insert(5);
}
```

### 13.6 `pair` 对组

`pair` 用于把两个数据组合成一组。

```cpp
void test01()
{
    pair<string, int> p("Tom", 18);
    cout << p.first << "\t" << p.second << endl;

    pair<string, int> p2 = make_pair("Jerry", 18);
}
```

`first` 表示第一个数据。  
`second` 表示第二个数据。

### 13.7 `set` 内置类型排序

`set` 默认从小到大排序。

默认排序规则来自 `set` 的第二个模板参数：

```cpp
template
<
    class T,
    class Compare = std::less<T>,
    class Allocator = std::allocator<T>
>
class set;
```

其中：

```cpp
Compare = std::less<T>
```

表示默认使用小于比较，即从小到大排序。

自定义从大到小排序：

```cpp
class MyCompare
{
public:
    bool operator()(int v1, int v2) const
    {
        return v1 > v2;
    }
};

void test01()
{
    set<int, MyCompare> s2;

    s2.insert(10);
    s2.insert(20);
    s2.insert(30);
    s2.insert(40);
    s2.insert(50);

    for (set<int, MyCompare>::const_iterator it = s2.begin(); it != s2.end(); it++)
    {
        cout << *it << " ";
    }
}
```

`MyCompare` 是仿函数。因为它重载了 `operator()`，所以对象可以像函数一样调用：

```cpp
MyCompare comp;
comp(10, 20);
```

`set` 内部保存比较器对象，在需要比较两个元素 `a`、`b` 时调用：

```cpp
comp(a, b);
```

在某些标准库实现中，内部比较器成员可能类似 `_M_comp`，排序和查找时会出现类似：

```cpp
_M_comp(a, b);
```

只要编译器看到比较器对象能被这样调用，模板就能实例化通过。

### 13.8 使用函数指针作为 `set` 排序规则

除了仿函数，函数指针也可以作为比较规则。

```cpp
bool myCompare(int v1, int v2)
{
    return v1 > v2;
}

void test01()
{
    set<int, bool(*)(int, int)> s3(myCompare);
}
```

`bool(*)(int, int)` 是函数指针类型：

```text
指向一个函数；
函数参数是两个 int；
函数返回值是 bool。
```

函数名 `myCompare` 在很多表达式中可以自动转换为函数指针。

`set<int, bool(*)(int, int)> s3(myCompare);` 的含义：

```text
set 中元素类型是 int；
比较器类型是 bool(*)(int, int)；
实际使用 myCompare 这个函数作为比较规则。
```

函数指针也可以用函数调用语法：

```cpp
comp(a, b);
```

它等价于：

```cpp
(*comp)(a, b);
```

因此仿函数对象和函数指针都能满足 `set` 对比较器的要求：

```cpp
comp(a, b)
```

模板不要求比较器一定是某个固定类型，只要求传入的比较器能被合法调用，并返回可用于判断的结果。

### 13.9 `set` 存放自定义类型

自定义类型必须指定排序规则。

```cpp
class Person
{
public:
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }

    string m_name;
    int m_age;
};
```

比较规则：

```cpp
class ComparePerson
{
public:
    bool operator()(const Person& p1, const Person& p2) const
    {
        return p1.m_age > p2.m_age;
    }
};
```

使用：

```cpp
void test01()
{
    set<Person, ComparePerson> s;

    Person p1("liubei", 24);
    Person p2("guanyu", 28);
    Person p3("zhangfei", 25);
    Person p4("zhaoyun", 21);

    s.insert(p1);
    s.insert(p2);
    s.insert(p3);
    s.insert(p4);

    for (set<Person, ComparePerson>::const_iterator it = s.begin(); it != s.end(); it++)
    {
        cout << it->m_name << "\t" << it->m_age << endl;
    }
}
```

比较规则不仅决定排序，也决定 `set` 判断元素是否重复。

如果比较规则只比较年龄：

```cpp
return p1.m_age > p2.m_age;
```

那么两个年龄相同但姓名不同的人，在 `set` 中可能被认为是等价元素。  
因为：

```cpp
comp(p1, p2) == false
comp(p2, p1) == false
```

这表示二者没有先后关系，`set` 会把它们看成同一类元素。

如果需要年龄相同也能按姓名区分：

```cpp
class ComparePerson
{
public:
    bool operator()(const Person& p1, const Person& p2) const
    {
        if (p1.m_age != p2.m_age)
        {
            return p1.m_age > p2.m_age;
        }

        return p1.m_name < p2.m_name;
    }
};
```

排序规则：

```text
先按年龄降序；
年龄相同，再按姓名升序。
```

比较函数要满足严格弱序，不能写出前后矛盾的规则。

## 14. 容器选择速查

| 需求 | 推荐容器 |
| --- | --- |
| 经常尾部插入，频繁按下标访问 | `vector` |
| 头尾都经常插入删除 | `deque` |
| 经常中间插入删除，不需要下标访问 | `list` |
| 后进先出 | `stack` |
| 先进先出 | `queue` |
| 自动排序且不允许重复 | `set` |
| 自动排序且允许重复 | `multiset` |

迭代器能力：

| 容器 | 迭代器能力 | 能否使用标准 `sort` |
| --- | --- | --- |
| `vector` | 随机访问 | 可以 |
| `deque` | 随机访问 | 可以 |
| `list` | 双向 | 不可以，用 `list::sort()` |
| `set` | 双向 | 不需要，自动有序 |
| `stack` | 不提供遍历迭代器 | 不可以 |
| `queue` | 不提供遍历迭代器 | 不可以 |

访问方式：

| 容器 | `[]` | `at()` | `front()` | `back()` |
| --- | --- | --- | --- | --- |
| `string` | 可以 | 可以 | 可以 | 可以 |
| `vector` | 可以 | 可以 | 可以 | 可以 |
| `deque` | 可以 | 可以 | 可以 | 可以 |
| `list` | 不可以 | 不可以 | 可以 | 可以 |
| `stack` | 不可以 | 不可以 | 不适用 | 不适用 |
| `queue` | 不可以 | 不可以 | 可以 | 可以 |
| `set` | 不可以 | 不可以 | 不常用 | 不常用 |
