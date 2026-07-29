#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
// 内存分配模型
// 代码区：存放函数的二进制代码，由操作系统进行管理，代码区是共享且只读的
// 全局区：存放全局变量和静态变量以及常量（字符串常量，全局常量），程序结束后由操作系统释放
// 栈区：由编译器自动分配释放，存放函数的参数值，局部变量等
// 堆区：由程序员分配与释放，若程序员不释放，程序结束时由操作系统回收

////全局变量
// int g_a = 10;
////const修饰的全局常量
// const int c_g_b = 10;
// int* func()
//{
//	int* p = new int(10);
//	return p;
// }
// int main()
//{
//	//静态变量
//	static int s_a = 10;
//	//局部变量
//	int a = 10;
//	//常量
//	//字符串常量
//	cout << "字符串常量的地址 ： " << &"hello world" << endl;
//	//const修饰的局部变量不在全局区
//	const int c_l_a = 10;
//	int* p = func();
//	cout << *p << endl;
//	system("pause");
//	return 0;
// }

////堆区
// int* func()
//{
//	int* p = new int(10);//传回对应堆区内存的地址
//	return p;
// }
// void test01()
//{
//	int* p = func();
//	cout << *p << endl;
//	delete(p);//传入对应的地址释放堆区内存
// }
// void test02()
//{
//	int* arr = new int[10];  //10代表数组有十个元素
//	for (int i = 0; i < 10; i++)
//	{
//		arr[i] = 100 + i;
//	}
//	delete[] arr;//表示释放数组
// }

////引用的本质是一个指针常量int* const a
// void myswap(int& a, int& b)//引用传递
//{
//	int temp = a;
//	a = b;
//	b = temp;
// }
////引用做函数的返回值
//// 1.不返回局部变量的
// int& test01()
//{
//	static int a = 10;//静态变量放在全局区不在栈区，函数结束之后也会保留才可以传回去
//	return a;
// }
//// 2.返回值做左值
//
// void showvalue(const int& val)//防止误操作
//{
//	cout << val << endl;
//}
////引用:给变量起别名
////引用后两个访问的是同一块内存
// int main()
//{
//	int a = 10;
//	int c = 30;
//	int &b = a;//引用必须初始化，引用在初始化之后不可以改变
//	//引用做函数参数
//	myswap(a, c);
//	cout << a << endl;
//	cout << c << endl;
//
//	test01() = 1000; //返回值是引用相当于返回了a的一个别名，因此可以作为左值对该地址的变量进行修改
//	//常量引用
//	//用来修饰形参，防止误操作
//	const  int& ref = 10;//相当于创建了一个变量int temp=10,然后进行引用，const int&ref=temp;
//	//此时ref就不可以修改了，只读状态
//	int a = 100;
//	showvalue(a);
//	system("pause");
//	return 0;
// }

////函数默认值
////如果有传入就用传入的，没有传入的就用默认的
////如果某一位置已经有了默认参数，从该数字往后所有都要有默认参数
////函数的声明和实现只能有一个有默认参数，防止歧义
//
////函数的占位参数
////占位参数也可以有默认参数
//
////函数重载
////函数名称相同，提高复用性
////必须在同一个作用域，比如都在全局作用域
////函数名称相同
////函数参数类型不同，或者个数不同，或者顺序不同
////函数的返回值不能作为重载的满足条件
////注意引用作为参数
////注意参数有默认值
// int func(int c,int b,int e,int d)
//{
//	cout << "重载函数" << endl;
//	return c;
// }
// void func(int a,int)
//{
//	cout << "占位符" << endl;
// }
////int func(int a, int b = 10, int c = 20)
////{
////	return a + b + c;
////}
// void func(int& a)
//{
//	cout << "int&a" << endl;
// }
// void func(const int& a)
//{
//	cout << "const int&a" << endl;
// }
// int main()
//{
//	int a = 10;
//	func(10);
//	func(a);
//	system("pause");
//	/*int sum2 = func(10, 100, 300);*/
//	return 0;
// }

////类和对象
////封装
////在属性和行为整体封装一类事物
////权限:
////public    成员类内类外都可以访问
////protected 成员类内可以访问类外不可以  儿子可访问
////private   成员类内可以访问类外不可以	儿子不可以访问
// const double PI = 3.14;
// class Circle
//{
//	//访问权限
// public:
//	//类中的属性和行为都称为成员
//	//属性（又称为成员属性成员变量）
//	int m_r;
//	//行为（又称为成员函数成员方法）
//	double calculateZC()
//	{
//		return 2 * PI * m_r;
//	}
// };
// class student
//{
// public:
//	string m_number;
//	string m_name;
//	void showinform()
//	{
//		cout << "学号是：" << m_number << endl;
//		cout << "姓名是：" << m_name << endl;
//	}
//	void setName(string name)
//	{
//		m_name = name;
//	}
//	void setNumber(string number)
//	{
//		m_number = number;
//	}
// };
// class person
//{
// public:
//	string m_name;
// protected:
//	string m_car;
// private:
//	int m_password;
// public:
//	void func()
//	{
//		m_name = "张三";
//		m_car = "拖拉机";
//		m_password = 123456;
//	}
// };
////struct默认权限为公共，而class默认私有
// int main()
//{
//	////通过圆类创建具体的圆（对象）
//	////实例化，具体化一个对象出来
//	//Circle c1;
//	////对一个对象赋值
//	//c1.m_r = 10;
//	//cout << "圆的周长是" << c1.calculateZC() << endl;
//
//	//student A;
//	//A.setNumber( "8208250831");
//	//A.setName ("cs");
//	//A.showinform();
//	person p1;
//	p1.m_name = "李四";
//	//保护权限和私有权限在类外不可访问
//	system("pause");
//	return 0;
// }

