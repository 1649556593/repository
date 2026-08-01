// C++面向对象：封装，继承，多态
// 泛型编程：模板，两者目的就是复用性的提高
// STL初识(Standard Template Library，标准模板库)
// STL广义上分为容器，算法，迭代器；容器和算法之间通过迭代器进行无缝衔接
// STL几乎所有代码都采用了模板类和模板函数

// STL六大组件：容器，算法，迭代器，仿函数，适配器，空间配置器
// 1.容器：各种数据结构，如vector，list，deque，set，map，用来存放数据
//  序列式容器：强调值的排序，序列式容器中的每个元素均有固定的位置
//  关联式容器：二叉树结构，各个元素之间没有严格的物理上的顺序关系
// 2.算法：常用算法，如sort，find，copy，for_each
//  质变算法和非质变算法
// 3.迭代器：扮演了容器与算法的胶合剂
//  算法需要通过迭代器才能访问容器中的数据，每个容器都有自己专属的迭代器
//  输入（只读），输出（只写），前向（读写，只能向前推进），双向（读写，前后），随机访问（可跳跃方式访问）
//  后两个更常用
// 4.仿函数：行为类似函数，可以作为算法的某种策略
// 5.适配器：一种用来修饰容器或者仿函数或迭代器接口的东西
// 6.空间适配器：负责空间的配置和管理

// 容器:vector
// 算法：for_each
// 迭代器：vector<int>::iterator
#include <vector>
// void myprint(int val)
//{
//	cout << val << endl;
// }
// void test01()
//{
//	vector<int>v;
//	//插入数据
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//	v.push_back(60);
//	//通过迭代器访问容器中数据
//	vector<int>::iterator itBegin = v.begin();//起始迭代器 指向容器中第一个元素
//	vector<int>::iterator itEnd = v.end();//起始迭代器 指向容器中第一个元素
//	while (itBegin != itEnd)
//	{
//		cout << *itBegin << endl;
//		itBegin++;
//	}
//
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << *it << endl;
//	}
//
//	for_each(v.begin(), v.end(), myprint);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// class Person
//{
// public:
//	Person(string name, int age)
//	{
//		this -> m_name = name;
//		this->m_age = age;
//	}
//	string m_name;
//	int m_age;
// };
// void myprint(Person& p)
//{
//	cout << p.m_name << "\t" << p.m_age << endl;
// }
// void test01()
//{
//	vector<Person>v;
//	Person p1("aaa", 10);
//	Person p2("baa", 10);
//	Person p3("caa", 10);
//	Person p4("daa", 10);
//	Person p5("eaa", 10);
//	v.push_back(p1);
//	v.push_back(p2);
//	v.push_back(p3);
//	v.push_back(p4);
//	v.push_back(p5);
//
//	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << (*it).m_name << "\t" << (*it).m_age << endl;
//	}
//
//	for_each(v.begin(), v.end(), myprint);
//
// }
// void test02()
//{
//	vector<Person*>v;
//	Person p1("aaa", 10);
//	Person p2("baa", 10);
//	Person p3("caa", 10);
//	Person p4("daa", 10);
//	Person p5("eaa", 10);
//	v.push_back(&p1);
//	v.push_back(&p2);
//	v.push_back(&p3);
//	v.push_back(&p4);
//	v.push_back(&p5);
//	for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << (*it)->m_name << "\t" << (*it)->m_age << endl;
//	}
// }
// int main()
//{
//	test02();
//	system("pause");
//	return 0;
// }

////容器嵌套容器
// void myprint(vector<int> v)//myprint的参数就是这一层vector里存储的参数类型，底层是func（*it）
//{
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << (*it) << endl;
//	}
// }
// void  test01()
//{
//	vector<vector<int>>v;
//	vector<int>v1;
//	vector<int>v2;
//	vector<int>v3;
//	vector<int>v4;
//	for (int i = 0; i < 4; i++)
//	{
//		v1.push_back(i);
//		v2.push_back(i+1);
//		v3.push_back(i+2);
//		v4.push_back(i+3);
//	}
//	v.push_back(v1);
//	v.push_back(v2);
//	v.push_back(v3);
//	v.push_back(v4);
//
//	for_each(v.begin(), v.end(), myprint);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////string 是一个类，类的内部封装了char*，是一个char*的容器
////string& operator=(const char* s);		//char*类型字符串 赋值给当前的字符串
////string& operator=(const string& s);		//字符赋值给当前的字符串
////string& operator=(char c);				//把字符串s赋给当前的字符串
////string& assign(const char* s);			//把字符串s赋给当前的字符串
////string& assign(const char* s, int n);	//把字符串s的前n个字符赋给当前的字符串
////string& assign(const string& s);		//把字符串s赋给当前字符串
////string& assign(int n, char c);			//用n个字符c赋给当前字符串
//
// string& append(const string& s, int posd, int n);
// void test01()
//{
//	string str1 = "helloworld";
//	string str2 = str1;
//	string str3;//不允许初始化为字符
//	str3 = 'a';
//	string str4;
//	str4.assign("helloworld");
//	string str5;
//	str5.assign("helloworld",5);
//	string str6;
//	str6.assign(str5);
//	string str7;
//	str7.assign(10,'w');
//}
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
//}

////string字符串拼接
////string& operator+=(const char* str);
////string& operator+=(const char c);
////string& operator+=(const string& str);
////string& append(const char* s);
////string& append(const char* s, int n);
////string& append(const string& s);
////重载+=操作符
////重载+=操作符
////重载+=操作符
////把字符串s连接到当前字符串结尾
////把字符串s的前n个字符连接到当前字符串结尾
////同operator+=(const string& str)
////字符串s中从pos开始的n个字符连接到字符串结尾
// void test01()
//{
//	string str1 = "我";
//	str1 += "爱玩游戏";
//	str1 += ':';
//	string str2 = "地下城";
//	str1 += str2;
//
//	string str3 = "I";
//	str3.append(" LOVE");
//	//str3.append("023415230156410.015",10);
//	str3.append("023415230156410.015",1, 3);//调整截取位置和 字符个数
//
//	str3.append(str2);
//
//	cout << str1 << endl;
//	cout << str3 << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////int find(const string& str, int pos = 0) const;		//查找str第一次出现位置,从pos开始查找
////int find(const char* s, int pos = 0) const;			//查找s第一次出现位置,从pos开始查找
////int find(const char* s, int pos, int n) const;		//从pos位置查找s的前n个字符第一次位置
////int find(const char c, int pos = 0) const;			//查找字符c第一次出现位置
////int rfind(const string& str, int pos = npos) const;	//查找str最后一次位置,从pos开始查找
////int rfind(const char* s, int pos = npos) const;		//查找s最后一次出现位置,从pos开始查找
////int rfind(const char* s, int pos, int n) const;		//从pos查找s的前n个字符最后一次位置
////int rfind(const char c, int pos = 0) const;			//查找字符c最后一次出现位置
////string& replace(int pos, int n, const string& str);	//替换从pos开始n个字符为字符串str
////string& replace(int pos, int n, const char* s);		//替换从pos开始的n个字符为字符串s
// void test01()
//{
//	string str1 = "abcdefg";
//	cout << str1.find("de") << endl;//rfind是从左往右查，如果没找到就返回-1
//	cout << str1.rfind("de") << endl;//rfind从右往左查找
//
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////string的字符串比较
////int compare(const string& s) const;	//与字符串s比较
////int compare(const char* s) const;		//与字符串s比较
////等于返回0，前面的大于后面的返回正数，否则负数
// void test01()
//{
//	string str1 = "helloworld";
//	string str2 = "hello";
//	if (str1.compare(str2) == 0)
//	{
//		cout << "str1=str2" << endl;
//	}
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////字符存取
////char& operator[](int n);	//通过[]方式取字符
////char& at(int n);			//通过at方法获取字符
// void test01()
//{
//	string str = "hello";
//	for (int i = 0; i < str.size(); i++)
//	{
//		cout << str[i] << endl;
//		cout << str.at(i) << endl;
//	}
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////字符串插入删除
////string& insert(int pos, const char* s);		//插入字符串
////string& insert(int pos, const string& str);	//插入字符串
////string& insert(int pos, int n, char c);		//在指定位置插入n个字符c
////string& erase(int pos, int n = npos);			//删除从Pos开始的n个字符
// void test01()
//{
//	string str1 = "hello";
//	cout << str1.insert(1, "333") << endl;
//	cout << str1.erase(1, 3) << endl;
//
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
//
////获取想要的字串
////string substr(int pos0, int n = npos)const;//返回由pos开始的n个字符组成的字符串
// void test01()
//{
//	string str = "abc";
//	cout << str.substr(1, 2) << endl;
//	string str2 = "zhangsan@sina.com";
//	string username = str2.substr(0, str2.find("@"));
//	cout << username << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;

