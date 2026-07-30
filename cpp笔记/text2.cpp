
// 文件的读写
#include <fstream>
// 三个类，ofstream（写），ifstream（读）,fstream
// ios::in		为读文件而打开文件
// ios::out		为写文件而打开文件
// ios::ate		初始位置：文件尾
// ios::app		追加方式写文件
// ios::trunc	如果文件存在先删除再创建
// ios::binary   二进制方式
// void test01()
//{
//	ofstream ofs;
//	ofs.open("test.txt", ios::out);
//	ofs << "姓名：张三" << endl;
//	ofs << "性别：男" << endl;
//	ofs << "年龄：18" << endl;
//	ofs.close();
//	ifstream ifs;
//	ifs.open("test.txt", ios::in);
//	if (!ifs.is_open())
//	{
//		cout << "文件打开失败" << endl;
//	}
//	/*char buf[1024];
//	while (ifs >> buf)
//	{
//		cout << buf << endl;
//	}*/
//	//char buf2[1024] = { 0 };
//	//while (ifs.getline(buf2, sizeof(buf2)))
//	//{
//	//	cout << buf2 << endl;
//	//}
//	//string buf;
//	//while (getline(ifs, buf))
//	//{
//	//	cout << buf << endl;
//	//}
//	//ifs.close();
//	char c;
//	while ((c = ifs.get()) != EOF)
//	{
//		cout << c;
//	}//效率过低
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////二进制写文件
// class Person
//{
// public:
//	char m_name[64];
//	int m_age;
// };
// void test01()
//{
//	ofstream ofs;
//	ofs.open("test2.txt", ios::out | ios::binary);
//	Person p = { "张三",18 };
//	ofs.write((const char*)&p, sizeof(Person));
//	//强转为数组地址
//	ofs.close();
//	ifstream ifs;
//	ifs.open("test2.txt", ios::in | ios::binary);
//	if (!ifs.is_open())
//	{
//		cout << "文件打开失败" << endl;
//		return;
//	}
//	Person p2;
//	ifs.read((char*)&p, sizeof(Person));
//	cout << p.m_name << endl << p.m_age << endl;
//	ifs.close();
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
// template<typename T>
////函数模板注意事项
////1.自动类型推导，必须推导出一致的数据类型T才能用
////2.模板必须要确定出T的数据类型，才可以使用
// void func()
//{
//	cout << "func调用" << endl;
// }
// template<typename T>
// void mySwap(T& a, T& b)
//{
//	T temp = a;
//	a = b;
//	b = temp;
// }
// template<typename T>
// void mysort(T arr,int len)
//{
//	for (int i = 0; i < len; i++)
//	{
//		int max = i;
//		for (int j = i + 1; j < len; j++)
//		{
//			if (arr[max] < arr[j])
//			{
//				max = j;
//			}
//		}
//		if (i != max)
//		{
//			mySwap(arr[max], arr[i]);
//		}
//	}
// }
// int main()
//{
//	int a = 10;
//	int b = 200;
//	func<int>();//函数模板即使里面没有未确定的数据类型，也要确定出T的数据类型
//	mySwap<int>(a, b);
//	cout << a << "\t" << b << endl;
//	system("pause");
//	return 0;
// }

// 普通函数与函数模板区别
// 1.普通函数调用可以发生隐式类型转换
// 2.函数模板用自动类型推导，不可以发生隐式类型转换
// 3.函数模板用显示指定类型add<int>(a,c)，可以发生隐式类型转换
// int add(int a, int b)
//{
//	return a + b;
// }
// int main()
//{
//	cout << add(20, 'c')/*隐式类型转换*/ << endl;
//	system("pause");
//	return 0;
// }

////普通函数与函数模板调用规则
////1.如果函数模板和普通函数都可以调用，优先调用普通函数
////2.如果通过空模板参数 函数名<>(参数)  强制调用 函数模板
////3.函数模板可以发生函数重载
////4.如果函数模板可以更好的匹配，优先调用函数模板
////实际开发中不同时出现
// void myprint(int a, int b)
//{
//	cout << "调用的普通函数" << endl;
// }
// template<class T>
// void myprint(T a, T b)
//{
//	cout << "调用的函数模板" << endl;
// }
// template<class T>
// void myprint(T a, T b,T c)
//{
//	cout << "调用的函数重载模板" << endl;
// }
// void test01()
//{
//	int a = 10;
//	int b = 20;
//	int c = 30;
//	myprint(a, b);
//	myprint('a', 'b');
//	myprint<>(a, b);
//	myprint(a, b,c);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 函数模板的局限性
// 不是万能的,有些特定数据类型需要具体化方式做特殊实现，比如想做比较，整型可以但类不可以
// 解决方法：具体化：直接具体化出类的比较函数，通过函数重载解决 （template<>表示模板的特例）
// class Person
//{
//	int age;
// };
// template<class T>
// bool myCompare(T& p1, T& p2)
//{
//	;
// }
// template<>bool myCompare(Person& p1, Person& p2)
//{
//	;
// }