// 成员属性设置私有
// 控制读写权限，检测数据有效性
// class person
//{
// public:
//	void setname(string name)
//	{
//		m_name = name;
//	}
//	string getname()
//	{
//		return m_name;
//	}
//	void setage(int age)
//	{
//		if (age < 0 || age>150)
//		{
//			cout << "年龄输入有误输入失败" << endl;
//			return;
//		}
//		m_age = age;
//	}
//	int getage()
//	{
//		return m_age;
//	}
//	void setIdol(string Idol)
//	{
//		m_Idol = Idol;
//	}
// private:
//	string m_name;//可写可读
//	int m_age = 18;//可读，写要检测有效性
//	string m_Idol;//可写不可读
// };

// class cube
//{
// public:
//	void set(int l, int w, int h)
//	{
//		m_L = l;
//		m_W = w;
//		m_H = h;
//	}
//	int calculateS()
//	{
//		return 2 * m_L * m_W + 2 * m_H * m_W + 2 * m_H * m_L;
//	}
//	int calculateV()
//	{
//		return m_L * m_W * m_H;
//	}
//	int getL()
//	{
//		return m_L;
//	}
//	int getW()
//	{
//		return m_W;
//	}
//	int getH()
//	{
//		return m_H;
//	}
//	bool is_same(cube &c2)
//	{
//		if ((m_L == c2.getL()) && (m_W == c2.getW()) && (m_H == c2.getH()))
//			return true;
//		return false;
//	}
// private:
//	int m_L;
//	int m_W;
//	int m_H;
// };
// bool issame(cube &c1,cube &c2)
//{
//	if ((c1.getH() == c2.getH()) && (c1.getW() == c2.getW()) && (c1.getL() == c2.getL()))
//		return true;
//	else
//		return false;
// }
////在一个类中可以让另一个类作为该类中的成员
////如果在.h文件中声明circle和point，要把成员函数的实现去掉只留下声明
////在.cpp文件中实现成员函数的时候要写void circle::setR（）即应该标明这是哪个类的成员函数实现
////在.cpp文件中要写#include"circle.h"来引用头文件#pragma once，防止头文件重复包含而编译错误
// int main()
//{
//	cube c1;
//	cube c2;
// }

////对象的初始化和清理
////构造函数进行初始化操作
////析构函数进行清理工作
// class person
//{
//	//构造函数,没有返回值，不用写void
//	//函数名与类名相同
//	//可以有参数，可以发生重载
//	//创建对象的时候，构造函数会自动调用并且只调用一次
// public:
//	person()
//	{
//		cout << "person无参构造函数的调用" << endl;
//	}
//	person(int age)
//	{
//		m_age = age;
//		cout << "person有参构造函数的调用" << endl;
//	}
//	person(const person &p)//拷贝函数,将传入的人身上的所有属性拷贝到自己身上
//	{
//		m_age = p.m_age;
//		cout << "person的拷贝构造函数的调用" << endl;
//	}
//	//析构函数
//	//没有返回值也不写void
//	//函数名与类名相同 在名称前加~
//	//析构函数不可以有参数不可以重载
//	//对象在销毁前析构函数自动被调用
//	//如果构造函数和析构函数没有写，编译器会构造空函数
//	~person()
//	{
//		cout << "析构函数的调用" << endl;
//	}
//	int m_age;
//	int* m_height;
// };
////构造函数的分类与调用
////有参无参
////普通拷贝
////调用
// void test01()
//{
//	//括号法创建对象并且选择合适的构造函数,简单方便
//	/*person p;
//	person p2(10);
//	person p3(p);*/
//	//单纯创建对象使用person()构造函数不要加(),编译器会认为是函数声明
//	//显示法
//	person p;
//	person p2 = person(10); //调用了有参构造
//	person p3 = person(p);
//	person(10);//匿名对象，在前行执行结束后，系统会立即回收匿名对象,不要用拷贝构造函数初始化匿名对象
//	//编译器会认为，person(p3)==person p3，上下重定义
//	//隐式转换法
//	person p4 = 10;//相当于person p4=person(10),相当于person p4(10);
// }
// 拷贝构造函数调用时机
// 1.使用已经创建完毕的对象来初始化一个新对象
// 2.值传递的方式给函数参数传值，值传递的时候由于要创建一个新的类对象，且传入了一个p，因此进行的是拷贝构造函数
//     person p（p1）等效于person p=person（p1）所以是拷贝构造对吧，比如func（p1），这本质上并没有调用person函数，
//     所以如果接收参数的时候是person p，就相当于拷贝构造，而person& p就只是引用没有构造
// 构造函数调用规则
// 1.cpp编译器会默认提供：默认构造（空），拷贝构造（值拷贝），析构函数（空）
// 2.如果写了默认构造其他的也照样提供
// 3.如果有有参构造，那么就不会提供默认构造。！！！
// 4.如果写了拷贝构造，编译器就不提供其他的构造函数。