// vector容器 ：单端数组
// 可以动态扩展:找更大的空间将元数据拷贝新空间，释放原空间
// vector的迭代器是支持随机访问的迭代器

////vector<T> v;						//采用模板实现类实现，默认构造函数
////vector(v.begin(), v.end());		//将v[begin(),end())区间中的元素拷贝给本身。
////vector(n, elem);					//构造函数将n个elem拷贝给本身。
////vector(const vector& vec);		//拷贝构造函数。
// void printvector(vector<int>& v1)
//{
//	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
//
// void test01()
//{
//	vector<int>v1;//默认构造
//	for (int i = 0; i < 10; i++)
//	{
//		v1.push_back(i);
//	}
//	printvector(v1);
//	vector<int>v2(v1.begin(), v1.end());
//	printvector(v2);
//	vector<int>v3(10, 100);
//	printvector(v3);
//	vector<int>v3(v2);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////vector& operator=(const vector& vec);	//重载等号操作符
////assign(beg, end);						//将[beg,end)区间中的数据拷贝赋值给本身。
////assign(n, elem);						//将n个elem拷贝赋值给本身。
// void printvector(vector<int>& v1)
//{
//	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	vector<int>v1;
//	for (int i = 0; i < 10; i++)
//	{
//		v1.push_back(i);
//	}
//	printvector(v1);
//
//	vector<int>v2;
//	v2 = v1;
//	printvector(v2);
//
//	vector<int>v3;
//	v3.assign(v2.begin(),v2.end());
//	printvector(v3);
//
//	vector<int>v4;
//	v4.assign(10, 100);
//	printvector(v4);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

//////vector容量和大小
////empty();			//判断容器是否为空
////capacity();		//容器的容量
////size();			//返回容器中元素的个数
////resize(int num);	//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
////					//如果容器变短，则末尾超出容器长度的元素被删除。/
////resize(int num，elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
////					//如果容器变短，则末尾超出容器长度的元素被删除
// void printvector(vector<int>& v1)
//{
//	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	vector<int>v1;
//	for (int i = 0; i < 10; i++)
//	{
//		v1.push_back(i);
//	}
//	printvector(v1);
//	if (v1.empty())
//	{
//		cout << "v1为空" << endl;
//	}
//	cout << v1.capacity() << endl;
//	cout << v1.size() << endl;
//
//
//	v1.resize(15);//默认0填充新的位置
//	printvector(v1);
//	cout << v1.capacity() << endl;
//	cout << v1.size() << endl;
//
//
//	v1.resize(3);
//	printvector(v1);
//	cout << v1.capacity() << endl;
//	cout << v1.size() << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////vector的插入和删除
// push_back(ele);									//尾部插入元素ele
// pop_back();										//删除最后一个元素
// insert(const_iterator pos, ele);					//迭代器指向位置pos插入元素ele
// insert(const_iterator pos, int count, ele);		//代器指向位置pos插入count个元素ele
// erase(const_iterator pos);						//删除迭代器指向的元素
// erase(const_iterator start, const_iterator end);	//删除代器从start到end之间的元素
// clear();											//删除容器中所有元素
//
// void printvector(vector<int>& v1)
//{
//	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	vector<int>v1;
//	for (int i = 0; i < 10; i++)
//	{
//		v1.push_back(i);
//	}
//	v1.pop_back();
//	v1.pop_back();
//	v1.pop_back();
//	v1.pop_back();
//	printvector(v1);
//
//	v1.insert(v1.begin(), 3 ,100);
//	printvector(v1);
//
//	v1.erase(v1.begin(),v1.begin()+3);
//	printvector(v1);
//
//	v1.clear();
//	printvector(v1);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////vector数据存取
////at(int idx);		//返回索引idx所指的数据
////operator[];		//返回索引idx所指的数据
////front();			//返回容器中第一个数据元素
////back();			//返回容器中最后一个数据元素
//
//
// void printvector(vector<int>& v1)
//{
//	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
//	{
//		cout << *it << endl;
//	}
//}
// void test01()
//{
//	vector<int>v1;
//	for (int i = 0; i < 10; i++)
//	{
//		v1.push_back(i);
//	}
//	for (int i = 0; i < v1.size(); i++)
//	{
//		cout << v1[i] << endl;
//		cout << v1.at(i) << endl;
//	}
//	cout << v1.front() << endl;
//	cout << v1.back() << endl;
//
//}
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
//}

////vector容器的互换
////1.基本使用
// void printvector(vector<int>& v1)
//{
//	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	vector<int>v1;
//	for (int i = 0; i < 10; i++)
//	{
//		v1.push_back(i);
//	}
//	printvector(v1);
//	vector<int>v2;
//	for (int i = 10; i > 0; i--)
//	{
//		v1.push_back(i);
//	}
//	printvector(v1);
//	v1.swap(v2);
// }
// void test02();
// int main()
//{
//	//test01();
//	test02();
//	system("pause");
//	return 0;
// }
////2.实际用途
////巧用swap可以收缩内存空间
// void test02()
//{
//	vector<int>v;
//	for (int i = 0; i < 1000000; i++)
//	{
//		v.push_back(i);
//	}
//	cout << v.capacity() << endl;
//	cout << v.size() << endl;
//
//	v.resize(3);
//	cout << v.capacity() << endl;
//	cout << v.size() << endl;
//	vector<int>(v).swap(v);//通过拷贝构造创建临时匿名对象
//	//拷贝构造种size是多少就开辟多少空间，然后和v交换，把大片冗余空间
//	//交换个临时匿名对象，在这行代码执行结束后系统自动释放临时匿名对象
//	cout << v.capacity() << endl;
//	cout << v.size() << endl;
// }

////vector预留空间
////reserve(int len);//预留len个元素长度，预留空间不初始化，元素不可以访问
// void test01()
//{
//	vector<int>v;
//	v.reserve(100000);
//	int num = 0;
//	int* p = NULL;
//	for (int i = 0; i < 100000; i++)
//	{
//		v.push_back(i);
//		if (p != &v[0])
//		{
//			p = &v[0];
//			num++;
//		}
//		//用来计算一共开辟了多少次内存
//	}
//	cout << num << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// deque容器
// deque:双端数组，可以对头端进行插入删除操作
// deque和vector区别
// vector对于头部的插入删除效率低，数据量越大，效率越低
// deque相对vector来说，对头部的插入删除速度回比vector快
// vector访问元素时速度比deque快

// deque构造
// deque<T> deqT;          //默认构造形式
// deque(beg, end);        //构造函数将[beg, end)区间中的元素拷贝给本身。
// deque(n, elem);         //构造函数将n个elem拷贝给本身。
// deque(const deque& deq);//拷贝构造函数

#include <deque>
// void printdeque(const deque<int>&d1)//只读设置
//{
//	for (deque<int>::const_iterator it = d1.begin(); it != d1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	deque<int>d1;
//	for (int i = 0; i < 10; i++)
//	{
//		d1.push_back(i);
//	}
//	printdeque(d1);
//	deque<int>d2(d1.begin(), d1.end());
//	deque<int>d3(10, 100);
//	deque<int>d4(d3);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

