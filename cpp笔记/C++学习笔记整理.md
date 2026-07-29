# C++ 学习笔记整理

> 来源：`text.cpp` 中的注释和示例代码。  
> 整理方式：按学习顺序归类，保留原有知识点，代码改成更容易单独阅读的小示例；同时把几个容易踩坑的地方补上说明。

## 目录

1. C++ 程序基础结构
2. 内存分区模型与 `new` / `delete`
3. 引用
4. 函数进阶：默认参数、占位参数、函数重载
5. 类和对象：封装与访问权限
6. 成员属性私有化
7. 类的分文件编写
8. 构造函数、析构函数与拷贝构造
9. 深拷贝与浅拷贝
10. 初始化列表与对象成员
11. 静态成员
12. 类对象模型与 `this` 指针
13. `const` 成员函数、常对象与 `mutable`
14. 友元
15. 运算符重载
16. 继承
17. 多态
18. 多态综合案例：电脑组装
19. 易错点速查

## 1. C++ 程序基础结构

常见头部：

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
```

说明：

- `#include <iostream>`：输入输出，如 `cout`、`cin`。
- `#include <string>`：使用 `string` 类型。
- `using namespace std;`：可以直接写 `cout`、`string`，不用写 `std::cout`、`std::string`。
- `_CRT_SECURE_NO_WARNINGS`：Visual Studio 中用于关闭某些 C 风格函数的安全警告。

建议：学习阶段可以使用 `using namespace std;`，但工程代码中更推荐写 `std::cout`、`std::string`，避免命名冲突。

## 2. 内存分区模型与 `new` / `delete`

C++ 程序运行时常被讲成四个主要区域：

| 区域 | 存放内容 | 生命周期 |
| --- | --- | --- |
| 代码区 | 函数编译后的二进制指令 | 由操作系统管理，只读、共享 |
| 全局区/静态区 | 全局变量、静态变量、全局常量、字符串常量等 | 程序结束后由操作系统释放 |
| 栈区 | 函数参数、局部变量等 | 编译器自动分配和释放 |
| 堆区 | `new` 申请的内存 | 程序员手动 `delete`，否则通常到程序结束才由系统回收 |

注意：这是一种常用教学模型，具体实现由编译器、操作系统、平台决定，C++ 标准本身不强制规定这些名字。

### 2.1 全局变量、静态变量、局部变量

```cpp
int g_a = 10;              // 全局变量：通常在全局区/静态区
const int c_g_b = 10;      // 全局常量：通常在全局区/静态区

int* func()
{
    int* p = new int(10);  // 堆区
    return p;
}

int main()
{
    static int s_a = 10;   // 静态变量：通常在全局区/静态区
    int a = 10;            // 局部变量：栈区
    const int c_l_a = 10;  // 局部常量：通常仍在栈区或被优化

    cout << "字符串常量的地址: " << &"hello world" << endl;

    int* p = func();
    cout << *p << endl;

    delete p;
    p = nullptr;

    return 0;
}
```

### 2.2 堆区申请和释放

单个对象：

```cpp
int* func()
{
    int* p = new int(10);
    return p;
}

void test01()
{
    int* p = func();
    cout << *p << endl;

    delete p;
    p = nullptr;
}
```

数组：

```cpp
void test02()
{
    int* arr = new int[10];

    for (int i = 0; i < 10; i++)
    {
        arr[i] = 100 + i;
    }

    delete[] arr;
    arr = nullptr;
}
```

记忆规则：

- `new int` 对应 `delete p`。
- `new int[10]` 对应 `delete[] arr`。
- 释放后把指针置为 `nullptr`，可以减少野指针风险。

## 3. 引用

引用可以理解成“给已有变量起别名”。初始化后，引用不能再绑定到别的对象。

```cpp
int a = 10;
int& b = a;   // b 是 a 的引用

b = 20;       // 修改 b 等价于修改 a
cout << a;    // 20
```

从实现角度看，很多编译器会把引用实现成类似“指针常量”的东西，例如 `int* const`，但在语言层面引用不是普通指针，使用时更像变量别名。

### 3.1 引用作为函数参数

引用传参可以直接修改实参。

```cpp
void myswap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a = 10;
    int c = 30;

    myswap(a, c);

    cout << a << endl;  // 30
    cout << c << endl;  // 10
}
```

### 3.2 引用作为函数返回值

不要返回局部变量的引用，因为局部变量会在函数结束后销毁。

可以返回静态变量的引用：

```cpp
int& test01()
{
    static int a = 10;
    return a;
}

int main()
{
    test01() = 1000;       // 返回引用，可以作为左值
    cout << test01();      // 1000
}
```

### 3.3 常量引用

常量引用常用于函数形参，防止函数误修改数据。

```cpp
void showvalue(const int& val)
{
    cout << val << endl;
}

int main()
{
    int a = 100;
    showvalue(a);

    const int& ref = 10;
    // 编译器可理解为创建临时变量 int temp = 10，再让 ref 引用它
}
```

## 4. 函数进阶：默认参数、占位参数、函数重载

### 4.1 默认参数

如果函数调用时没有传入参数，就使用默认值。

规则：