////深拷贝与浅拷贝
////浅拷贝只是把指针拷贝过来，地址一模一样，深拷贝在堆区创建开辟新的空间，地址不同
// class person
//{
// public:
//	person()
//	{
//		cout << "person无参构造函数的调用" << endl;
//	}
//	person(int age, int height)
//	{
//		m_age = age;
//		m_height = new int(height);
//		cout << "person有参构造函数的调用" << endl;
//	}
//	person(const person& p)
//	{
//		m_age = p.m_age;
//		m_height = new int(*p.m_height);//深拷贝
//		cout << "person的拷贝构造函数的调用" << endl;
//	}
//	~person()
//	{
//		if (m_height != NULL)
//		{
//			delete(m_height);
//			m_height = NULL;
//		}
//		cout << "析构函数的调用" << endl;
//	}
//	int m_age;
//	int* m_height;
// };
// void test02()
//{
//	person p1(18,160);
//	person p2(p1);//现在对象里面有指针且相同，
//	//两个对象都会触发析构函数，导致同一地址被两次释放而报错
// }
// int main()
//{
//	test02();
//	system("pause");
//	return 0;
// }

////初始化列表
// class person
//{
// public:
//	/*person(int a,int b,int c)
//	{
//		m_A = a;
//		m_B = b;
//		m_C = c;
//	}*/
//	person(int a,int b,int c) :m_A(a), m_B(b), m_C(c)
//	{
//
//	}
//	int m_A;
//	int m_B;
//	int m_C;
// };
// int main()
//{
//	person p(10, 20, 30);
//	system("pause");
//	return 0;
// }
//

// class phone
//{
// public:
//	phone(string pname)
//	{
//		m_pname = pname;
//	}
//	string m_pname;
// };
// class person
//{
// public:
//	person(string name, string pname):m_name(name), m_phone(pname)
//	//构造函数的时候本身其实也是创建了一个phone类的对象m_phone,所以这里也可以直接用phone的构造函数
//	{
//
//	}
//	string m_name;
//	phone m_phone;
// };
////当其他类对象作为本类成员，先构造其他类对象，再构造自身
////析构函数先析构自身，再析构其他类对象，两者相反
// void test01()
//{
//	person p("张三", "苹果20promax");
//	cout << p.m_name << "拿着" << p.m_phone.m_pname << "手机" << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////静态成员
////静态成员变量
////静态成员函数：只能访问静态成员变量
// class person
//{
// public:
//	static void func()
//	{
//		m_A = 100;//不可访问非静态成员变量
//		cout << "static void func调用" << endl;
//		//m_C不可调用因为无法区分要改变哪个对象的数据
//	}
//	//1.所有对象共享同一份数据
//	//2.编译阶段就分配内存
//	//3.类内声明，类外初始化操作
//	static int m_A;
//	int m_C;
// private:
//	static int m_B ;
// };
// int person::m_A = 100;
// int person::m_B = 200;
//
// void test01()
//{
//	person p;
//	cout << p.m_A << endl;
//	p.func();
//	person::func();
//	person p2;
//	p2.m_A = 200;
//	cout << p.m_A << endl;//表明所有对象都公用同一个数据
//	cout << person::m_A << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////成员变量与成员函数是分开存储的
// class person
//{
//	int m_A;//属于类的对象上,只有非静态变量属于静态上
//	static int m_B;//静态变量不属于对象上
//	void func();//非静态成员函数不属于对象上
//	static void func2();//静态成员函数不属于对象上
// };
// void test01()
//{
//	person p;
//	//空对象占一个字节，为了区分空对象占内存的位置
//	//每个空对象也应该有一个独一无二的地址
//	cout << "sizeof p:" << sizeof(p) << endl;
// }
// void test02()
//{
//	person p;
//	cout << "sizeof p:" << sizeof(p) << endl;
// }
// int main()
//{
//	//test01();
//	test02();
//
//	system("pause");
//	return 0;
// }

////this指针,只想被调用的成员函数所属的对象
////1.解决名称冲突！！
////2.返回对象本身！！
// class person
//{
// public:
//	int age;
//	person(int age)
//	{
//		this->age = age;
//	}
//	person& personaddage(person& p)
//	{
//		this->age += p.age;
//		return *this;
//	}
// };
////this指针指向的是被调用的成员函数所属的对象！！！
// void test01()
//{
//	person p1(18);
// }
// void test02()
//{
//	person p1(10);
//	person p2(18);
//	p2.personaddage(p1).personaddage(p1).personaddage(p1).personaddage(p1);//链式编程思想
//  如果不反回引用，返回值，比如你写一个累加的链式方法，连续调用三次之后，你会发现原始对象的状态只被修改了一次！！！
//  剩下两次操作全作用在临时副本上，执行完就被销毁了，完全达不到你想要的连续修改效果。
// }