//// 功能描述：
//
////给deque容器进行赋值
////函数原型：
//
////deque& operator=(const deque& deq);	//重载等号操作符
////assign(beg, end);						//将[beg, end)区间中的数据拷贝赋值给本身。
////assign(n, elem);						//将n个elem拷贝赋值给本身。
////和vector基本完全相同
// void printdeque(const deque<int>&d1)
//{
//	for (deque<int>::const_iterator it = d1.begin(); it != d1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	deque<int>d1;
//	for (int i = 0; i < 10; i++)
//	{
//		d1.push_back(i);
//	}
//	deque<int>d2;
//	d2 = d1;
//	deque<int>d3;
//	d3.assign(d1.begin(), d1.end());
//	deque<int>d4;
//	d4.assign(10, 100);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////// 功能描述：
////// 对deque容器的大小进行操作
////
////// 函数原型：
////deque没有容量的限制
////deque.empty();				//判断容器是否为空
////deque.size();					//返回容器中元素的个数
////deque.resize(num);			//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。
////								//如果容器变短，则末尾超出容器长度的元素被删除。
////deque.resize(num, elem);		//重新指定容器的长度为num,若容器变长，则以elem值填充新位置。
////								//如果容器变短，则末尾超出容器长度的元素被删
// void printdeque(const deque<int>&d1)
//{
//	for (deque<int>::const_iterator it = d1.begin(); it != d1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	deque<int>d1;
//	for (int i = 0; i < 10; i++)
//	{
//		d1.push_back(i);
//	}
//	cout << d1.size() << endl;
//	if (d1.empty())
//	{
//		cout << "d1为空" << endl;
//	}
//	d1.resize(15);
//	cout << d1.size() << endl;
//	printdeque(d1);
//
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

//////deque 插入和删除
////// 向deque容器中插入和删除数据
////// 函数原型：
////// 两端插入操作：
////push_back(elem);   //在容器尾部添加一个数据
////push_front(elem);  //在容器头部插入一个数据
////pop_back();        //删除容器最后一个数据
////pop_front();       //删除容器第一个数据
////
////// 指定位置操作：
////insert(pos, elem);      //在pos位置插入一个elem元素的拷贝，返回新数据的位置。
////insert(pos, n, elem);    //在pos位置插入n个elem数据，无返回值。
////insert(pos, beg, end);   //在pos位置插入[beg,end)区间的数据，无返回值。
////clear();               //清空容器的所有数据
////erase(beg, end);        //删除[beg,end)区间的数据，返回下一个数据的位置。
////erase(pos);            //删除pos位置的数据，返回下一个数据的位置。
// void printdeque(const deque<int>&d1)
//{
//	for (deque<int>::const_iterator it = d1.begin(); it != d1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	deque<int>d1;
//	for (int i = 0; i < 10; i++)
//	{
//		d1.push_back(i);
//		d1.push_front(i);
//	}
//	d1.pop_back();
//	d1.pop_front();
//	d1.insert(d1.begin(), 1000);
//	d1.insert(d1.begin(),2, 1000);
//	//printdeque(d1);
//
//	deque<int>d2;
//	d2.push_back(1);
//	d2.push_back(2);
//	d2.push_back(3);
//	d2.push_back(4);
//	d2.insert(d2.begin(),d2.begin(), d2.end());
//	d2.erase(d2.begin(), d2.begin() + 4);
//	d2.erase(d2.begin());
//	d2.clear();
//	printdeque(d2);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 数据存取
// 功能描述：
// 对deque中的数据的存取操作

//// 函数原型：
////at(int idx);   //返回索引idx所指的数据
////operator[];    //返回索引idx所指的数据
////front();       //返回容器中第一个数据元素
////back();        //返回容器中最后一个数据元素
// void printdeque(const deque<int>&d1)
//{
//	for (deque<int>::const_iterator it = d1.begin(); it != d1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	deque<int>d1;
//	for (int i = 0; i < 10; i++)
//	{
//		d1.push_back(i);
//	}
//	for (int i = 0; i < d1.size(); i++)
//	{
//		cout << d1[i] << " ";
//		cout << d1.at(i)<<" ";
//	}
//	cout << endl;
//	cout << d1.front() << endl;
//	cout << d1.back() << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////deque的排序
// void printdeque(const deque<int>& d1)
//{
//	for (deque<int>::const_iterator it = d1.begin(); it != d1.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
// }
// void test01()
//{
//	deque<int>d1;
//	d1.push_back(100);
//	d1.push_back(600);
//	d1.push_back(300);
//	d1.push_back(900);
//	printdeque(d1);
//	sort(d1.begin(), d1.end());//默认从小到大
//	printdeque(d1);
//
// }
////对于支持随机访问的迭代器的容器都可以利用sort算法直接对其进行排序
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 案例：评委打分
// 初始化Person，把选手存在vector容器里
// 把成绩存在deque容器里，排序去头去尾，把成绩录入选手当中
// class Person
//{
// public:
//	Person(string name, int score)
//	{
//		this->m_name = name;
//		this->ave_score = score;
//	}
//	string m_name;
//	int ave_score;
// };
// void createPerson(vector<Person>& v)
//{
//	string str = "ABCDE";
//	for (int i = 0; i < 5; i++)
//	{
//		string name = "选手";
//		name += str[i];
//		int score = 0;
//		Person p(name, score);
//		v.push_back(p);
//	}
//	//for (vector<Person>::const_iterator it = v.begin(); it != v.end(); it++)
//	//{
//	//	cout << (*it).m_name << endl;
//	//}
// }
// void setscore(vector<Person>& v)
//{
//	srand((unsigned int)time(NULL));
//	for (int i = 0; i < 5; i++)
//	{
//		deque<int>d;
//		for (int i = 0; i < 10; i++)
//		{
//			int score = rand() % 41 + 60;
//			d.push_back(score);
//			cout << score << " ";
//		}
//		cout << endl;
//		sort(d.begin(), d.end());
//		d.pop_back();
//		d.pop_front();
//		int sum = 0;
//		for (int i = 0; i < d.size(); i++)
//		{
//			sum += d[i];
//			cout << d[i] << " ";
//		}
//		cout << endl;
//		v[i].ave_score = sum / d.size();
//		cout << v[i].m_name << "\t"<<v[i].ave_score<<endl;
//	}
// }
// int main()
//{
//	vector<Person> v;
//	createPerson(v);
//	setscore(v);
//	system("pause");
//	return 0;
// }