- 如果某个形参有默认值，那么它右边的所有形参都必须有默认值。
- 函数声明和函数实现中，只能有一个位置写默认参数，避免歧义。

```cpp
int func(int a, int b = 10, int c = 20)
{
    return a + b + c;
}
```

### 4.2 占位参数

占位参数只有类型没有变量名，也可以有默认值。

```cpp
void func(int a, int)
{
    cout << "占位参数" << endl;
}

void func2(int a, int = 10)
{
    cout << "带默认值的占位参数" << endl;
}
```

### 4.3 函数重载

函数重载：同一个作用域中，函数名相同，但参数列表不同。

满足条件之一即可：

- 参数类型不同。
- 参数个数不同。
- 参数顺序不同。

注意：

- 返回值不能作为函数重载的判断条件。
- 引用参数、`const` 引用参数、默认参数都可能影响重载匹配。

```cpp
void func(int a, int)
{
    cout << "占位参数版本" << endl;
}

void func(int& a)
{
    cout << "int& 版本" << endl;
}

void func(const int& a)
{
    cout << "const int& 版本" << endl;
}

int main()
{
    int a = 10;

    func(10);  // 右值更适合匹配 const int&
    func(a);   // 左值更适合匹配 int&
}
```

## 5. 类和对象：封装与访问权限

封装：把一类事物的属性和行为放到一个类中。

类中的内容统称为成员：

- 成员变量：属性。
- 成员函数：行为、方法。

访问权限：

| 权限 | 类内访问 | 类外访问 | 子类访问 |
| --- | --- | --- | --- |
| `public` | 可以 | 可以 | 可以 |
| `protected` | 可以 | 不可以 | 可以 |
| `private` | 可以 | 不可以 | 不可以直接访问 |

`struct` 默认权限是 `public`，`class` 默认权限是 `private`。

### 5.1 圆类示例

```cpp
const double PI = 3.14;

class Circle
{
public:
    int m_r;

    double calculateZC()
    {
        return 2 * PI * m_r;
    }
};

int main()
{
    Circle c1;
    c1.m_r = 10;

    cout << "圆的周长是: " << c1.calculateZC() << endl;
}
```

### 5.2 学生类示例

```cpp
class Student
{
public:
    string m_number;
    string m_name;

    void setName(string name)
    {
        m_name = name;
    }

    void setNumber(string number)
    {
        m_number = number;
    }

    void showInform()
    {
        cout << "学号是: " << m_number << endl;
        cout << "姓名是: " << m_name << endl;
    }
};
```

### 5.3 访问权限示例

```cpp
class Person
{
public:
    string m_name;

protected:
    string m_car;

private:
    int m_password;

public:
    void func()
    {
        m_name = "张三";
        m_car = "拖拉机";
        m_password = 123456;
    }
};

int main()
{
    Person p1;
    p1.m_name = "李四";

    // p1.m_car = "汽车";       // 类外不能访问 protected
    // p1.m_password = 123456;  // 类外不能访问 private
}
```

## 6. 成员属性私有化

把成员变量设为 `private`，通过公有函数读写，可以：

- 控制读写权限。
- 检测数据有效性。
- 隐藏内部实现。

```cpp
class Person
{
public:
    void setName(string name)
    {
        m_name = name;
    }

    string getName()
    {
        return m_name;
    }

    void setAge(int age)
    {
        if (age < 0 || age > 150)
        {
            cout << "年龄输入有误，输入失败" << endl;
            return;
        }

        m_age = age;
    }

    int getAge()
    {
        return m_age;
    }

    void setIdol(string idol)
    {
        m_idol = idol;
    }

private:
    string m_name;       // 可写可读
    int m_age = 18;      // 可读，写入时检查有效性
    string m_idol;       // 可写不可读
};
```

### 6.1 立方体案例

类内成员函数比较：

```cpp
class Cube
{
public:
    void set(int l, int w, int h)
    {
        m_L = l;
        m_W = w;
        m_H = h;
    }

    int calculateS()
    {
        return 2 * m_L * m_W + 2 * m_H * m_W + 2 * m_H * m_L;
    }

    int calculateV()
    {
        return m_L * m_W * m_H;
    }

    int getL()
    {
        return m_L;
    }

    int getW()
    {
        return m_W;
    }

    int getH()
    {
        return m_H;
    }

    bool isSame(Cube& c2)
    {
        return m_L == c2.getL() && m_W == c2.getW() && m_H == c2.getH();
    }

private:
    int m_L;
    int m_W;
    int m_H;
};
```

全局函数比较：

```cpp
bool isSame(Cube& c1, Cube& c2)
{
    return c1.getL() == c2.getL()
        && c1.getW() == c2.getW()
        && c1.getH() == c2.getH();
}
```

## 7. 类的分文件编写

当类越来越大时，可以拆成头文件和源文件。

例如 `Circle.h`：

```cpp
#pragma once

class Circle
{
public:
    void setR(int r);
    int getR();

private:
    int m_r;
};
```

例如 `Circle.cpp`：

```cpp
#include "Circle.h"

void Circle::setR(int r)
{
    m_r = r;
}

int Circle::getR()
{
    return m_r;
}
```

要点：