////空指针调用成员函数
// class person
//{
// public:
//	void showclassname()
//	{
//		cout << "this is a person class" << endl;
//	}
//	void showpersonage()
//	{
//		if (this == NULL)
//		{
//			return;
//		}
//		cout << "age=" << this->m_age << endl;
//	}
//	int m_age;
// };
// void test01()
//{
//	person* p = NULL;
//	p->showclassname();
//	p->showpersonage();//报错原因是因为传入的指针是NULL
// }

////const修饰成员函数
// class person
//{
// public:
//	//this指针的本质是指针常量，指针的指向是不可以修改的 person* const this
//	void showperson()const//常函数本质相当于const person* const this,this指向的值也不可以修改
//	{
//		m_C = 100;
//	}
//	int m_age;
//	int m_A;
//	int m_B;
//	mutable int m_C;//加mutable的可以修改
// };
// void test02()
//{
//	const person p1;//常对象，不允许修改对象里的数据,但mutable修饰的仍然可以改
//	//对象只能调用常函数
//
// }
// int main()
//{
//
//	system("pause");
//	return 0;
// }

////友元
////全局函数做友元
// class building
//{
//	friend void goodgay(building* building);
//
// public:
//	building()
//	{
//		m_settingroom = "客厅";
//		m_bedroom = "卧室";
//	}
//	string m_settingroom;
// private:
//	string m_bedroom;
// };
////全局函数
// void goodgay(building* building)
//{
//	cout << "好基友全局函数正在访问：" << building->m_settingroom << endl;
//	cout << "好基友全局函数正在访问：" << building->m_bedroom << endl;
//
// }
// void test01()
//{
//	building building;
//	goodgay(&building);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
// 类做友元
// 在类里面加上别的类的声明，在调用别的类的对象的时候就可以访问这个类看里的私有成员
// class building
//{
//	friend class goodgay;
// public:
//	building();
//	string m_settingroom;
// private:
//	string m_bedroom;
//
// };
// class goodgay
//{
// public:
//	goodgay();
//	void visit();
//	building* m_building;
// };
// building::building()
//{
//	m_settingroom = "客厅";
//	m_bedroom = "卧室";
// }
// goodgay::goodgay()
//{
//	m_building = new building;
// }
// void goodgay::visit()
//{
//	cout << "好基友正在参观" << m_building->m_settingroom << endl;
//	cout << "好基友正在参观" << m_building->m_bedroom << endl;
//
// }
// void test01()
//{
//	goodgay gg;
//	gg.visit();
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
// 成员函数做友元:
// class building;
// class goodgay
//{
// public:
//	goodgay();
//	void visit();
//	void visit2();
//	building* m_building;
// };
// class building
//{
//	friend void goodgay::visit();
// public:
//	building();
//	string m_settingroom;
// private:
//	string m_bedroom;
//
// };
//
// building::building()
//{
//	m_settingroom = "卧室";
//	m_bedroom = "客厅";
// }
// goodgay::goodgay()
//{
//	m_building = new building;
// }
// void goodgay::visit()
//{
//	cout << "visit函数正在访问：" << m_building->m_settingroom << endl;
//	cout << "visit函数正在访问：" << m_building->m_bedroom << endl;
//
// }
// void goodgay::visit2()
//{
//	cout << "visit2函数正在访问：" << m_building->m_settingroom << endl;
//	//cout << "visit函数正在访问：" << m_building->m_bedroom << endl;
//
// }
//
// void test01()
//{
//	goodgay gg;
//	gg.visit();
//	gg.visit2();
//
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 总结：友元相当于就是可以访问私有成员的函数或者对象
// friend void goodgay(building* building);全局函数访问
// friend class goodgay;类访问
// friend void goodgay::visit();成员函数访问

// 运算符重载
////加号运算符重载
////成员函数重载
////全局函数重载
// class person
//{
// public:
//	/*person operator+(person& p)
//	{
//		person temp;
//		temp.m_a = this->m_a + p.m_a;
//		temp.m_b = this->m_b + p.m_b;
//		return temp;
//	}*/
//	int m_a;
//	int m_b;
// };
// person operator+(person& p1, person& p2)
//{
//	person temp;
//	temp.m_a = p1.m_a + p2.m_a;
//	temp.m_b = p1.m_b + p2.m_b;
//	return temp;
// }
// person operator+(person& p1, int a)//函数重载
//{
//	person temp;
//	temp.m_a = p1.m_a + 10;
//	return temp;
// }
// void test01()
//{
//	person p1;
//	p1.m_b = 10;
//	p1.m_a = 10;
//	person p2;
//	p2.m_b = 10;
//	p2.m_a = 10;
//	person p3 = p1 + p2;
//	person p4 = p1 + 10;
//	//对于成员函数重载，本质是person p3=p1.operator+(p2);
//	//对于全局函数重载，本质是person p3=operatoer+(p1,p2);
//	//上面是二者的简化
//	//运算符重载也可以发生函数重载
//	cout << p3.m_a << endl << p3.m_b << endl << p4.m_a << endl;;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 左移运算符重载
// class person
//{
//	friend ostream& operator<<(ostream& cout, person& p);
// public:
//	person(int a, int b)
//	{
//		m_a = a;
//		m_b = b;
//	}
// private:
//	//通常不用成员函数进行左移运算符重载
//	int m_a;
//	int m_b;
// };
// ostream& operator<<(ostream& cout, person& p)
//{
//	cout << "m_a=" << p.m_a << "m_b=" << p.m_b ;
//	return cout;
// }
////cout是ostream的一个对象，如果想进行链式访问，必须保证始终是同一个cout，因此就必须返回引用不能返回值
////cout<<p形式上其实就等于p1+p2，只不过这里重载的运算符是<<而不是+
////拷贝构造的时候接受参数必须是引用，不然相当于又要进行一次拷贝构造，进入死循环
////拷贝构造函数调用时机
////1.使用已经创建完毕的对象来初始化一个新对象
////2.值传递的方式给函数参数传值，值传递的时候由于要创建一个新的类对象，且传入了一个p，因此进行的是拷贝构造函数
////ostream类把cout的拷贝构造删掉了，如果这里用ostream cout那就相当于ostream out=cout，或者ostream out（cout），相当于拷贝构造
//
// void test01()
//{
//	person p(10, 10);
//	cout << p << endl;
//}
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
//}