////stack容器：栈
////stack 常用接口
//
////// 构造函数:
////stack<T> stk;          //stack采用模板类实现， stack对象的默认构造形式
////stack(const stack& stk); //拷贝构造函数
////
////// 赋值操作:
////stack& operator=(const stack& stk); //重载等号操作符
////
////// 数据存取:
////push(elem); //向栈顶添加元素
////pop();      //从栈顶移除第一个元素
////top();      //返回栈顶元素
////
////// 大小操作:
////empty();    //判断堆栈是否为空
////size();     //返回栈的大小
// #include<stack>
// void test01()
//{
//	stack<int>s;
//	s.push(10);
//	s.push(20);
//	s.push(30);
//	s.push(40);
//	s.push(50);
//	if (s.empty())
//	{
//		cout << "栈为空" << endl;
//	}
//	cout << s.size() << endl;
//	cout << s.top() << endl;
//	s.pop();
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// queue容器:队列
// 只有队头和队尾可以被访问，因此不允许遍历行为
//  queue 相关接口
// queue<T> que;          //queue采用模板类实现，queue对象的默认构造形式
// queue(const queue& que); //拷贝构造函数
//
//// 赋值操作:
// queue& operator=(const queue& que); //重载等号操作符
//
//// 数据存取:
// push(elem); //往队尾添加元素
// pop();      //从队头移除第一个元素
// back();     //返回最后一个元素
// front();    //返回第一个元素
//
//// 大小操作:
// empty();    //判断队列是否为空
// size();     //返回队列的大小
// #include<queue>
// class Person
//{
//
// public:
//	Person(string name, int age)
//	{
//		this->m_age = age;
//		this->m_name = name;
//	}
//	int m_age;
//	string m_name;
// };
// void test01()
//{
//	queue<Person>q;
//	Person p1("tangseng", 18);
//	Person p2("shaseng", 18);
//	Person p3("sunwukong", 18);
//	Person p4("bailongma", 18);
//	Person p5("xiaolongnv", 18);
//	q.push(p1);
//	q.push(p2);
//	q.push(p3);
//	q.push(p4);
//	q.push(p5);
//	if(!q.empty())
//	{
//		cout << q.front().m_name << "\t" << q.front().m_age << endl;
//		cout << q.back().m_name << "\t" << q.back().m_age << endl;
//	}
//	cout << q.size() << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////list容器:双向循环链表
////可以对任意位置进行快速插入和删除,不会导致空间浪费
////缺点：遍历速度慢，占用空间大
////list<T> lst;          //list采用采用模板类实现,对象的默认构造形式:
////list(beg, end);        //构造函数将[beg, end)区间中的元素拷贝给本身。
////list(n, elem);         //构造函数将n个elem拷贝给本身。
////list(const list& lst);//拷贝构造函数。
// #include<list>
// void printlist(list<int>& l)
//{
//	for (list<int>::const_iterator it=l.begin();it!=l.end();it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	list<int>l;
//	l.push_back(10);
//	l.push_back(20);
//	l.push_back(30);
//	l.push_back(40);
//	l.push_back(50);
//	l.push_back(60);
//	printlist(l);
//	list<int>l2 (l);
//	list<int>l3(l.begin(), l.end());
//	list<int>l4(10, 1000);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

//// 给list容器进行赋值，以及交换list容器
//// 函数原型:
////assign(beg, end);        //将[beg, end)区间中的数据拷贝赋值给本身。
////assign(n, elem);         //将n个elem拷贝赋值给本身。
////list& operator=(const list& lst); //重载等号操作符
////swap(lst);               //将lst与本身的元素互换。
// #include<list>
// void printlist(list<int>& l)
//{
//	for (list<int>::const_iterator it=l.begin();it!=l.end();it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	list<int>l;
//	l.push_back(10);
//	l.push_back(20);
//	l.push_back(30);
//	l.push_back(40);
//	l.push_back(50);
//	l.push_back(60);
//	printlist(l);
//	list<int>l2 = l;
//	list<int>l3;
//	l3.assign(l2.begin(), l2.end());
//	list<int>l4;
//	l4.assign(10, 100);
//	l3.swap(l4);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////容器大小操作
////size();			//返回容器中元素的个数 函数原型:
////empty();			//判断容器是否为空
////resize(num);		//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
//					//如果容器变短，则末尾超出容器长度的元素被删除。
////resize(num, elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
//					//如果容器变短，则末尾超出容器长度的元素被删除。
// #include<list>
// void printlist(list<int>& l)
//{
//	for (list<int>::const_iterator it=l.begin();it!=l.end();it++)
//	{
//		cout << *it << endl;
//	}
//}
// void test01()
//{
//	list<int>l;
//	l.push_back(10);
//	l.push_back(20);
//	l.push_back(30);
//	l.push_back(40);
//	l.push_back(50);
//	l.push_back(60);
//	if (l.empty())
//	{
//		cout << "l为空" << endl;
//	}
//	cout << l.size() << endl;
//	l.resize(10,1000);//用指定数字填充空位
//	printlist(l);
//}
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
//}

////list插入和删除
////// 对list容器进行数据的插入和删除
//// 函数原型:
////push_back(elem);     //在容器尾部加入一个元素
////pop_back();          //删除容器中最后一个元素
////push_front(elem);    //在容器开头插入一个元素
////pop_front();         //从容器开头移除第一个元素
////insert(pos, elem);    //在pos位置插elem元素的拷贝，返回新数据的位置。
////insert(pos, n, elem);  //在pos位置插入n个elem数据，无返回值。
////insert(pos, beg, end); //在pos位置插入[beg,end)区间的数据，无返回值。
////clear();             //移除容器的所有数据
////erase(beg, end);      //删除[beg,end)区间的数据，返回下一个数据的位置。
////erase(pos);          //删除pos位置的数据，返回下一个数据的位置。
////remove(elem);        //删除容器中所有与elem值匹配的元素。
//
#include <list>
// void printlist(list<int>& l)
//{
//	for (list<int>::const_iterator it=l.begin();it!=l.end();it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	list<int>l;
//	l.push_back(10);
//	l.push_back(20);
//	l.push_back(30);
//	l.push_back(40);
//	l.push_front(100);
//	l.push_front(300);
//	l.pop_back();
//	l.pop_front();
//	l.insert(l.begin(), 1000);
//	l.insert(l.end(),3, 1000);
//	l.insert(l.begin(), l.begin(), l.end());
//	//l.erase(l.begin(), l.end());
//	l.remove(1000);
//	printlist(l);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// list数据存取
//  函数原型:
// front(); //返回第一个元素。
// back();  //返回最后一个元素。
// 由于内存空间不连续，所以不存在operator[],at()
// list迭代器不支持随机访问,支持双向

////list反转和排序
////reverse();
////sort();
// void printlist(list<int>& l)
//{
//	for (list<int>::const_iterator it=l.begin();it!=l.end();it++)
//	{
//		cout << *it << endl;
//	}
// }
// bool mycompare(int v1,int v2)
//{
//	return v1 > v2;
// }
// void test01()
//{
//	list<int>l;
//	l.push_back(10);
//	l.push_back(40);
//	l.push_back(20);
//	l.push_back(80);
//	l.reverse();
//	printlist(l);
//	//所有不支持随机迭代器的容器，不可以用标准的排序算法
//	//不支持随即迭代器的容器内部会提供算法
//	l.sort();
//	l.sort(mycompare);
//	printlist(l);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////排序案例
// class Person
//{
// public:
//	Person(string name, int age, int height)
//	{
//		this->m_age = age;
//		this->m_height = height;
//		this->m_name = name;
//	}
//	string m_name;
//	int m_age;
//	int m_height;
// };
// int mycompare(Person& p1, Person& p2)
//{
//	if (p1.m_age != p2.m_age)
//		return (p1.m_age) < (p2.m_age);
//	else
//		return (p1.m_height) < (p2.m_height);
// }//!!!自定义函数里面，前者小于后者是从小到大；
// void printlist(list<Person>&l)
//{
//	for (list<Person>::const_iterator it = l.begin(); it != l.end(); it++)
//	{
//		cout<<(*it).m_name << "\t"
//			<< (*it).m_age << "\t"
//			<< (*it).m_height << endl;
//	}
// }
////"\t"是自动将后续的文本跳转到下一个预设的对齐位置，8个空格
// void test01()
//{
//	list<Person>L1;
//	Person p1("liubei",24,180);
//	Person p2("guanyu", 20,190);
//	Person p3("caocao", 23,183);
//	Person p4("zhangf", 20,172);
//	Person p5("zhugl", 25,189);
//	Person p6("zhouyu", 20,180);
//	L1.push_back(p1);
//	L1.push_back(p2);
//	L1.push_back(p3);
//	L1.push_back(p4);
//	L1.push_back(p5);
//	L1.push_back(p6);
//	L1.sort(mycompare);
//	printlist(L1);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////set/multiset容器
////所有容器会在插入时自动排序,底层结构是二叉树实现
////set不允许容器中有重复的元素
////multiset允许容器中有重复的元素
#include <set>
////set构造和赋值
////构造
////set<T> st;
////set st1(const set& st)
////赋值
////set& operator=(const set& st)
// void printset(set<int>& s1)
//{
//	for (set<int>::const_iterator it = s1.begin(); it != s1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	set<int>s1;
//	s1.insert(10);//没有push_back
//	s1.insert(60);
//	s1.insert(40);
//	s1.insert(90);
//	s1.insert(1000);
//	s1.insert(789);
//	s1.insert(488);
//	printset(s1);
//
//	set<int>s2(s1);
//
//	set<int>s3;
//	s3 = s2;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// set的大小和交换
//  函数原型:
// size();    //返回容器中元素的数目
// empty();   //判断容器是否为空
// swap(st);  //交换两个集合容器
// set数据不能重复，因此无法重新设置大小resize，以免默认设置0重复数据
// void printset(set<int>& s1)
//{
//	for (set<int>::const_iterator it = s1.begin(); it != s1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	set<int>s1;
//	s1.insert(10);
//	s1.insert(80);
//	s1.insert(30);
//	s1.insert(40);
//	s1.insert(5);
//	if (s1.empty())
//	{
//		cout << "容器为空" << endl;
//	}
//	cout << s1.size() << endl;
//	set<int>s2;
//	s2.swap(s1);
//	printset(s1);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////  set插入和删除
//// 功能描述：
//// set容器进行插入数据和删除数据
//
////insert(elem);      //在容器中插入元素。
////clear();           //清除所有元素
////erase(pos);        //删除pos迭代器所指的元素，返回下一个元素的迭代器。
////erase(beg, end);   //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
////erase(elem);       //删除容器中值为elem的元素。
//
// void printset(set<int>& s1)
//{
//	for (set<int>::const_iterator it = s1.begin(); it != s1.end(); it++)
//	{
//		cout << *it << endl;
//	}
//}
// void test01()
//{
//	set<int>s1;
//	s1.insert(10);
//	s1.insert(80);
//	s1.insert(30);
//	s1.insert(40);
//	s1.insert(5);
//	s1.erase(s1.begin());
//	s1.erase(++s1.begin());
//	s1.erase(++s1.begin(),--s1.end());
//	printset(s1);
//	s1.clear();
//	printset(s1);
//}
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
//}