- `.h` 文件里通常写类声明。
- `.cpp` 文件里写成员函数实现。
- 实现成员函数时要写作用域：`Circle::setR`。
- `#pragma once` 可以防止头文件被重复包含。

## 8. 构造函数、析构函数与拷贝构造

构造函数用于初始化对象。

规则：

- 没有返回值，不写 `void`。
- 函数名与类名相同。
- 可以有参数，可以重载。
- 创建对象时自动调用，只调用一次。

析构函数用于清理对象。

规则：

- 没有返回值，不写 `void`。
- 函数名与类名相同，前面加 `~`。
- 不可以有参数，不可以重载。
- 对象销毁前自动调用。

```cpp
class Person
{
public:
    Person()
    {
        cout << "Person 无参构造函数调用" << endl;
    }

    Person(int age)
    {
        m_age = age;
        cout << "Person 有参构造函数调用" << endl;
    }

    Person(const Person& p)
    {
        m_age = p.m_age;
        cout << "Person 拷贝构造函数调用" << endl;
    }

    ~Person()
    {
        cout << "析构函数调用" << endl;
    }

    int m_age = 0;
};
```

### 8.1 构造函数调用方式

```cpp
void test01()
{
    Person p1;              // 默认构造，不要写 Person p1();
    Person p2(10);          // 括号法
    Person p3(p2);          // 拷贝构造

    Person p4 = Person(10); // 显式法
    Person p5 = Person(p2); // 显式法调用拷贝构造

    Person(10);             // 匿名对象，本行结束后立即销毁

    Person p6 = 10;         // 隐式转换法，相当于 Person p6(10)
}
```

注意：`Person p1();` 会被编译器理解为函数声明，不是创建对象。

### 8.2 拷贝构造函数调用时机

常见时机：

- 用已经创建好的对象初始化新对象：`Person p2(p1);`
- 函数参数使用值传递：`void func(Person p);`
- 函数返回局部对象时，可能涉及拷贝或移动，也可能被编译器优化。

值传递会创建新对象，因此会调用拷贝构造；引用传递不会创建新对象。

```cpp
void funcByValue(Person p)
{
}

void funcByRef(Person& p)
{
}
```

### 8.3 编译器默认提供的函数

如果你不写，编译器通常会提供：

- 默认构造函数。
- 拷贝构造函数，默认做值拷贝。
- 拷贝赋值运算符，默认做值拷贝。
- 析构函数。

构造相关规则：

- 如果写了有参构造，编译器不再提供默认构造。
- 如果写了拷贝构造，编译器不再提供普通默认构造。
- 如果类中管理堆资源，通常需要自己写拷贝构造、拷贝赋值和析构函数。

## 9. 深拷贝与浅拷贝

浅拷贝：只复制指针地址，两个对象指向同一块堆内存。  
深拷贝：重新在堆区申请空间，把值复制过去，两个对象指向不同内存。

浅拷贝风险：

- 同一块内存被释放两次。
- 其中一个对象释放后，另一个对象里的指针变成野指针。

```cpp
class Person
{
public:
    Person(int age, int height)
    {
        m_age = age;
        m_height = new int(height);
    }

    Person(const Person& p)
    {
        m_age = p.m_age;
        m_height = new int(*p.m_height);
    }

    ~Person()
    {
        if (m_height != nullptr)
        {
            delete m_height;
            m_height = nullptr;
        }
    }

    int m_age;
    int* m_height;
};

void test02()
{
    Person p1(18, 160);
    Person p2(p1);  // 深拷贝，避免两个对象释放同一块内存
}
```

## 10. 初始化列表与对象成员

### 10.1 初始化列表

初始化列表可以直接初始化成员变量。

```cpp
class Person
{
public:
    Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c)
    {
    }

    int m_A;
    int m_B;
    int m_C;
};
```

### 10.2 类对象作为成员

一个类中可以让另一个类的对象作为成员。

```cpp
class Phone
{
public:
    Phone(string pname)
    {
        m_pname = pname;
    }

    string m_pname;
};

class Person
{
public:
    Person(string name, string pname) : m_name(name), m_phone(pname)
    {
    }

    string m_name;
    Phone m_phone;
};

void test01()
{
    Person p("张三", "苹果20 Pro Max");
    cout << p.m_name << "拿着" << p.m_phone.m_pname << "手机" << endl;
}
```

构造和析构顺序：

- 当其他类对象作为本类成员时，先构造成员对象，再构造自身。
- 析构顺序相反：先析构自身，再析构成员对象。
- 多个成员对象的构造顺序由它们在类中的声明顺序决定，不由初始化列表顺序决定。

## 11. 静态成员

静态成员变量：

- 所有对象共享同一份数据。
- 编译阶段分配内存。
- 类内声明，类外初始化。

静态成员函数：

- 可以通过对象调用，也可以通过类名调用。
- 只能直接访问静态成员变量，不能直接访问非静态成员变量。

```cpp
class Person
{
public:
    static void func()
    {
        m_A = 100;
        cout << "static void func 调用" << endl;
    }

    static int m_A;
    int m_C;

private:
    static int m_B;
};

int Person::m_A = 100;
int Person::m_B = 200;

void test01()
{
    Person p;
    cout << p.m_A << endl;

    p.func();
    Person::func();

    Person p2;
    p2.m_A = 200;

    cout << p.m_A << endl;       // 200，说明所有对象共享
    cout << Person::m_A << endl; // 200
}
```