// 递增运算符重载++
// class myinteger
//{
//	friend ostream& operator<<(ostream& cout, const myinteger& p);
// public:
//	myinteger& operator++()//myint.operator++()
//	{
//		m_num++;
//		return *this;
//	}
//	myinteger operator++(int)//myint.operator++(0)
//	{
//		myinteger temp = *this;
//		m_num++;
//		return temp;
//	}
//	myinteger()
//	{
//		m_num = 0;
//	}
// private:
//		int m_num;
// };
// ostream& operator<<(ostream& cout, const myinteger& p)
//{
//	cout << p.m_num;
//	return cout;
// }
////注意，operator++（int）返回的是临时变量的拷贝值，
////函数结束后临时变量被销毁，无法引用（因为引用的本质是指针）
////所以只能用值传递
// void test01()
//{
//	myinteger myint;
//	cout << myint++ << endl;
//	cout << myint << endl;
//
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////赋值运算符重载
// class person
//{
// public:
//	person(int age)
//	{
//		m_age = new int(age);
//	}
//	~person()
//	{
//		if (m_age != NULL)
//		{
//			delete(m_age);
//		}
//	}
//	person& operator=(person& p1)
//	{
//		if (m_age != NULL)
//		{
//			delete(m_age);
//		}
//		m_age = new int(*(p1.m_age));//深拷贝
//		return *this;
//	}
//	int *m_age;
// };
// void test01()
//{
//	person p1(18);
//	person p2(20);
//	p2 = p1;//浅拷贝，只是把p1.m_age的值给了p2，也就是说两者的地址一模一样
//	//编译器默认提供浅拷贝!!!容易导致内存重复释放和野指针的解引用等
//	cout << "p1的年龄为:" << *p1.m_age << endl;
//	cout << "p1的年龄为:" << *p2.m_age << endl;
//
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////关系运算符重载
// class person
//{
// public:
//	person(string name, int age)
//	{
//		m_name = name;
//		m_age = age;
//	}
//	bool operator==(person& p2)
//	{
//		if ((m_name == p2.m_name) && (m_age == p2.m_age))
//			return true;
//		return false;
//	}
//	bool operator!=(person& p2)
//	{
//		if ((m_name == p2.m_name) && (m_age == p2.m_age))
//			return false;
//		return true;
//	}
//	string m_name;
//	int m_age;
// };
// void test01()
//{
//	person p1("tom", 18);
//	person p2("tom", 19);
//	if (p1 == p2)
//	{
//		cout << "p1和p2是相等的" << endl;
//	}
//	else
//	{
//		cout << "p1和p2是不相等的" << endl;
//	}
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////函数调用运算符重载
// class Myprint
//{
// public:
//	void operator()(string test)
//	{
//		cout << test << endl;
//	}
// };
// class Myadd
//{
// public:
//	int operator()(int num1, int num2)
//	{
//		return num1 + num2;
//	}
// };
//
// void test01()
//{
//	Myprint myprint;
//	myprint("hello world");//仿函数
//	Myadd myadd;
//	//等价于
//	//myadd.operator()(10, 20);
//	cout << myadd(10, 20) << endl;;
// }
////仿函数非常灵活，没有一个固定的写法
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 继承
// 普通实现页面
// class java
//{
// public:
//	void header()
//	{
//		cout << "公共头部" << endl;
//	}
//	void footer()
//	{
//		cout << "公共底部" << endl;
//	}
//	void left()
//	{
//		cout << "公共左侧" << endl;
//	}
//	void content()
//	{
//		cout << "java学科视频" << endl;
//	}
// };
// class cpp
//{
// public:
//	void header()
//	{
//		cout << "公共头部" << endl;
//	}
//	void footer()
//	{
//		cout << "公共底部" << endl;
//	}
//	void left()
//	{
//		cout << "公共左侧" << endl;
//	}
//	void content()
//	{
//		cout << "C++学科视频" << endl;
//	}
// };
// 继承
// class basepage
//{
// public:
//	void header()
//	{
//		cout << "公共头部" << endl;
//	}
//	void footer()
//	{
//		cout << "公共底部" << endl;
//	}
//	void left()
//	{
//		cout << "公共左侧" << endl;
//	}
// };
// class java : public basepage//公共继承方式
////class 子类（派生类）：继承方式 父类（基类）
//{
// public:
//	void content()
//	{
//		cout << "java学科视频" << endl;
//	}
//};
// void test01()
//{
//	java ja;
//	ja.footer();
//	ja.header();
//	ja.left();
//	ja.content();
//}
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
//}
////公共继承：父类的公共在子类中是公共，保护是保护，私有不可访问
////保护继承：父类的公共在子类中是保护，保护是保护，私有不可访问
////私有继承：父类的公共在子类中是私有，保护是私有，私有不可访问
// class base1
//{
// public:
//	int m_a = 10;
// protected:
//	int m_b = 10;
// private:
//	int m_c = 10;
// };
// class son1 :public base1
//{
//
// };
// class son2 :protected base1
//{
//
// };
// class son3 :private base1
//{
//
// };