// 类模板
// template<class NameType,class AgeType>
// class person
//{
// public:
//	person(NameType name, AgeType age=int)
//	{
//		this->m_name = name;
//		this->m_age = age;
//	}
//	void showperson()
//	//showperson 是 类模板person的成员函数，不是独立的函数模板，
//	//它的类型参数完全依附于类模板的实例化结果，不需要你单独传<>指定类型。
//	{
//		cout << "name:" << m_name << "\t" << "age:" << m_age <<  endl;
//	}
//	NameType m_name;
//	AgeType m_age;
// };
// void test01()
//{
//	person<string, int> p1("张三", 18);
//	p1.showperson();
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
////类模板和函数模板的区别
////1.类模板没有自动类型推导的方式，即必须写<string,int>
////2.类模板在模板参数列表可以有默认参数AgeType age=int,就只需要写person<string>了

////类模板中成员函数的创建时机
////类模板中成员函数在调用时才创建
// class Person1
//{
// public:
//	void showPerson1()
//	{
//		cout << "Person1 show" << endl;
//		//age.showperson2();不能这么写因为普通类成员函数在调用前就已经创建好了
//	}
//	int age;
// };
// class Person2
//{
// public:
//	void showPerson2()
//	{
//		cout << "Person2 show" << endl;
//	}
// };
//
// template<class T>
// class Myclass
//{
// public:
//	void func1()
//	{
//		obj.showPerson1();
//	}
//	void func2()
//	{
//		obj.showPerson2();
//	}
//	T obj;
// };
//
// void test01()
//{
//	Myclass<Person1>m;
//
//	m.func1();
//	//不报错是因为没有调用func2函数之前都不会生成这个func2函数
//
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////类模板对象做函数参数
////1.指定传入类型//最常用！
////2.参数模板化
////3.整个类模板化
// template<class T1, class T2>
// class Person
//{
// public:
//	Person(T1 name, T2 age)
//	{
//		this->m_name = name;
//		this->m_age = age;
//	}
//	void showPerson()
//	{
//		cout << "姓名：" << m_name << "\t" << "年龄：" << m_age << endl;
//	}
//	T1 m_name;
//	T2 m_age;
// };
////1.指定传入类型
// void printperson(Person<string, int>& p)
//{
//
// }
////2.参数模板化
// template<class T1, class T2>
// void printperson2(Person<T1,T2>& p)
//{
//
// }
////3.整个类模板化
// template<class T>
// void printperson2(T& p)
//{
//
// }
// void test01()
//{
//	Person<string, int> p("张三", 100);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////类模板与继承
// template<class T>
// class Base
//{
//	T m;
// };
// class Son :public Base<int>
//{
//
// };
// template<class T1, class T2>
// class Son2 :public Base<T2>
//{
//	T1 obj;
// };
// void test01()
//{
//	Son2<int,char> s1;//!!!
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////类模板成员函数的类外实现
// template <class T1,class T2>
// class Person
//{
// public:
//	Person(T1 name, T2 age);
//	//{
//	//	this->m_Name = name;
//	//	this->m_age = age;
//	//}
//	void showperson();
//	/*{
//		cout << m_name << "\t" << m_age << endl;
//	}*/
//	T1 m_name;
//	T2 m_age;
// };
////构造函数的类外实现
// template<class T1,class T2>
// Person<T1,T2>::Person(T1 name, T2 age)
//{
//	this->m_Name = name;
//	this->m_age = age;
// }
////成员函数类外实现
// template<class T1, class T2>
// void Person<T1, T2>::showperson()
//{
//	cout << m_name << "\t" << m_age << endl;
// }
// void test01()
//{
//	Person<string, int> p1("zhangsan",19);
//	p1.showperson();
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
//