## 12. 类对象模型与 `this` 指针

### 12.1 成员变量与成员函数分开存储

非静态成员变量属于对象。静态成员变量、非静态成员函数、静态成员函数都不存储在每个对象内部。

```cpp
class Person
{
    int m_A;              // 属于对象
    static int m_B;       // 不属于对象
    void func();          // 不属于对象
    static void func2();  // 不属于对象
};
```

空对象也占 1 个字节，用于区分不同空对象的地址。

```cpp
class Empty
{
};

int main()
{
    Empty e;
    cout << sizeof(e) << endl;  // 通常是 1
}
```

### 12.2 `this` 指针

`this` 指针指向被调用成员函数所属的对象。

主要用途：

- 解决成员变量与形参重名。
- 返回对象本身，实现链式调用。

```cpp
class Person
{
public:
    Person(int age)
    {
        this->age = age;
    }

    Person& addAge(Person& p)
    {
        this->age += p.age;
        return *this;
    }

    int age;
};

void test02()
{
    Person p1(10);
    Person p2(18);

    p2.addAge(p1).addAge(p1).addAge(p1);
}
```

为什么链式调用要返回引用：

- 返回 `Person&`：后续调用继续作用在原对象上。
- 返回 `Person`：会返回临时副本，后续调用作用在副本上，原对象不会持续被修改。

### 12.3 空指针调用成员函数

原笔记中有“空指针调用成员函数”的示例。这里要特别注意：通过空指针调用成员函数在 C++ 中属于未定义行为，不推荐依赖。

```cpp
class Person
{
public:
    void showClassName()
    {
        cout << "this is a Person class" << endl;
    }

    void showPersonAge()
    {
        if (this == nullptr)
        {
            return;
        }

        cout << "age = " << this->m_age << endl;
    }

    int m_age;
};
```

虽然某些编译器上 `p->showClassName()` 可能看起来可以运行，但只要 `p` 是空指针，这种调用就不应该写在正常代码中。

## 13. `const` 成员函数、常对象与 `mutable`

普通成员函数里，`this` 的本质类似：

```cpp
Person* const this;
```

也就是 `this` 的指向不能变，但 `this` 指向的对象可以被修改。

`const` 成员函数中，`this` 类似：

```cpp
const Person* const this;
```

也就是不能修改对象中的普通成员变量。

```cpp
class Person
{
public:
    void showPerson() const
    {
        // m_age = 100;  // 错误：const 成员函数不能修改普通成员
        m_C = 100;       // 正确：mutable 成员可以修改
    }

    int m_age;
    int m_A;
    int m_B;
    mutable int m_C;
};

void test02()
{
    const Person p1;

    // p1.m_age = 10;     // 错误：常对象不能修改普通成员
    p1.m_C = 10;          // 正确：mutable 成员可以修改
    p1.showPerson();      // 常对象只能调用 const 成员函数
}
```

## 14. 友元

友元可以让函数或类访问另一个类的私有成员。

常见形式：

```cpp
friend void goodGay(Building* building); // 全局函数做友元
friend class GoodGay;                    // 类做友元
friend void GoodGay::visit();            // 成员函数做友元
```

友元会破坏一定封装性，所以要谨慎使用。

### 14.1 全局函数做友元

```cpp
class Building
{
    friend void goodGay(Building* building);

public:
    Building()
    {
        m_sittingRoom = "客厅";
        m_bedRoom = "卧室";
    }

    string m_sittingRoom;

private:
    string m_bedRoom;
};

void goodGay(Building* building)
{
    cout << "访问: " << building->m_sittingRoom << endl;
    cout << "访问: " << building->m_bedRoom << endl;
}
```

### 14.2 类做友元

```cpp
class Building
{
    friend class GoodGay;

public:
    Building();
    string m_sittingRoom;

private:
    string m_bedRoom;
};

class GoodGay
{
public:
    GoodGay();
    void visit();

private:
    Building* m_building;
};

Building::Building()
{
    m_sittingRoom = "客厅";
    m_bedRoom = "卧室";
}

GoodGay::GoodGay()
{
    m_building = new Building;
}

void GoodGay::visit()
{
    cout << "正在参观: " << m_building->m_sittingRoom << endl;
    cout << "正在参观: " << m_building->m_bedRoom << endl;
}
```

### 14.3 成员函数做友元

```cpp
class Building;

class GoodGay
{
public:
    GoodGay();
    void visit();
    void visit2();

private:
    Building* m_building;
};

class Building
{
    friend void GoodGay::visit();

public:
    Building();
    string m_sittingRoom;

private:
    string m_bedRoom;
};
```

## 15. 运算符重载

运算符重载可以让自定义类型使用类似内置类型的运算符。

注意：

- 不要滥用，语义要自然。
- 运算符重载也可以发生函数重载。
- 部分运算符通常适合写成成员函数，部分适合写成全局函数。

### 15.1 加号运算符重载

成员函数版本本质：