// 继承中的对象模型
// class base
//{
// public:
//	int m_a;
// protected:
//	int m_b;
// private:
//	int m_c;
// };
// class son :public base
//{
// public:
//	int m_d;
// };
// void test01()
//{
//	cout << sizeof(son) << endl;//16,也就是非静态成员属性都会被子类继承下去
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
// 继承中构造和析构顺序
// class base
//{
// public:
//	base()
//	{
//		cout << "base中的构造函数" << endl;
//	}
//	~base()
//	{
//		cout << "base中的析构函数" << endl;
//	}
// };
// class son :public base
//{
// public:
//	son()
//	{
//		cout << "son中的构造函数" << endl;
//	}
//	~son()
//	{
//		cout << "son中的析构函数" << endl;
//	}
// };
// void test01()
//{
//	son s1;
//	//构造是先父后子
//	//析构是先子后父
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 继承中同名成员处理方式
// class base
//{
// public:
//	base()
//	{
//		m_A = 100;
//	}
//	void func()
//	{
//		cout << "base中的func调用" << endl;
//	}
//	int m_A;
//
// };
// class son :public base
//{
// public:
//	son()
//	{
//		m_A = 200;
//	}
//	void func()
//	{
//		cout << "son中的func调用" << endl;
//	}
//	int m_A;
// };
// void test01()
//{
//	son s1;
//	cout << s1.m_A << endl;
//	cout << s1.base::m_A << endl;
//	s1.func();
//	s1.base::func();
//
//	//访问父类同名成员需要加base：：作用域
//	//如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏父类所有同名成员函数
//	//如果想访问父类中被隐藏的必须要加作用域
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
// 继承同名静态成员处理方法
// class base
//{
// public:
//	static int m_A;
// };
// int base::m_A = 100;//静态成员变量不会在类内占用内存，不属于任何对象不会跟着对象走，因此需要在类外赋值
// class son :public base
//{
// public:
//	static int m_A;
// };
// int son::m_A = 200;
// void test01()
//{
//	cout << son::base::m_A << endl;
//	son s1;
//	cout << s1.m_A << endl;
//	cout << s1.base::m_A << endl;
//
//
//	//访问父类同名成员需要加base：：作用域
//	//如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏父类所有同名成员函数
//	//如果想访问父类中被隐藏的必须要加作用域
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////多继承语法
////class 子类：继承方式 父类，继承方式 父类2
// class base1
//{
// public:
//	int m_a;
// };
// class base2
//{
// public:
//	int m_a;
// };
// class son :public base1, public base2
//{
//	int m_c;
//	int m_d;
// };
// void test01()
//{
//	son s1;
//	cout << s1.base1::m_a << endl;
//	cout << s1.base2::m_a << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////菱形继承
////多继承会产生二义性
////动物类
// class animal
//{
// public:
//	int m_age;
// };
// class sheep :virtual public animal//虚继承,animal称为虚基类
//	//vbptr虚基类指针指向虚基类表vbtable，查表得到虚基类偏移量
//	//计算出虚基类成员真实地址，完成读写
//{
//
// };
// class tuo :virtual public animal//虚继承
//{
//
// };
// class sheeptuo :public sheep, public tuo
//{
//
// };
// void test01()
//{
//	sheeptuo st;
//	sheep s;
//	s.m_age = 100;
//	//当出现菱形继承的时候，两个父类有同名数据，加作用域区分
//	st.sheep::m_age=18;
//	st.tuo::m_age = 28;
//	//这份数据只要有一个就行，菱形继承导致数据两份，资源浪费
// }