////set查找和统计
////find(key)		//查找key是否存在，若存在则返回该元素的迭代器，不存在则返回set.end()
////count(count)	//统计key元素的个数

// void printset(set<int> &s1)
// {
//     for (set<int>::const_iterator it = s1.begin(); it != s1.end(); it++)
//     {
//         cout << *it << endl;
//     }
// }
// void test01()
//{
//	set<int>s1;
//	s1.insert(10);
//	s1.insert(80);
//	s1.insert(30);
//	s1.insert(40);
//	s1.insert(5);
//	set<int>::const_iterator it=s1.find(5);
//	if (it == s1.end())
//	{
//		cout << "没找到" << endl;
//	}
//	printset(s1);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////set和multiset的区别
//// set不可以插入重复数据，而multiset可以
//// set插入数据的同时会返回插入结果，表示插入是否成功
//// multiset不会检测数据，因此可以插入重复数据
// void printset(multiset<int>& s1)
//{
//	for (multiset<int>::const_iterator it = s1.begin(); it != s1.end(); it++)
//	{
//		cout << *it << endl;
//	}
// }
// void test01()
//{
//	set<int> s;
//	pair< set<int>::iterator, bool >ret = s.insert(10);
//	//s.insert函数返回值是pair对组,类内成员一个是迭代器一个是bool,如果遇到
//	//相同的元素，那么就会返回false,因此不可以有重复的元素
//	//而multiset的insert只会返回迭代器，因此不会出现false
//	if (ret.second)
//	{
//		cout << "第一次插入成功" << endl;
//	}
//	ret = s.insert(10);
//	if (ret.second)
//	{
//		cout << "第二次插入成功" << endl;
//	}
//	multiset<int>s1;
//	s1.insert(10);
//	s1.insert(10);
//	s1.insert(10);
//	s1.insert(40);
//	s1.insert(5);
//	printset(s1);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////pair队组
////默认构造和含参构造
// void test01()
//{
//	pair<string, int>p("Tom", 18);
//	cout << p.first << "\t" << p.second << endl;
//
//	pair<string, int>p2 = make_pair("Jerry", 18);
//
// }

////set容器排序
// class MyCompare
//{
// public:
//	bool operator()(int v1, int v2)const
//	{
//		return v1 > v2;
//	}
// };
// bool myCompare(int v1, int v2)
//{
//	return v1 > v2;
// }
//
// void test01()
//{
//	set<int>s1;
//	s1.insert(10);
//	s1.insert(20);
//	s1.insert(30);
//	s1.insert(40);
//	s1.insert(50);
//	s1.insert(60);
//	s1.insert(70);
//	for (set<int>::const_iterator it = s1.begin(); it != s1.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//	//template
//	//<
//	//	class T,
//	//	class Compare = std::less<T>,
//	//	class Allocator = std::allocator<T>
//	//>class set;
//	//它的第二个模板参数Compare，从设计之初就不是写死的固定逻辑，而是一个类型占位符，默认值是标准库自带的
//	//std::less<T>，也就是默认从小到大排序的仿函数。
//	set<int,MyCompare>s2;//set的模板有默认参数，默认从小到大排序
//	s2.insert(10);
//	s2.insert(20);
//	s2.insert(30);
//	s2.insert(40);
//	s2.insert(50);
//	s2.insert(60);
//	s2.insert(70);
//	for (set<int,MyCompare>::const_iterator it = s2.begin(); it != s2.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//	set<int, bool(*)(int, int)>s3(myCompare);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
// set类的排序底层实现也是仿函数,和上面写的代码相差不大
// 本质上只要编译器看到_M_comp(a,b)这行代码是合法可调用的，模板就能顺利编译通过
// bool(*)(int, int)是一个函数指针类型，编译器自动创建一个函数指针comp，仿函数是因为重载了()而形式上等于_M_comp(a,b)
// 而这个函数指针在编译器内部可以不解引用就代表一个函数，因而可以直接写成comp(a,b)两者都满足这个要求
////set容器排序，存放自定义类型
// class Person
//{
// public:
//	Person(string name, int age)
//	{
//		this->m_name = name;
//		this->m_age = age;
//	}
//	string m_name;
//	int m_age;
// };
// class ComparePerson
//{
// public:
//	bool operator()(const Person& p1, const Person& p2)const
//	{
//		return p1.m_age > p2.m_age;
//	}
// };
// void test01()
//{
//	set<Person,ComparePerson>s;//自定义类型都要指定排序规则
//	Person p1("liubei", 24);
//	Person p2("guanyu", 28);
//	Person p3("zahngfei", 25);
//	Person p4("zhaoyun", 21);
//	s.insert(p1);
//	s.insert(p2);
//	s.insert(p3);
//	s.insert(p4);
//	for (set<Person,ComparePerson>::const_iterator it = s.begin(); it != s.end(); it++)
//	{
//		cout << (*it).m_name << "\t" << (*it).m_age << endl;
//	}
//	cout << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// map容器和multimap容器
// map中所有元素都是pair
// pair第一个元素为key（键值）起索引作用，第二个元素为value（实值）
// 所有元素都会根据元素的键值自动排序