```cpp
p3 = p1.operator+(p2);
```

全局函数版本本质：

```cpp
p3 = operator+(p1, p2);
```

示例：

```cpp
class Person
{
public:
    int m_a;
    int m_b;
};

Person operator+(Person& p1, Person& p2)
{
    Person temp;
    temp.m_a = p1.m_a + p2.m_a;
    temp.m_b = p1.m_b + p2.m_b;
    return temp;
}

Person operator+(Person& p1, int a)
{
    Person temp;
    temp.m_a = p1.m_a + a;
    temp.m_b = p1.m_b;
    return temp;
}
```

### 15.2 左移运算符重载

通常不用成员函数重载 `<<`，因为我们希望写成：

```cpp
cout << p << endl;
```

而不是：

```cpp
p << cout;
```

示例：

```cpp
class Person
{
    friend ostream& operator<<(ostream& out, const Person& p);

public:
    Person(int a, int b)
    {
        m_a = a;
        m_b = b;
    }

private:
    int m_a;
    int m_b;
};

ostream& operator<<(ostream& out, const Person& p)
{
    out << "m_a = " << p.m_a << ", m_b = " << p.m_b;
    return out;
}
```

为什么 `ostream&` 要传引用、返回引用：

- `cout` 是 `ostream` 对象，不能随便拷贝。
- 返回引用才能继续链式调用：`cout << p << endl;`

### 15.3 递增运算符 `++` 重载

前置递增返回引用，后置递增返回值。

```cpp
class MyInteger
{
    friend ostream& operator<<(ostream& out, const MyInteger& value);

public:
    MyInteger()
    {
        m_num = 0;
    }

    MyInteger& operator++()
    {
        ++m_num;
        return *this;
    }

    MyInteger operator++(int)
    {
        MyInteger temp = *this;
        m_num++;
        return temp;
    }

private:
    int m_num;
};

ostream& operator<<(ostream& out, const MyInteger& value)
{
    out << value.m_num;
    return out;
}
```

要点：

- `operator++()`：前置 `++`。
- `operator++(int)`：后置 `++`，其中 `int` 是占位参数，用于区分前置和后置。
- 后置递增返回的是临时旧值，函数结束后临时变量会销毁，所以不能返回局部变量引用。

### 15.4 赋值运算符重载

如果类中有堆区资源，默认赋值运算符只做浅拷贝，容易造成重复释放。

```cpp
class Person
{
public:
    Person(int age)
    {
        m_age = new int(age);
    }

    ~Person()
    {
        delete m_age;
        m_age = nullptr;
    }

    Person& operator=(const Person& p)
    {
        if (this == &p)
        {
            return *this;
        }

        delete m_age;
        m_age = new int(*p.m_age);

        return *this;
    }

    int* m_age;
};
```

### 15.5 关系运算符重载

```cpp
class Person
{
public:
    Person(string name, int age)
    {
        m_name = name;
        m_age = age;
    }

    bool operator==(const Person& p2)
    {
        return m_name == p2.m_name && m_age == p2.m_age;
    }

    bool operator!=(const Person& p2)
    {
        return !(*this == p2);
    }

    string m_name;
    int m_age;
};
```

### 15.6 函数调用运算符重载

重载 `()` 后，对象可以像函数一样调用，这种对象常叫“仿函数”。

```cpp
class MyPrint
{
public:
    void operator()(string text)
    {
        cout << text << endl;
    }
};

class MyAdd
{
public:
    int operator()(int num1, int num2)
    {
        return num1 + num2;
    }
};

void test01()
{
    MyPrint myPrint;
    myPrint("hello world");

    MyAdd myAdd;
    cout << myAdd(10, 20) << endl;
}
```

仿函数写法很灵活，没有固定形式。

## 16. 继承

继承可以把多个类中重复的公共内容抽取到父类中，子类复用父类成员，并扩展自己的功能。

语法：

```cpp
class 子类 : 继承方式 父类
{
};
```

也叫：

- 子类：派生类。
- 父类：基类。

### 16.1 普通页面案例到继承

不使用继承时，`Java`、`Cpp` 页面中会重复写公共头部、底部、左侧栏。

使用继承后：

```cpp
class BasePage
{
public:
    void header()
    {
        cout << "公共头部" << endl;
    }

    void footer()
    {
        cout << "公共底部" << endl;
    }

    void left()
    {
        cout << "公共左侧" << endl;
    }
};

class Java : public BasePage
{
public:
    void content()
    {
        cout << "Java 学科视频" << endl;
    }
};

void test01()
{
    Java ja;
    ja.header();
    ja.footer();
    ja.left();
    ja.content();
}
```

### 16.2 继承方式

| 继承方式 | 父类 `public` 成员在子类中 | 父类 `protected` 成员在子类中 | 父类 `private` 成员 |
| --- | --- | --- | --- |
| `public` 继承 | `public` | `protected` | 不可直接访问 |
| `protected` 继承 | `protected` | `protected` | 不可直接访问 |
| `private` 继承 | `private` | `private` | 不可直接访问 |