////动态多态
////满足条件：
////1.有继承关系
////2.子类要重写(函数返回类型函数名参数列表完全相同)父类虚函数
////动态多态的使用
////父类的指针或者引用 执行子类对象
// class Animal
//{
// public:
//	virtual void speak()//虚函数
//	{
//		cout << "动物在说话" << endl;
//	}
//	//vfptr 虚函数指针，指向vftable 虚函数表记录虚函数地址&Animal::speak
//
// };
// class Cat:public Animal //子类同样继承vfptr ，当子类重写父类虚函数，
//	//子类中的虚函数表内部会替换成子类的虚函数地址&Cat::speak;但是指针是未发生改变的
//	//当父类的指针或引用指向子类对象的时候，就发生了多态
//{
// public:
//	void speak()
//	{
//		cout << "小猫在说话" << endl;
//	}
// };
////子类就是有一个新的vftable，并且他的vfptr指向这个新的vftable，
////并且这个新的vftable暂时存储的是&animal::speak（），当我在cat类内部重写speak的时候，
////会改写cat的vftable中的地址，写成&cat::speak,animal&不能确定到底调用哪个，
////需要传入cat或者dog才能顺着cat和dog的vfptr去找到对应的vftable中的函数地址，然后
////根据这个地址调用函数(动态绑定)
//
////只要你没给函数加virtual关键字，类根本不会生成虚表，对象里连vfptr这个额外指针都不存在
////，函数地址在编译期就会直接硬编码，参数/变量声明的是什么类型，就百分百调用这个类里对
////应版本的函数，连任何分支判断、查表的额外开销都没有。（静态绑定）
////重点就是多了一个vfptr，需要通过类来查找vftable
// class Dog :public Animal
//{
// public:
//	void speak()
//	{
//		cout << "小狗在说话" << endl;
//	}
// };
// void dospeak(Animal& animal)//地址早绑定，在编译阶段确定函数地址
////如果想执行猫说话，那么这个函数地址不能提前绑定，需要在运行阶段
////进行绑定，晚绑定
//{
//	animal.speak();
//}
// void test01()
//{
//	Cat cat;
//	Dog dog;
//	dospeak(cat);
//	dospeak(dog);
//}
// int main()
//{
//	test01();
//	system("pause");
//	return  0;
//}

// 多态实例
// 普通写法
// class Calculate
//{
// public:
//	int getresult(string oper)
//	{
//		if (oper == "+")
//		{
//			return m_Num1 + m_Num2;
//		}
//		if (oper == "-")
//		{
//			return m_Num1 - m_Num2;
//		}
//		if (oper == "*")
//		{
//			return m_Num1 * m_Num2;
//		}
//	}
//	int m_Num1;
//	int m_Num2;
// };
// void test01()
//{
//	Calculate c;
//	c.m_Num1 = 10;
//	c.m_Num2 = 10;
//	cout << c.m_Num1 << "+" << "=" << c.getresult("+") << endl;
//	cout << c.m_Num1 << "-" << "=" << c.getresult("-") << endl;
//	cout << c.m_Num1 << "*" << "=" << c.getresult("*") << endl;
//	//如果想扩展新的功能要修改源码
//	//在真实的开发中 提倡开闭功能
// }
// int main()
//{
//
//	system("pause");
//	return 0;
// }
////利用多态
////好处
////1.组织结构清晰
////2.可读性强
////3.对于前期后期扩展维护性高
// class AbstractCalculate
//{
// public:
//	virtual int getresult()
//	{
//		return 0;
//	}
//	int m_Num1;
//	int m_Num2;
// };
// class addcalculate:public AbstractCalculate
//{
// public:
//	int getresult()
//	{
//		return m_Num1 + m_Num2;
//	}
// };
// class subcalculate :public AbstractCalculate
//{
// public:
//	int getresult()
//	{
//		return m_Num1 - m_Num2;
//	}
// };
// class mulcalculate :public AbstractCalculate
//{
// public:
//	int getresult()
//	{
//		return m_Num1 * m_Num2;
//	}
// };
// void test01()
//{
//	AbstractCalculate* abc = new addcalculate;
//	//创建抽象指针getresult不知道执行哪个，当给了具体类型之后根据vfptr找vftable来执行对应的getresult，是多态
//	abc->m_Num1= 10;
//	abc->m_Num2= 10;
//	cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->getresult() << endl;
//	delete(abc);
//	abc = NULL;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////纯虚函数与多态类
////纯虚函数写法 virtual 返回值类型 函数名（参数列表）=0；
////当类中有了纯虚函数，这个类称为抽象类(无法实例化对象)
////抽象类子类必须要重写父类中的纯虚函数，否则也属于抽象类
// class base
//{
// public:
//	virtual void func() = 0;
// };
// class son :public base
//{
// public:
//	void func()
//	{
//
//	}
// };
// void test01()
//{
//	base* abc = new son;
//	abc->func();
//	delete(abc);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
//
////多态实例2
// class AbstractDrinking
//{
// public:
//	virtual void boil() = 0;
//	virtual void brew() = 0;
//	virtual void pornincup() = 0;
//	virtual void putsomething() = 0;
//	void makedrink()
//	{
//		boil(); brew(); pornincup(); putsomething();
//	}
// };
// class Coffee :public AbstractDrinking
//{
//	void boil()
//	{
//		cout << "煮农夫山泉" << endl;
//	}
//	void brew()
//	{
//		cout << "冲泡咖啡" << endl;
//
//	}
//	void pornincup()
//	{
//		cout << "倒入咖啡杯" << endl;
//
//	}
//	void putsomething()
//	{
//		cout << "加糖和牛奶" << endl;
//	}
// };
// class Tea :public AbstractDrinking
//{
//	void boil()
//	{
//		cout << "煮农矿泉水" << endl;
//	}
//	void brew()
//	{
//		cout << "冲泡龙井" << endl;
//
//	}
//	void pornincup()
//	{
//		cout << "倒入茶杯" << endl;
//
//	}
//	void putsomething()
//	{
//		cout << "加入枸杞" << endl;
//	}
// };
// void dowork(AbstractDrinking* abs)
//{
//	abs->makedrink();
//	delete(abs);
// }
// void dowork2(AbstractDrinking& abs)
//{
//	abs.makedrink();//一个接口多种实现
// }
// void test01()
//{
//	dowork(new Coffee);
//	Tea c;
//	dowork2(c);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////虚析构和纯虚析构
// class Animal
//{
// public:
//	Animal()
//	{
//		cout << "animal的构造函数" << endl;
//	}
//	virtual void speak() = 0;
//	//virtual ~Animal()
//	//{
//	//	cout << "animal的析构函数" << endl;
//	//}
//	virtual ~Animal() = 0;//虚析构和纯虚析构都需要代码实现
//	//有了纯虚析构之后，这个类也属于抽象类，无法实例化对象
// };
// Animal ::~Animal()
//{
//	cout << "Animal纯虚析构函数调用" << endl;
// }
// class Cat :public Animal
//{
// public:
//	Cat(string name)
//	{
//		m_name = new string(name);
//		cout << "cat的构造函数" << endl;
//	}
//	void speak()
//	{
//		cout << *m_name<<"小猫在说话" << endl;
//	}
//	string *m_name;
//	~Cat()
//	{
//		if (m_name != NULL)
//			delete(m_name);
//		cout << "cat的析构函数" << endl;
//	}
// };
// void test01()
//{
//	Animal* abc = new Cat("Tom");
//	abc->speak();
//	//父类指针在析构的时候不会调用子类析构函数
//	// 导致子类如果有堆区属性，出现内存泄露
//	//因为这里明确animal*abc是Animal类型的，
//	//所以在释放过程中只会调用Animal的析构函数，
//	//只有把Animal的析构函数改成虚析构函数才会调用对应类型的析构函数
//	//注意：编译器会在执行完Cat的析构函数后自动调用父类析构函数
//	delete abc;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 多态案例3
// 先抽象出三个零件的类
// 然后具体出什么厂商的零件，不同厂商的零件调用的工作函数不相同，用到多态
// 创造电脑接口，先构造电脑，然后不同的零件有分别对应的工作函数（多态），然后进行工作函数
// class CPU // CPU
// {
// public:
//     virtual void calculate() = 0;
// };
// class VideoCard // 显卡
// {
// public:
//     virtual void display() = 0;
// };
// class Memory // 内存条
// {
// public:
//     virtual void storage() = 0;
// };