////map构造和赋值
////默认构造，拷贝构造
////赋值operator=
////大小size()
////判断是否为空empty()
////交换两个集合容器 swap(s)
// #include<map>
// void printmap(map<int,int>&m)
//{
//	for (map<int, int>::const_iterator it = m.begin(); it != m.end(); it++)
//	{
//		cout << (*it).first << "\t" << (*it).second << endl;
//	}
// }
// void test01()
//{
//	map<int, int>m;
//	m.insert(pair<int,int>(1,10));
//	m.insert(pair<int, int>(2, 20));
//	m.insert(pair<int, int>(3, 30));
//	m.insert(pair<int, int>(9, 0));//按照key值自动排序
//	m.insert(pair<int, int>(5, 50));
//	m.insert(pair<int, int>(6, 60));
//	m.insert(pair<int, int>(7, 70));
//	printmap(m);
//
//	map<int, int>m2(m);
//
//	map<int, int>m3 = m;
//	if (m3.empty())
//	{
//		cout << "map容器为空" << endl;
//	}
//	cout << m3.size() << endl;
//	m3.swap(m2);
//
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// map插入和删除
//// 向容器中插入元素，返回插入结果的迭代器（部分容器会返回pair<迭代器, bool>标识是否插入成功）
// iterator insert(const value_type& elem);
//
//// 清空容器内所有元素，将size置为0，不会释放底层容量
// void clear();
//
//// 删除迭代器pos指向的元素，返回下一个有效元素的迭代器
// iterator erase(iterator pos);
//
//// 删除左闭右开区间[beg, end)内的所有元素，返回end位置对应的新迭代器
// iterator erase(iterator beg, iterator end);
//
//// 针对关联容器（set/map）的重载版本：删除所有值/键等于key的元素，返回实际删除的元素个数
// size_type erase(const key_type& key);

#include <map>
// void printmap(map<int,int,MyCompare>&m)
//{
//	for (map<int, int>::const_iterator it = m.begin(); it != m.end(); it++)
//	{
//		cout << (*it).first << "\t" << (*it).second << endl;
//	}
// }
// void test01()
//{
//	map<int, int>m;
//	m.insert(pair<int,int>(1,10));
//	m.insert(make_pair(1,10));
//	m.insert(map<int,int>::value_type(3,30));
//	m[4] = 40;//按照key值自动排序
//	//中括号不建议插入，用途，可以利用key访问到value
//	cout << m[8] << endl;//如果不存在键值8，
//	//就会创建一个新的对组插入，并把实值设置为0
//	printmap(m);
//	m.erase(m.begin());
//	m.erase(3);//按照key删除
//	m.erase(m.begin(), m.end());
//	m.clear();
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////map查找和统计
////find(key) 查找key，返回对应的迭代器
////count(key)统计key出现的次数，在map容器中，其返回值只有0或1
// #include<map>
// void test01()
//{
//	map<int, int>m;
//	m.insert(pair<int,int>(1,10));
//	m.insert(pair<int, int>(2, 20));
//	m.insert(pair<int, int>(3, 30));
//	m.insert(pair<int, int>(4, 40));
//	m.insert(pair<int, int>(5, 50));
//	cout << (*m.find(3)).second << endl;
//	cout << m.count(6) << endl;
//
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// map容器的排序规则
// #include<map>
// class MyCompare
//{
// public:
//	bool operator()(int v1, int v2)const
//	{
//		return v1 > v2;
//	}
// };
// void printmap(map<int, int,MyCompare>& m)
//{
//	for (map<int, int>::const_iterator it = m.begin(); it != m.end(); it++)
//	{
//		cout << (*it).first << "\t" << (*it).second << endl;
//	}
// }
// void test01()
//{
//	map<int, int,MyCompare>m;
//	m.insert(pair<int,int>(1,10));
//	m.insert(pair<int, int>(7, 20));
//	m.insert(pair<int, int>(4, 30));
//	m.insert(pair<int, int>(9, 40));
//	m.insert(pair<int, int>(0, 50));
//	printmap(m);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////案例：员工分组
// #include<vector>
// #include<map>
// #define CEHUA 1
// #define MEISHU 2
// #define YANFA 3
// class Worker
//{
// public:
//	string m_name;
//	int m_salary;
// };
// void createworker(vector<Worker>&v)
//{
//	string nameseed= "ABCDEFGHIJK";
//	srand((unsigned int)time(NULL));
//	for (int i = 0; i < 10; i++)
//	{
//		Worker w;
//		w.m_name = "员工";
//		w.m_name += nameseed[i];
//		w.m_salary = rand() % 10000 + 10001;
//		v.push_back(w);
//	}
//	/*for (vector<Worker>::const_iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << (*it).m_name << "\t" << (*it).m_salary << endl;
//	}*/
//
// }
// void setgroup(vector<Worker>&v,multimap<int,Worker>&m)
//{
//	srand((unsigned int)time(NULL));
//	for (vector<Worker>::const_iterator it=v.begin();it!=v.end();it++)
//	{
//		int deptId = rand() % 3 + 1;
//		m.insert(make_pair(deptId, (*it)));
//	}
// }
//
// void showworker(multimap<int,Worker>&m)
//{
//	cout << "策划部门:" << endl;
//	int count = m.count(CEHUA);
//	multimap<int, Worker>::iterator pos = m.begin();
//	for (int i = 0; i < count; i++)
//	{
//		cout << (*pos).second.m_name << "\t" << (*pos).second.m_salary << endl;
//		pos++;
//	}
//	cout << "美术部门:" << endl;
//	count = m.count(MEISHU);
//	pos = m.find(MEISHU);
//	for (int i = 0; i < count; i++)
//	{
//		cout << (*pos).second.m_name << "\t" << (*pos).second.m_salary << endl;
//		pos++;
//	}
//	cout << "研发部门:" << endl;
//	count = m.count(YANFA);
//	pos = m.find(YANFA);
//	for (int i = 0; i < count; i++)
//	{
//		cout << (*pos).second.m_name << "\t" << (*pos).second.m_salary << endl;
//		pos++;
//	}
//
// }
// int main()
//{
//	vector<Worker>v;
//	createworker(v);
//
//	multimap<int, Worker>m;
//	setgroup(v,m);
//	showworker(m);
//	system("pause");
//	return 0;
// }

// 函数对象
// 重载函数调用符的类，其对象称为函数对象
// 函数对象使用重载的()时，称为仿函数
// 函数对象本质是一个类不是一个函数

////1.函数对象在使用时可以像普通函数一样调用，可以有参数可以有返回值
// class Myadd
//{
// public:
//	int operator()(int a, int b)
//	{
//		return a + b;
//	}
// };
// void test01()
//{
//	Myadd myadd;
//	cout << myadd(10, 20) << endl;
// }
////2.函数对象超出普通函数的概念，函数对象可以有自己的状态
//(通过类的内部成员记录成员属性)
// class Myprint
//{
// public:
//	Myprint(int count)
//	{
//		this->count = count;
//	}
//	void operator()(string test)
//	{
//		cout << test << endl;
//		this->count++;
//	}
//	int count;
//};
// void test02()
//{
//	Myprint myprint(0);
//	myprint("hello world");
//	myprint("hello world");
//	myprint("hello world");
//	cout << myprint.count << endl;
//}
// int main()
//{
//	test02();
//	system("pause");
//	return 0;
//}
//
////3. 函数对象可以作为参数传递
// class Myprint
//{
// public:
//	Myprint(int count)
//	{
//		this->count = count;
//	}
//	void operator()(string test)
//	{
//		cout << test << endl;
//		this->count++;
//	}
//	int count;
// };
// void doprint(Myprint& myprint,string test)
//{
//	myprint(test);
// }
// void test02()
//{
//	Myprint myprint(0);
//	doprint(myprint, "hello");
// }
// int main()
//{
//	test02();
//	system("pause");
//	return 0;
// }

// 谓词
// 谓词概念：谓词是一个能接收参数、返回bool类型的可调用对象
// 一个返回bool的函数/仿函数/Lambda，用来告诉STL算法「当前元素是否符合我的要求」。
// C++里谓词的本质：「可调用+返回bool」的实体
// 一元谓词
// class greaterfive
//{
// public:
//	bool operator()(int a)
//	{
//		return a > 5;
//	}
// };
// void test01()
//{
//	vector<int>v;
//	for (int i = 0; i < 10; i++)
//	{
//		v.push_back(i);
//	}
//	//find_if的第三个参数是自定义一元谓词（返回bool类型、接收一个容器元素作为参数的可调用对象）
//	//greaterfive()相当于创建了一个临时匿名对象
//	vector<int>::iterator it=find_if(v.begin(), v.end(), greaterfive());
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
////二元谓词
// class MyCompare
//{
// public:
//	bool operator()(int a, int b)
//	{
//		return a > b;
//	}
// };
// void test01()
//{
//	vector<int>v;
//	v.push_back(10);
//	v.push_back(70);
//	v.push_back(40);
//	v.push_back(20);
//	v.push_back(90);
//	v.push_back(0);
//	sort(v.begin(), v.end());
//	sort(v.begin(), v.end(),MyCompare());
//	for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << (*it) << endl;
//	}
// }
// int main()
//{
//
//	test01();
//	system("pause");
//	return 0;
// }