```cpp
class Base1
{
public:
    int m_a = 10;

protected:
    int m_b = 10;

private:
    int m_c = 10;
};

class Son1 : public Base1
{
};

class Son2 : protected Base1
{
};

class Son3 : private Base1
{
};
```

### 16.3 继承中的对象模型

父类中的非静态成员属性会被子类继承下去，包括 `private` 成员。只是 `private` 成员不能被子类直接访问。

```cpp
class Base
{
public:
    int m_a;

protected:
    int m_b;

private:
    int m_c;
};

class Son : public Base
{
public:
    int m_d;
};

void test01()
{
    cout << sizeof(Son) << endl;  // 常见情况下是 16
}
```

### 16.4 继承中构造和析构顺序

```cpp
class Base
{
public:
    Base()
    {
        cout << "Base 构造函数" << endl;
    }

    ~Base()
    {
        cout << "Base 析构函数" << endl;
    }
};

class Son : public Base
{
public:
    Son()
    {
        cout << "Son 构造函数" << endl;
    }

    ~Son()
    {
        cout << "Son 析构函数" << endl;
    }
};
```

顺序：

- 构造：先父类，再子类。
- 析构：先子类，再父类。

### 16.5 继承中同名成员处理

如果子类和父类有同名成员，访问父类同名成员需要加作用域。

```cpp
class Base
{
public:
    Base()
    {
        m_A = 100;
    }

    void func()
    {
        cout << "Base 中的 func 调用" << endl;
    }

    int m_A;
};

class Son : public Base
{
public:
    Son()
    {
        m_A = 200;
    }

    void func()
    {
        cout << "Son 中的 func 调用" << endl;
    }

    int m_A;
};

void test01()
{
    Son s1;

    cout << s1.m_A << endl;       // 子类 m_A
    cout << s1.Base::m_A << endl; // 父类 m_A

    s1.func();                    // 子类 func
    s1.Base::func();              // 父类 func
}
```

注意：如果子类中出现和父类同名的成员函数，子类同名函数会隐藏父类所有同名函数。要访问被隐藏的父类函数，必须加父类作用域。

### 16.6 同名静态成员处理

静态成员变量不属于任何对象，不占用对象内存，通常要在类外初始化。

```cpp
class Base
{
public:
    static int m_A;
};

int Base::m_A = 100;

class Son : public Base
{
public:
    static int m_A;
};

int Son::m_A = 200;

void test01()
{
    cout << Son::m_A << endl;        // 200
    cout << Son::Base::m_A << endl;  // 100

    Son s1;
    cout << s1.m_A << endl;
    cout << s1.Base::m_A << endl;
}
```

### 16.7 多继承

语法：

```cpp
class 子类 : 继承方式 父类1, 继承方式 父类2
{
};
```

同名成员可能产生二义性，需要加作用域区分。

```cpp
class Base1
{
public:
    int m_a;
};

class Base2
{
public:
    int m_a;
};

class Son : public Base1, public Base2
{
    int m_c;
    int m_d;
};

void test01()
{
    Son s1;
    cout << s1.Base1::m_a << endl;
    cout << s1.Base2::m_a << endl;
}
```

### 16.8 菱形继承与虚继承

菱形继承会导致同一个基类数据在最终子类中出现多份，产生二义性和资源浪费。

```cpp
class Animal
{
public:
    int m_age;
};

class Sheep : virtual public Animal
{
};

class Tuo : virtual public Animal
{
};

class SheepTuo : public Sheep, public Tuo
{
};
```

虚继承要点：

- `Animal` 称为虚基类。
- 虚继承可以让最终子类中只保留一份虚基类成员。
- 编译器常通过 `vbptr`（虚基类指针）和 `vbtable`（虚基类表）记录偏移量，从而找到虚基类成员的真实地址。

## 17. 多态

多态分为静态多态和动态多态。

- 静态多态：函数重载、运算符重载，编译阶段确定。
- 动态多态：继承 + 虚函数，运行阶段确定。

动态多态满足条件：

- 有继承关系。
- 子类重写父类虚函数。重写要求返回类型、函数名、参数列表完全相同。
- 使用父类指针或父类引用指向子类对象。

### 17.1 动态多态基础

```cpp
class Animal
{
public:
    virtual void speak()
    {
        cout << "动物在说话" << endl;
    }
};

class Cat : public Animal
{
public:
    void speak()
    {
        cout << "小猫在说话" << endl;
    }
};

class Dog : public Animal
{
public:
    void speak()
    {
        cout << "小狗在说话" << endl;
    }
};

void doSpeak(Animal& animal)
{
    animal.speak();
}

void test01()
{
    Cat cat;
    Dog dog;

    doSpeak(cat);
    doSpeak(dog);
}
```

虚函数底层理解：

- 有虚函数的类对象中通常会有 `vfptr`，即虚函数表指针。
- `vfptr` 指向 `vftable`，即虚函数表。
- 父类虚函数表记录父类虚函数地址。
- 子类继承后也有虚函数表；如果子类重写虚函数，表中对应地址会替换为子类函数地址。
- 父类引用或指针指向子类对象时，程序会根据对象中的虚函数表在运行阶段决定调用哪个函数，这就是动态绑定。

如果函数没有加 `virtual`，调用地址通常在编译阶段确定。变量或参数声明是什么类型，就调用那个类型中的函数版本，这叫静态绑定。