// 类模板的份文件编写
// 由于类模板在未调用函数之前并没有生成函数，所以找不到函数的实现
//  第一种方法：直接包含源码.cpp
//  第二种方法：将.h和.cpp中的内容写到一起，然后后缀改为.hpp
// template<class T1,class T2>
// class Person
//{
// public:
//	Person(T1 name, T2 age);
//	void showperson();
//	T1 m_name;
//	T2 m_age;
// };
// template<class T1,class T2>
// Person<T1, T2>::Person(T1 name, T2 age)
//{
//	this->m_Name = name;
//	this->m_age = age;
// }
// template<class T1, class T2>
// void Person<T1, T2>::showperson()
//{
//	cout << m_name << "\t" << m_age << endl;
// }

////类模板与友元
// template<class T1,class T2>
// class Person;
//
// template <class T1, class T2>
// void printPerson2(Person<T1, T2>p)
//{
//	cout << p.m_name << p.m_age << endl;
// }
//
// template<class T1,class T2>
// class Person
//{
// public:
//	//全局函数 类内实现
//	friend void printPerson(Person<T1, T2>p)
//	{
//		cout << p.m_name << p.m_age << endl;
//	}
//	//全局函数类外实现
//	//加空模板参数列表
//	//如果全局函数是类外声明，需要让编译器提前知道这个函数模板存在
//	friend void printPerson2<>(Person<T1, T2>p);//普通函数声明,加了<>才是函数模板声明
//
//	Person(T1 name, T2 age)
//	{
//		this->m_name = name;
//		this->m_age = age;
//	}
// private:
//	T1 m_name;
//	T2 m_age;
// };
//
//
// void test01()
//{
//	Person<string, int> p1("张三", 18);
//	printPerson2(p1);
// }
// int main()
//{
//	test01();
//	system("pause");
//	system("cls");
// }

// 类模板案例

template <class T>
class MyArray
{
public:
    MyArray(int capacity)
    {
        this->m_capacity = capacity;
        this->m_size = 0;
        this->pAddress = new T[this->m_capacity];
    }
    MyArray(const MyArray &arr)
    {
        this->m_capacity = arr.m_capacity;
        this->m_size = arr.m_size;
        this->pAddress = new T[this->m_capacity];
        for (int i = 0; i < this->m_size; i++)
        {
            this->pAddress[i] = arr.pAddress[i];
        }
    }
    MyArray &operator=(const MyArray &arr)
    {
        if (this->pAddress != NULL)
        {
            delete[] this->pAddress;
            this->pAddress = NULL;
            this->m_capacity = 0;
            this->m_size = 0;
        }
        this->m_capacity = arr.m_capacity;
        this->m_size = arr.m_size;
        this->pAddress = new T[this->m_capacity];
        for (int i = 0; i < this->m_size; i++)
        {
            this->pAddress[i] = arr.pAddress[i];
        }
        return *this;
    }

    void push_back(const T &value)
    {
        if (this->m_capacity == this->m_size)
        {
            return;
        }
        this->pAddress[this->m_size] = value;
        this->m_size++;
    }

    void delete_back()
    {
        if (this->m_size == 0)
        {
            return;
        }
        this->m_size--;
    }

    T &operator[](int index)
    {
        return this->pAddress[index];
    }

    int getcapacity()
    {
        return this->m_capacity;
    }

    int getsize()
    {
        return this->m_size;
    }

    ~MyArray()
    {
        if (this->pAddress != NULL)
        {
            delete[] this->pAddress;
            this->pAddress = NULL;
        }
    }

private:
    T *pAddress;
    int m_capacity;
    int m_size;
};

void printIntArray(MyArray<int> &arr)
{
    for (int i = 0; i < arr.getsize(); i++)
    {
        cout << arr[i];
    }
}
class Person
{
public:
    Person() {}; // 写了含参构造会自动删除无参构造，在new Person[]的时候会导致没有无参构造可用!!
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }
    int m_age;
    string m_name;
};

void printPersonArray(MyArray<Person> &arr1) // const修饰不允许调用没有const修饰的成员函数
{
    for (int i = 0; i < arr1.getsize(); i++)
    {
        cout << arr1[i].m_name << "\t" << arr1[i].m_age << endl;
    }
}

void test01()
{
    MyArray<int> arr1(5);
    MyArray<int> arr2(arr1);
    MyArray<int> arr3 = arr1;
}
void test02()
{
    Person p1("张三", 18);
    Person p2("张三", 18);
    Person p3("张三", 18);
    Person p4("张三", 18);
    MyArray<Person> arr1(4);
    arr1.push_back(p1);
    arr1.push_back(p2);
    arr1.push_back(p3);
    arr1.push_back(p4);
    printPersonArray(arr1);
}
int main()
{
    // test01();
    test02();
    system("pause");
    system("cls");
}