// class IntelCPU : public CPU
// {
// public:
//     virtual void calculate()
//     {
//         cout << "intel的CPU开始计算了" << endl;
//     }
// };
// class IntelVideoCard : public VideoCard
// {
// public:
//     virtual void display()
//     {
//         cout << "intel的显卡开始显示了" << endl;
//     }
// };
// class IntelMemory : public Memory
// {
// public:
//     virtual void storage()
//     {
//         cout << "intel的内存条开始存储了" << endl;
//     }
// };
// class LenovoCPU : public CPU
// {
// public:
//     virtual void calculate()
//     {
//         cout << "Lenovo的CPU开始计算了" << endl;
//     }
// };
// class LenovoVideoCard : public VideoCard
// {
// public:
//     virtual void display()
//     {
//         cout << "Lenovo的显卡开始显示了" << endl;
//     }
// };
// class LenovoMemory : public Memory
// {
// public:
//     virtual void storage()
//     {
//         cout << "Lenovo的内存条开始存储了" << endl;
//     }
// };

// class Computer
// {
// public:
//     Computer(CPU *cpu, VideoCard *videocard, Memory *memory)
//     {
//         m_cpu = cpu;
//         m_videocard = videocard;
//         m_memory = memory;
//     }
//     void work()
//     {
//         m_cpu->calculate();
//         m_videocard->display();
//         m_memory->storage();
//     }
//     ~Computer()
//     {
//         if (m_cpu != NULL)
//         {
//             delete m_cpu;
//             cout << "...." << endl;
//         }
//         if (m_videocard != NULL)
//             delete m_videocard;
//         if (m_memory != NULL)
//             delete m_memory;
//     }

// private:
//     CPU *m_cpu;
//     VideoCard *m_videocard;
//     Memory *m_memory;
// };

// void test01()
// {
//     CPU *intelCPU = new IntelCPU;
//     VideoCard *intelcard = new IntelVideoCard;
//     Memory *intelmemory = new IntelMemory;
//     Computer *computer1 = new Computer(intelCPU, intelcard, intelmemory);
//     computer1->work();
//     delete computer1;
// }
// int main()
// {
//     test01();
//     system("pause");
//     return 0;
// }