### 17.2 计算器案例：普通写法与多态写法

普通写法：

```cpp
class Calculate
{
public:
    int getResult(string oper)
    {
        if (oper == "+")
        {
            return m_Num1 + m_Num2;
        }

        if (oper == "-")
        {
            return m_Num1 - m_Num2;
        }

        if (oper == "*")
        {
            return m_Num1 * m_Num2;
        }

        return 0;
    }

    int m_Num1;
    int m_Num2;
};
```

缺点：如果想扩展新功能，比如除法，需要修改原类代码。真实开发中通常提倡“开闭原则”：对扩展开放，对修改关闭。

多态写法：

```cpp
class AbstractCalculate
{
public:
    virtual int getResult()
    {
        return 0;
    }

    int m_Num1;
    int m_Num2;
};

class AddCalculate : public AbstractCalculate
{
public:
    int getResult()
    {
        return m_Num1 + m_Num2;
    }
};

class SubCalculate : public AbstractCalculate
{
public:
    int getResult()
    {
        return m_Num1 - m_Num2;
    }
};

class MulCalculate : public AbstractCalculate
{
public:
    int getResult()
    {
        return m_Num1 * m_Num2;
    }
};

void test01()
{
    AbstractCalculate* abc = new AddCalculate;

    abc->m_Num1 = 10;
    abc->m_Num2 = 10;

    cout << abc->m_Num1 << " + " << abc->m_Num2
         << " = " << abc->getResult() << endl;

    delete abc;
    abc = nullptr;
}
```

多态优点：

- 组织结构清晰。
- 可读性强。
- 扩展和维护更方便。

### 17.3 纯虚函数与抽象类

纯虚函数写法：

```cpp
virtual 返回值类型 函数名(参数列表) = 0;
```

规则：

- 类中有纯虚函数，这个类称为抽象类。
- 抽象类不能实例化对象。
- 子类必须重写父类中的纯虚函数，否则子类仍然是抽象类。

```cpp
class Base
{
public:
    virtual void func() = 0;
};

class Son : public Base
{
public:
    void func()
    {
    }
};

void test01()
{
    Base* abc = new Son;
    abc->func();
    delete abc;
}
```

### 17.4 多态案例：制作饮品

这是模板方法模式的雏形：父类定义制作流程，子类实现具体步骤。

```cpp
class AbstractDrinking
{
public:
    virtual void boil() = 0;
    virtual void brew() = 0;
    virtual void pourInCup() = 0;
    virtual void putSomething() = 0;

    void makeDrink()
    {
        boil();
        brew();
        pourInCup();
        putSomething();
    }
};

class Coffee : public AbstractDrinking
{
public:
    void boil()
    {
        cout << "煮农夫山泉" << endl;
    }

    void brew()
    {
        cout << "冲泡咖啡" << endl;
    }

    void pourInCup()
    {
        cout << "倒入咖啡杯" << endl;
    }

    void putSomething()
    {
        cout << "加糖和牛奶" << endl;
    }
};

class Tea : public AbstractDrinking
{
public:
    void boil()
    {
        cout << "煮矿泉水" << endl;
    }

    void brew()
    {
        cout << "冲泡龙井" << endl;
    }

    void pourInCup()
    {
        cout << "倒入茶杯" << endl;
    }

    void putSomething()
    {
        cout << "加入枸杞" << endl;
    }
};

void doWork(AbstractDrinking* abs)
{
    abs->makeDrink();
    delete abs;
}

void doWork2(AbstractDrinking& abs)
{
    abs.makeDrink();
}
```

注意：如果要通过父类指针 `delete` 子类对象，父类析构函数应该写成虚析构。这个案例中如果没有堆资源，很多时候看不出问题，但规范写法仍建议加虚析构。

### 17.5 虚析构与纯虚析构

如果父类指针指向子类对象，并且通过父类指针释放对象，父类析构函数必须是虚函数，否则可能只调用父类析构，不调用子类析构，导致子类资源泄漏。

虚析构：

```cpp
class Animal
{
public:
    virtual void speak() = 0;

    virtual ~Animal()
    {
        cout << "Animal 析构函数" << endl;
    }
};
```

纯虚析构：

```cpp
class Animal
{
public:
    Animal()
    {
        cout << "Animal 构造函数" << endl;
    }

    virtual void speak() = 0;

    virtual ~Animal() = 0;
};

Animal::~Animal()
{
    cout << "Animal 纯虚析构函数调用" << endl;
}

class Cat : public Animal
{
public:
    Cat(string name)
    {
        m_name = new string(name);
        cout << "Cat 构造函数" << endl;
    }

    void speak()
    {
        cout << *m_name << " 小猫在说话" << endl;
    }

    ~Cat()
    {
        delete m_name;
        m_name = nullptr;
        cout << "Cat 析构函数" << endl;
    }

private:
    string* m_name;
};

void test01()
{
    Animal* abc = new Cat("Tom");
    abc->speak();

    delete abc;
}
```

要点：