////算数仿函数
////template<class T> T plus<T>      //加法仿函数
////template<class T> T minus<T>     //减法仿函数
////template<class T> T multiplies<T>//乘法仿函数
////template<class T> T divides<T>  //除法仿函数
////template<class T> T modulus<T>   //取模仿函数
////template<class T> T negate<T>    //取反仿函数
//
// #include<functional>
// void test01()
//{
//	//取反
//	negate<int>n;
//	n(50);
//	//plus加法
//	plus<int>m;
//	m(100, 300);
//}
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
//}
////关系仿函数
////template<class T> bool equal_to<T>        //等于
////template<class T> bool not_equal_to<T>    //不等于
////template<class T> bool greater<T>         //大于
////template<class T> bool greater_equal<T>   //大于等于
////template<class T> bool less<T>            //小于
////template<class T> bool less_equal<T>      //小于等于
// void test()
//{
//	vector<int>v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//	v.push_back(60);
//	v.push_back(70);
//	sort(v.begin(), v.end(),greater<int>());
//	for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << (*it) << endl;
//	}
// }
// int main()
//{
//	test();
//	system("pause");
//	return 0;
// }
////逻辑仿函数
////template<class T> bool logical_and<T>    //逻辑与
////template<class T> bool logical_or<T>     //逻辑或
////template<class T> bool logical_not<T>    //逻辑非
// #include<functional>
// void test01()
//{
//	vector<bool>v;
//	v.push_back(true);
//	v.push_back(false);
//	v.push_back(true);
//	v.push_back(false);
//	for(vector<bool>::const_iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << (*it) << endl;
//	}
//	vector<bool>v2;
//	v2.resize(v.size());
//	transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());
//	for (vector<bool>::const_iterator it = v2.begin(); it != v2.end(); it++)
//	{
//		cout << (*it) << endl;
//	}
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// STL常用算法
// • 算法主要是由头文件 <algorithm> <functional> <numeric> 组成。
// • <algorithm> 是所有STL头文件中最大的一个，范围涉及到比较、交换、查找、遍历操作、复制、修改等等
// • <numeric> 体积很小，只包括几个在序列上面进行简单数学运算的模板函数
// • <functional> 定义了一些模板类, 用以声明函数对象。
//
// 5.1 常用遍历算法
// for_each    //遍历容器
// transform  //搬运容器到另一个容器中
// void myprint(int a)
//{
//	cout << a << endl;
// }
// int Transform(int a)
//{
//	return a;
// }
// void test01()
//{
//	vector<int>v;
//	for (int i = 0; i < 10; i++)
//	{
//		v.push_back(i);
//	}
//	for_each(v.begin(), v.end(), myprint);//!!!!!!
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }
// class Transform
//{
// public:
//	int operator()(int v)
//	{
//		return v;
//	}
// };
// void test01()
//{
//	vector<int>v;
//	for (int i = 0; i < 10; i++)
//	{
//		v.push_back(i);
//	}
//	vector<int>v2;
//	v2.resize(v.size());//!!!!
//	transform(v.begin(), v.end(), v2.begin(),Transform);
//	//在搬运过程中第四个参数是个函数，可以对数据进行一些逻辑运算
//	//，因此他的返回值和vector容器存储的数据是同一种类型
//	for_each(v2.begin(), v2.end(), myprint);
////第三个参数相当于给了一个打印的函数接口，给一个符合该类型数据的打印函数
//}
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
//}

// 5.2常用的查找算法
// find         //查找元素
// find_if      //按条件查找元素
// adjacent_find //查找相邻重复元素
// binary_search //二分查找法
// count        //统计元素个数
// count_if     //按条件统计元素个数
// void test01()
//{
//	vector<int>v;
//	for (int i = 0; i < 10; i++)
//	{
//		v.push_back(i);
//	}
//	vector<int>::iterator it = find(v.begin(), v.end(), 50);
//	if (it == v.end())
//	{
//		cout << "没找到" << endl;
//	}
//	else
//	{
//		cout << "找到了" << endl;
//	}
// }
// class Person
//{
// public:
//	Person(string name, int age)
//	{
//		this->m_age = age;
//		this->m_name = name;
//	}
//	/*bool operator==(const Person p1)
//	{
//		if (this->m_age == p1.m_age && this->m_name == p1.m_name)
//			return true;
//		return false;
//	}*/
//	string m_name;
//	int m_age;
// };
// void test02()
//{
//	vector<Person>v;
//	Person p1("张三", 18);
//	Person p2("张寺", 20);
//	Person p3("张五", 24);
//	Person p4("张六", 17);
//	Person p5("张其", 28);
//	Person p6("张吧", 42);
//	Person p7("张久", 26);
//	v.push_back(p1);
//	v.push_back(p2);
//	v.push_back(p3);
//	v.push_back(p4);
//	v.push_back(p5);
//	v.push_back(p6);
//	v.push_back(p7);
//	vector<Person>::iterator it=find(v.begin(),v.end(),p3);
//
// }
// int main()
//{
//	test02();
//	system("pause");
//	return 0;
// }
// find是找容器中是否有这样一个数据
// 所以底层的本质是一个循环，然后遍历每一个数据，
// 然后比较第三个参数是否和传入的数据是相同的
// 但由于底层的比较==只有系统自带的数据类型，所以person类型的数据传进去之后
// 在遇到==会发生未定义行为，因此需要在Person内部重载运算符==
// class Greater5
//{
// public:
//	bool operator()(int a)
//	{
//		return a > 5;
//	}
// };
//
// void test01()
//{
//	vector<int>v;
//	v.push_back(0);
//	v.push_back(2);
//	v.push_back(4);
//	v.push_back(5);
//	v.push_back(7);
//	find_if(v.begin(), v.end(), Greater5());
// }
// class Person
//{
// public:
//	Person(string name, int age)
//	{
//		this->m_age = age;
//		this->m_name = name;
//	}
//	string m_name;
//	int m_age;
// };
// class MyCompare
//{
// public:
//	bool operator()(Person& p1)
//	{
//		if ( p1.m_age>40)
//		{
//			return true;
//		}
//		return false;
//	}
// };
// void test02()
//{
//	vector<Person>v;
//	Person p1("张三", 18);
//	Person p2("张寺", 20);
//	Person p3("张五", 24);
//	Person p4("张六", 17);
//	Person p5("张其", 28);
//	Person p6("张吧", 42);
//	Person p7("张久", 26);
//	v.push_back(p1);
//	v.push_back(p2);
//	v.push_back(p3);
//	v.push_back(p4);
//	v.push_back(p5);
//	v.push_back(p6);
//	v.push_back(p7);
//	find_if(v.begin(), v.end(),MyCompare());
//	//！！！！！！！！！
//	//本质上底层只是需要一个判别的函数，
//	//底层只是把一个数据传入了_Pred这样一个函数来判别是否符合条件
//	//所以只要传入一个函数就可以，仿函数是比函数功能性更强所以仿函数用的比较多
// }
// int main()
//{
//	test02();
//	system("pause");
//	return 0;
// }
//

////adjacent_find查找相邻重复元素
////返回相邻元素的第一个位置的迭代器
// void test02()
//{
//	vector<int>v;
//	v.push_back(0);
//	v.push_back(1);
//	v.push_back(2);
//	v.push_back(1);
//	v.push_back(2);
//	v.push_back(2);
//	vector<int>::iterator it = adjacent_find(v.begin(), v.end());
//	if (it == v.end())
//	{
//		cout << "没找到相邻重复元素" << endl;
//	}
// }
// int main()
//{
//	test02();
//	system("pause");
//	return 0;
// }

