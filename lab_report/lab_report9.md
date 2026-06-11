# 解题报告

姓名：白家辉

班级：计算机大类2508

学号：8208250831

日期：2026.5.28

# 总览

本次解题报告中，共完成 4 道题目。

| 题目名称 | 难度 | 知识点 |
| -------- | ---- | ------ |
|P1152 欢乐的跳|入门|数组、差值统计、布尔标记|
|P1177 排序|普及|排序算法、分治|
|P1104 生日|普及|结构体排序、自定义比较|
|P2141 珠心算测验|普及|枚举、查找、集合|

# （一）欢乐的跳

## 题目信息

题目链接：[https://www.luogu.com.cn/problem/P1152](https://www.luogu.com.cn/problem/P1152)

知识点：数组、差值统计、布尔标记

## 题目简述

> 给定一个长度为 $n$ 的整数序列。如果所有相邻元素差的绝对值，恰好包含了从 `1` 到 `n-1` 的所有整数，则称这个序列是“欢乐的跳”。
>
> 现在要求判断给定序列是否满足这一性质。
>
> 对于全部数据，$1 \le n \le 1000$。
>
> 1.00s，128MB。

## 题目分析

### 1. 读题
题目不是要求对原序列排序，也不是看元素本身是否连续，而是只关心“相邻元素之差的绝对值”能否刚好覆盖 `1..n-1`。

### 2. 性质观察
一个长度为 `n` 的序列，一共有 `n-1` 个相邻差值。如果这些差值既都落在 `1..n-1` 范围内，又没有重复，那么它们就必然正好覆盖整个区间。

因此本题只需要统计每个差值是否出现过即可。

### 3. 程序设计思路
1. 顺序读入数组；
2. 对每一对相邻元素，计算差的绝对值 `d`；
3. 如果 `d` 不在 `1..n-1` 范围内，则一定不满足；
4. 否则用布尔数组标记这个差值已经出现；
5. 最后检查 `1..n-1` 是否全部被标记；
6. 若全部出现，则输出 `Jolly`，否则输出 `Not jolly`。

### 4. 数据结构与算法选择
本题用一个布尔数组记录差值出现情况即可。题目规模很小，直接模拟最清楚。

### 5. 时空复杂度分析
- 时间复杂度：$O(n)$，只需线性扫描一遍序列。
- 空间复杂度：$O(n)$，用于记录差值是否出现。

## 代码实现

![提交记录截图](result36.png)

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int n = 0;
	int arr[1001] = { 0 };
	memset(arr, 0, sizeof(arr));
	scanf("%d", &n);
	int temp = n-1;
	int pre = 0;
	int aft = 0;
    scanf(" %d",&pre);
	while (temp--)
	{
		scanf(" %d", &aft);
		int num = aft - pre;
        pre=aft;
		if (num < 0)
		{
			num = -num;
		}
        if(num>=n||num<0)
        {
            continue;
        }
		if (arr[num] == 0)
		{
			arr[num] = 1;
		}
	}
	int flat = 1;
	for (int i = 1; i < n; i++)
	{
		if (arr[i] != 1)
		{
			flat = 0;
		}
	}
	if (flat == 0)
	{
		printf("Not jolly\n");
	}
	else
	{
		printf("Jolly\n");
	}
}
```

---

# （二）排序

## 题目信息

题目链接：[https://www.luogu.com.cn/problem/P1177](https://www.luogu.com.cn/problem/P1177)

知识点：排序算法、分治

## 题目简述

> 输入 `N` 个整数，要求按从小到大的顺序输出。
>
> 对于全部数据，$N \le 10^5$，单个数值可达到 $10^9$。
>
> 1.00s，256MB。

## 题目分析

### 1. 读题
这是一道标准排序模板题，核心在于使用一个足够高效的排序算法处理 `10^5` 级别的数据。

### 2. 性质观察
由于数值范围很大，并不适合直接使用桶排序；但数据规模只有 `10^5`，使用时间复杂度为 $O(n \log n)$ 的比较排序完全可以通过。

### 3. 程序设计思路
1. 将所有整数读入数组；
2. 采用一种稳定可靠的高效排序算法，如归并排序、快速排序或语言自带的高效排序函数；
3. 排序完成后依次输出数组中的元素。

### 4. 数据结构与算法选择
本题只需要数组存储全部数据。算法上选择 $O(n \log n)$ 的排序即可，这也是处理通用大规模排序问题的标准方案。

### 5. 时空复杂度分析
- 时间复杂度：$O(n \log n)$。
- 空间复杂度：取决于具体排序实现。归并排序通常为 $O(n)$，原地快速排序平均可做到较低额外空间。

在题目给定范围下，这类复杂度完全足够。

## 代码实现

![提交记录截图](result33.png)

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cmp(const void* e1, const void* e2)
{
	int* p1 = (int*)e1;
	int* p2 = (int*)e2;
	return (*p1) - (*p2);
}
int main()
{
	int n = 0;
	scanf("%d", &n);
	int* arr = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		scanf(" %d", &arr[i]);
	}
	qsort(arr, n, sizeof(int), cmp);
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	free(arr);
	return 0;
}
```