- 虚析构和纯虚析构都可以解决父类指针释放子类对象的问题。
- 纯虚析构也必须提供函数实现。
- 有了纯虚析构后，这个类也属于抽象类，不能实例化对象。
- 析构顺序：先调用子类析构，再调用父类析构。

## 18. 多态综合案例：电脑组装

需求：

- 抽象出三个零件接口：`CPU`、`VideoCard`、`Memory`。
- 不同厂商实现不同零件。
- `Computer` 组合这些零件，通过父类指针调用各零件工作函数，实现多态。

原示例中的思路是正确的。这里整理成更规范的写法：给抽象基类增加虚析构，并使用 `override` 标明重写。

```cpp
#include <iostream>
#include <string>
using namespace std;

class CPU
{
public:
    virtual void calculate() = 0;
    virtual ~CPU() = default;
};

class VideoCard
{
public:
    virtual void display() = 0;
    virtual ~VideoCard() = default;
};

class Memory
{
public:
    virtual void storage() = 0;
    virtual ~Memory() = default;
};

class IntelCPU : public CPU
{
public:
    void calculate() override
    {
        cout << "Intel 的 CPU 开始计算了" << endl;
    }
};

class IntelVideoCard : public VideoCard
{
public:
    void display() override
    {
        cout << "Intel 的显卡开始显示了" << endl;
    }
};

class IntelMemory : public Memory
{
public:
    void storage() override
    {
        cout << "Intel 的内存条开始存储了" << endl;
    }
};

class LenovoCPU : public CPU
{
public:
    void calculate() override
    {
        cout << "Lenovo 的 CPU 开始计算了" << endl;
    }
};

class LenovoVideoCard : public VideoCard
{
public:
    void display() override
    {
        cout << "Lenovo 的显卡开始显示了" << endl;
    }
};

class LenovoMemory : public Memory
{
public:
    void storage() override
    {
        cout << "Lenovo 的内存条开始存储了" << endl;
    }
};

class Computer
{
public:
    Computer(CPU* cpu, VideoCard* videoCard, Memory* memory)
    {
        m_cpu = cpu;
        m_videoCard = videoCard;
        m_memory = memory;
    }

    void work()
    {
        m_cpu->calculate();
        m_videoCard->display();
        m_memory->storage();
    }

    ~Computer()
    {
        delete m_cpu;
        delete m_videoCard;
        delete m_memory;

        m_cpu = nullptr;
        m_videoCard = nullptr;
        m_memory = nullptr;
    }

private:
    CPU* m_cpu;
    VideoCard* m_videoCard;
    Memory* m_memory;
};

void test01()
{
    CPU* intelCPU = new IntelCPU;
    VideoCard* intelCard = new IntelVideoCard;
    Memory* intelMemory = new IntelMemory;

    Computer* computer1 = new Computer(intelCPU, intelCard, intelMemory);
    computer1->work();

    delete computer1;
}

int main()
{
    test01();
    return 0;
}
```

这个案例对应的知识点：

- `CPU`、`VideoCard`、`Memory` 是抽象类。
- `IntelCPU`、`LenovoCPU` 等具体类重写纯虚函数。
- `Computer` 持有基类指针，运行时根据真实对象类型调用对应函数。
- 因为 `Computer` 通过基类指针释放派生类对象，所以基类析构函数必须是 `virtual`。

## 19. 易错点速查

| 易错点 | 正确理解 |
| --- | --- |
| `Person p();` | 这是函数声明，不是创建对象；默认构造应写 `Person p;` |
| `new[]` 和 `delete` 混用 | `new[]` 必须配 `delete[]` |
| 返回局部变量引用 | 局部变量函数结束就销毁，不能返回其引用 |
| 拷贝构造参数不写引用 | 会再次触发拷贝构造，可能无限递归 |
| 类中有指针成员还用默认拷贝 | 默认浅拷贝可能导致重复释放 |
| 链式调用返回值而不是引用 | 后续调用可能作用在临时副本上 |
| 通过空指针调用成员函数 | 属于未定义行为，不要依赖 |
| 子类和父类同名成员 | 访问父类版本要加作用域，如 `s.Base::m_A` |
| 多继承同名成员 | 需要加作用域区分，如 `s.Base1::m_a` |
| 菱形继承 | 使用虚继承避免公共基类成员重复 |
| 基类指针删除派生类对象 | 基类析构函数必须是 `virtual` |
| 纯虚析构只声明不实现 | 纯虚析构也必须在类外提供实现 |
| 静态成员变量只在类内声明 | 通常还需要类外初始化，如 `int Person::m_A = 100;` |
| 常对象调用普通成员函数 | 常对象只能调用 `const` 成员函数 |
| `mutable` | 即使在常对象或 `const` 成员函数中也可以被修改 |

## 学习路线建议

这份笔记可以按下面顺序复习：

1. 先掌握内存、引用、函数重载。
2. 再掌握类的封装、构造析构、深浅拷贝。
3. 然后学习静态成员、`this`、`const` 成员函数、友元和运算符重载。
4. 最后重点理解继承和多态，尤其是虚函数、虚析构、纯虚函数。

如果只看一个核心线索：C++ 面向对象的重点是“对象如何构造、如何拷贝、如何释放、如何通过继承和虚函数实现一套接口多种行为”。