////binary_search
////函数原型：
////bool binary_search(iterator beg, Iterator end, value);
//// 查找指定的元素，查到 返回true 否则false
//// 注意: 在无序序列中不可用
//// beg 开始迭代器
//// end 结束迭代器
//// value 查找的元素
// void test01()
//{
//	vector<int>v;
//	v.push_back(0);
//	v.push_back(236);
//	v.push_back(79);
//	v.push_back(73);
//	v.push_back(78);
//	v.push_back(62);
//	std::sort(v.begin(), v.end(),std::less<int>());
//	//std是"standard"的缩写，C++标准里规定所有标准库的组件全部都封装在这个命名空间里。
//	//"sort不明确"的问题，就是因为作用域里同时出现了多个叫sort
//	//的符号，加上std::相当于给编译器下了明确指令：我要找的是
//	//<algorithm>头文件里定义的、C++标准库提供的这个经过高度优化的排序算法
//	bool ret = binary_search(v.begin(), v.end(),78);
//	if (!ret)
//	{
//		cout << "没找到" << endl;
//	}
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////5.2.5 count
////统计元素个数
////count(iterator beg, iterator end, value);
//// 统计元素出现次数
//// beg 开始迭代器
//// end 结束迭代器
//// value 统计的元素
// class Person
//{
// public:
//	bool operator==(const Person& p1)const
//	{
//		if (this->m_age == p1.m_age)
//			return true;
//		return false;
//	}
//	Person(string name, int age)
//	{
//		this->m_age = age;
//		this->m_name = name;
//	}
//	int m_age;
//	string m_name;
// };
// void test01()
//{
//	vector<Person>v;
//	Person p1("liubei", 12);
//	Person p2("liqing", 17);
//	Person p3("liubei", 20);
//	Person p4("guanyu", 20);
//	v.push_back(p1);
//	v.push_back(p2);
//	v.push_back(p3);
//	v.push_back(p4);
//	cout << count(v.begin(), v.end(), p3) << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////count_if按条件统计
// class Person
//{
// public:
//	bool operator==(const Person& p1)const
//	{
//		if (this->m_age == p1.m_age)
//			return true;
//		return false;
//	}
//	Person(string name, int age)
//	{
//		this->m_age = age;
//		this->m_name = name;
//	}
//	int m_age;
//	string m_name;
// };
// class MyCompare
//{
// public:
//	bool operator()(const Person& p1)
//	{
//		if (p1.m_age > 19)
//			return true;
//		return false;
//	}
// };
// void test01()
//{
//	vector<Person>v;
//	Person p1("liubei", 12);
//	Person p2("liqing", 17);
//	Person p3("liubei", 20);
//	Person p4("guanyu", 20);
//	v.push_back(p1);
//	v.push_back(p2);
//	v.push_back(p3);
//	v.push_back(p4);
//	cout << count_if(v.begin(), v.end(),MyCompare() ) << endl;
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

////常用排序算法
//
////算法简介 :
////• sort          //对容器内元素进行排序
////• random_shuffle //洗牌 指定范围内的元素随机调整次序
////• merge         //容器元素合并，并存储到另一容器中
////• reverse       //反转指定范围的元素
// class Person
//{
// public:
//	bool operator==(const Person& p1)const
//	{
//		if (this->m_age == p1.m_age)
//			return true;
//		return false;
//	}
//	Person(string name, int age)
//	{
//		this->m_age = age;
//		this->m_name = name;
//	}
//	int m_age;
//	string m_name;
// };
// bool MyCompare(Person& p1, Person& p2)
//{
//	if (p1.m_age > p2.m_age)
//	{
//		return true;
//	}
//	return false;
// }
// void test01()
//{
//	vector<Person>v;
//	Person p1("liubei", 12);
//	Person p2("liqing", 17);
//	Person p3("liubei", 20);
//	Person p4("guanyu", 20);
//	v.push_back(p1);
//	v.push_back(p2);
//	v.push_back(p3);
//	v.push_back(p4);
//	sort(v.begin(), v.end(), MyCompare);//底层实现是一个二元谓词
//	srand((unsigned int)time(NULL));
//	random_shuffle(v.begin(), v.end());
//	vector<Person>v2(v);
//	vector<int>v3;//过程类似归并排序，要求v1，v2是有序的，得到的v3也是有序的
//	v3.resize(v.size() + v2.size());
//	merge(v.begin(), v.end(),v2.begin(),v2.end(),v3.begin());
//	reverse(v3.begin(), v3.end());
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 常用拷贝和替换算法
// 算法简介 :
// copy         //容器内指定范围的元素拷贝到另一容器中
// replace      //将容器内指定范围的旧元素修改为新元素
// replace_if  //容器内指定范围满足条件的元素替换为新元素
// swap         //互换两个容器的元素
// bool MyCompare(int& a)
//{
//	if (a < 20)
//	{
//		return true;
//	}
//	return false;
//}
// void Myprint(int& a)
//{
//	cout << a << endl;
//}
// void test01()
//{
//	vector<int >v1;
//	v1.push_back(0);
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//	v1.push_back(4);
//	v1.push_back(5);
//	vector<int>v2;
//	v2.resize(v1.size());
//	copy(v1.begin(), v1.end(), v2.begin());
//	replace(v1.begin(),v1.end(),20, 2000);//oldval->newval,替换所有
//	replace_if(v1.begin(), v1.end(), MyCompare, 2000);//什么样的条件替换
//	for_each(v1.begin(), v1.end(), Myprint);
//	vector<int>v3;
//	v3.resize(v1.size());
//	swap(v1, v3);
//}
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
//}

////算数生成算法
////accumulate
////函数原型 :
////• accumulate(iterator beg, iterator end, value);
////// 计算容器元素累计总和
////// beg 开始迭代器
////// end 结束迭代器
////// value 起始值
////fill
////把容器中的指定范围数据修改为参数3
// #include<numeric>
// void test01()
//{
//	vector<int>v;
//	v.push_back(1);
//	v.push_back(1);
//	v.push_back(1);
//	v.push_back(1);
//	v.push_back(1);
//	v.push_back(1);
//	v.push_back(1);
//	v.push_back(1);
//	//参数三是起始的累加值
//	int total=accumulate(v.begin(), v.end(), 0);
//	cout << total << endl;
//	vector<int>v2;
//	v.resize(20);
//	fill(v.begin(), v.end(), 100);
// }
// int main()
//{
//	test01();
//	system("pause");
//	return 0;
// }

// 常用集合算法
// 算法简介:
//  //两个集合必须都是有序序列
// • set_intersection    //求两个容器的交集
// • set_union           //求两个容器的并集
// • set_difference      //求两个容器的差集
void myprint(int a)
{
    cout << a << " ";
}
void test01()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    // 参数三是起始的累加值
    vector<int> v2;
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(6);
    v2.push_back(7);
    v2.push_back(8);
    v2.push_back(9);
    vector<int> v3;
    v3.resize(v.size() + v2.size());
    vector<int>::iterator end = set_intersection(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin()); // 返回值是交集结束的位置
    for_each(v3.begin(), end, myprint);
    cout << endl;

    vector<int> v4;
    v4.resize(v.size() + v2.size());
    end = set_union(v.begin(), v.end(), v2.begin(), v2.end(), v4.begin()); // 返回值是交集结束的位置
    for_each(v4.begin(), end, myprint);
    cout << endl;

    vector<int> v5;
    v5.resize(v.size() + v2.size());
    end = set_difference(v.begin(), v.end(), v2.begin(), v2.end(), v5.begin()); // 返回值是交集结束的位置
    for_each(v5.begin(), end, myprint);
    cout << endl; // 差集，前者有的但后者没有的
}
int main()
{
    test01();
    system("pause");
    return 0;
}