---

# （三）生日

## 题目信息

题目链接：[https://www.luogu.com.cn/problem/P1104](https://www.luogu.com.cn/problem/P1104)

知识点：结构体排序、自定义比较

## 题目简述

> 输入若干同学的姓名和生日信息，要求按年龄从大到小输出姓名。也就是说，生日越早的人越先输出。
>
> 如果两位同学生日完全相同，则输入靠后的同学先输出。
>
> 对于全部数据，人数不超过 `100`。
>
> 1.00s，128MB。

## 题目分析

### 1. 读题
题目本质上是一个多关键字排序问题。主关键字是生日早晚，副关键字则是输入顺序的逆序。

### 2. 性质观察
年龄从大到小，等价于“出生日期从早到晚”。因此比较规则应当依次比较：
1. 年份；
2. 月份；
3. 日期；
4. 若前三项都相同，则比较输入顺序，后输入的人排在前面。

### 3. 程序设计思路
1. 用结构体保存每位同学的姓名、出生年月日和输入次序；
2. 编写自定义比较函数：
3. 出生更早者优先；
4. 若生日相同，则输入序号更大的优先；
5. 排序后按顺序输出姓名即可。

### 4. 数据结构与算法选择
本题适合使用结构体数组加自定义排序。这样既能保留原始信息，也方便统一处理多个比较关键字。

### 5. 时空复杂度分析
- 时间复杂度：$O(n \log n)$。
- 空间复杂度：$O(n)$，主要用于存储所有同学信息。

对于 `100` 级别的数据，任何常规排序实现都很轻松。

## 代码实现

![提交记录截图](result34.png)

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct stu
{
	char name[21];
	int year;
	int month;
	int date;
}stu;
int cmp(const void* e1, const void* e2)
{
	stu* p1 = (stu*)e1;
	stu* p2 = (stu*)e2;
	if (p1->year != p2->year)
	{
		return (p1->year) - (p2->year);
	}
	if (p1->month != p2->month)
	{
		return (p1->month) - (p2->month);
	}
	if (p1->date != p2->date)
	{
		return (p1->date) - (p2->date);
	}
    return 1;
}
int main()
{
	stu student[101];
	int n = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", student[i].name);
		scanf(" %d", &student[i].year);
		scanf(" %d", &student[i].month);
		scanf(" %d", &student[i].date);
	}
	qsort(student, n, sizeof(stu), cmp);
	for (int i = 0; i < n; i++)
	{
		printf("%s\n", student[i].name);
	}
}

```

---

# （四）珠心算测验

## 题目信息

题目链接：[https://www.luogu.com.cn/problem/P2141](https://www.luogu.com.cn/problem/P2141)

知识点：枚举、查找、集合

## 题目简述

> 给出一个由互不相同正整数组成的集合，要求统计其中有多少个数，恰好等于集合中另外两个不同数之和。
>
> 对于全部数据，$3 \le n \le 100$，集合中的数不超过 `10000`。
>
> 1.00s，128MB。

## 题目分析

### 1. 读题
题目要求判断一个数是否能表示成集合中另外两个不同数的和。因为集合中元素互不相同，所以只要找到一组满足条件的加数即可把该数计入答案。

### 2. 性质观察
`n` 最多只有 `100`，规模很小，因此完全可以直接枚举两个加数，再判断它们的和是否在集合中。

为了避免重复计数，同一个“目标数”只要被找到一次，就不应重复加入答案。

### 3. 程序设计思路
1. 读入所有数字，并保存到数组中；
2. 使用布尔数组或集合结构，支持快速判断某个数是否存在；
3. 枚举所有不同的两个下标 `i,j`；
4. 计算 `a[i]+a[j]`；
5. 若这个和也在集合中，则把对应目标数标记为“可表示”；
6. 最后统计有多少个数被标记即可。

### 4. 数据结构与算法选择
本题可以采用“二重枚举 + 快速查找”。数据范围很小，不需要更复杂的优化，关键是把“是否存在”这一步做成高效查询。

### 5. 时空复杂度分析
- 时间复杂度：$O(n^2)$，枚举所有数对。
- 空间复杂度：$O(n)$ 或 $O(V)$，取决于使用集合还是值域标记数组。

在 `n<=100` 的条件下，这是最直接也最稳妥的做法。

## 代码实现

![提交记录截图](result35.png)

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int n = 0;
	int sum = 0;
	scanf("%d", &n);
	int* arr1 = (int*)calloc(20002 , sizeof(int));
	int* arr2 = (int*)calloc(n , sizeof(int));
	int pos = 0;
	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		scanf(" %d", &temp);
		arr1[temp] = 1;
		arr2[pos++] = temp;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int num = arr2[i] + arr2[j];
			if (arr1[num] == 1)
			{
				sum++;
                arr1[num]=0;
			}
		}
	}
	printf("%d\n", sum);
    free(arr1);
    free(arr2);
	return 0;
}
```
