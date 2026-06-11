# 解题报告

姓名：白家辉

班级：计算机大类2508

学号：8208250831

日期：2026.6.11

# 总览

本次解题报告中，共完成 4 道题目。

| 题目名称 | 难度 | 知识点 |
| -------- | ---- | ------ |
|P1598 垂直柱状图|普及-|计数统计、格式输出|
|P2239 螺旋矩阵|普及/提高-|分层模拟、数学规律|
|P4715 淘汰赛|普及-|模拟、递归思维|
|P4913 二叉树深度|普及-|二叉树、迭代遍历、深度统计|

# （一）垂直柱状图

## 题目信息

题目链接：[https://www.luogu.com.cn/problem/P1598](https://www.luogu.com.cn/problem/P1598)

知识点：计数统计、格式输出

## 题目简述

> 输入四行只包含大写字母的文本，每行长度不超过 $100$。需要统计 `A` 到 `Z` 这 $26$ 个字母分别出现了多少次，并按照样例要求输出一幅竖直方向的柱状图。
>
> 输出时不仅要保证每一层的星号位置正确，还要特别注意行尾不能多输出空格。
>
> 1.00s，128MB。

## 题目分析

### 1. 读题
这题的核心不是复杂算法，而是“先统计，再按固定格式打印”。真正容易出错的部分主要在输出细节，尤其是每行末尾多余空格的控制。

### 2. 性质观察
柱状图的高度只取决于出现次数最多的那个字母。因此可以先统计全部字母频次，再从最大高度往下逐层判断：当前这一层某个字母位置是否应该打印 `*`。

### 3. 程序设计思路
处理过程分成两步：
1. 先扫描四行字符串，统计 `A` 到 `Z` 每个字母的出现次数；
2. 找出最大出现次数 `maxn`；
3. 从高度 `maxn` 这一层开始，一层一层向下输出；
4. 对于每层的每个字母，若它的出现次数不少于当前层高，就输出 `*`，否则输出空格；
5. 最后一行再输出字母 `A` 到 `Z` 作为横坐标。

### 4. 数据结构与算法选择
本题只需要一个长度为 `26` 的计数数组。算法上采用“计数 + 按层打印”的方式即可，思路直接，且很容易和柱状图结构对应起来。

### 5. 时空复杂度分析
- 时间复杂度：$O(26 \times H + L)$，其中 $H$ 为柱状图最大高度，$L$ 为输入总字符数。由于规模很小，可视作常数级。
- 空间复杂度：$O(26)$，仅需要一个字母计数数组。

## 代码实现

```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int arr[26] = { 0 };
	int n = 4;
	while (n--)
	{
		char s[100] = {0};
		fgets(s, sizeof(s), stdin);
		int sz = strlen(s);
		for (int i = 0; i < sz; i++)
		{
			int temp = s[i] - 'A';
			if (temp >= 0 && temp < 26)
			{
				arr[temp]++;
			}
		}
	}
	int max = 0;
	for (int i = 0; i < 26; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	char** print = (char**)malloc((max+1) * sizeof(char*));
	for (int i = 0; i <= max; i++)
	{
		print[i] = (char*)malloc(26 * sizeof(char));
	}
	for (int i = 0; i < 26; i++)
	{
		print[max][i] = i + 'A';
	}

	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (arr[j] >= max - i)
			{
				print[i][j] = '*';
			}
			else
			{
				print[i][j] = ' ';
			}
		}
	}
	for (int i = 0; i <= max; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			printf("%c ", print[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i <= max; i++)
	{
		free(print[i]);
	}
	free(print);

}
```

---

# （二）螺旋矩阵

## 题目信息

题目链接：[https://www.luogu.com.cn/problem/P2239](https://www.luogu.com.cn/problem/P2239)

知识点：分层模拟、数学规律

## 题目简述

> 按顺时针螺旋方式在一个 $n \times n$ 矩阵中依次填入 $1,2,3,\dots,n^2$。给定矩阵大小 $n$ 以及位置 $(i,j)$，要求求出该位置上的数字。
>
> 对于全部数据，$n$ 最大可达到 $30000$，因此不能真的把整个矩阵完整构造出来。
>
> 1.00s，128MB。

## 题目分析

### 1. 读题
如果直接模拟整个螺旋填数过程，虽然逻辑不难，但矩阵最大会达到 $30000 \times 30000$，无论时间还是空间都远远超出可承受范围。因此必须只根据位置推答案。

### 2. 性质观察
螺旋矩阵可以看成一层一层的“方环”：
1. 最外层是一圈；
2. 去掉最外层后，里面又是一个更小的螺旋矩阵；
3. 某个位置属于第几层，只取决于它到四条边的最小距离。

一旦确定了它所在的层，就能算出这一层左上角起始值，再根据它位于上边、右边、下边还是左边，推得最终答案。

### 3. 程序设计思路
先计算目标位置所在的层数 `k`：
1. `k` 等于该位置到四条边距离中的最小值再加一；
2. 设这一层边长为 `len`；
3. 先算出这一层左上角的起始编号；
4. 再判断 `(i,j)` 位于当前方环的哪一条边：
5. 如果在上边，就从起点向右偏移；
6. 如果在右边，就先走完整条上边再向下偏移；
7. 如果在下边或左边，也用类似方式累计偏移量。

这样无需建矩阵，就能直接得到指定位置的值。

### 4. 数据结构与算法选择
本题本质是数学推导题，不需要额外数据结构。相比直接模拟整张矩阵，按层分析并直接计算位置值，才是满足大规模数据要求的办法。

### 5. 时空复杂度分析
- 时间复杂度：$O(1)$，只需要常数次计算和分类讨论。
- 空间复杂度：$O(1)$，不需要存储矩阵。

这也是本题能通过 $n=30000$ 数据范围的关键。

## 代码实现

```c
#include<stdio.h>

int main()
{
    int N, temp1, temp2;
    scanf("%d %d", &N, &temp1);
    scanf("%d", &temp2);
    int target_x = temp1 - 1;
    int target_y = temp2 - 1;

    int left = 0, right = N - 1;
    int up = 0, down = N - 1;
    int num = 1;

    while (left <= right) 
    {
        for (int y = left; y <= right; y++) 
        {
            if (up == target_x && y == target_y) 
            {
                printf("%d\n", num);
                return 0;
            }
            num++;
        }
        up++;
        for (int x = up; x <= down; x++) 
        {
            if (x == target_x && right == target_y) 
            {
                printf("%d\n", num);
                return 0;
            }
            num++;
        }
        right--; 

       
        for (int y = right; y >= left; y--) {
            if (down == target_x && y == target_y) {
                printf("%d\n", num);
                return 0;
            }
            num++;
        }
        down--;

        
        for (int x = down; x >= up; x--) {
            if (x == target_x && left == target_y) {
                printf("%d\n", num);
                return 0;
            }
            num++;
        }
        left++;
    }

    return 0;
}

```

---

# （三）淘汰赛

## 题目信息

题目链接：[https://www.luogu.com.cn/problem/P4715](https://www.luogu.com.cn/problem/P4715)

知识点：模拟、递归思维

## 题目简述

> 有 $2^n$ 个国家参加淘汰赛，每个国家有一个互不相同的能力值。比赛按固定对阵顺序进行，能力值更高的国家一定获胜。
>
> 题目要求输出亚军的编号，也就是最后一场决赛中失败的那个国家编号。
>
> 对于全部数据，$n \leq 7$。
>
> 1.00s，128MB。

## 题目分析

### 1. 读题
因为强者一定能赢弱者，所以整个淘汰赛结果是完全确定的。题目并不是要找冠军，而是要找决赛输掉的那个国家，也就是“另一个进入决赛的人”。

### 2. 性质观察
整张赛程表可以视为左右两半分别决出一个冠军，最后这两个半区冠军再打一场决赛。因此亚军一定是左右两个半区冠军中能力值较小的那个。

这意味着我们并不需要记录每一场比赛的全部细节，只要分别找出左右半区的最强者即可。

### 3. 程序设计思路
把所有国家按题目给定顺序分成左右两个半区：
1. 在左半区找出能力值最大的国家编号；
2. 在右半区找出能力值最大的国家编号；
3. 这两个人就是最终进入决赛的两个选手；
4. 比较他们的能力值，较小者就是亚军，输出其编号。

从模拟角度看，也可以逐轮淘汰；但本题规模很小，直接抓住“亚军一定是两个半区冠军中的弱者”这个性质会更简洁。

### 4. 数据结构与算法选择
本题只需要数组存储每个国家的能力值。算法上可以用简单扫描分别求左右半区最大值，也可以用递归模拟比赛过程，本质都很直接。

### 5. 时空复杂度分析
- 时间复杂度：$O(2^n)$，只需要扫描一遍全部选手。
- 空间复杂度：$O(2^n)$ 或 $O(1)$ 额外空间，取决于具体实现方式。

由于 $n \leq 7$，总人数最多只有 $128$，任何线性做法都足够快。

## 代码实现

```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int n = 0;
	int num = 1;
	int pos = 0;
	int pos2 = 0;
	scanf("%d", &n);
	if (n == 1)
	{
		int temp1 = 0;
		int temp2 = 0;
		scanf("%d %d", &temp1, &temp2);
		printf("%d\n", temp1 < temp2 ? 1 : 2);
		return 0;
	}
	for (int i = 0; i < n; i++)
	{
		num *= 2;
	}
	int* arr = (int*)malloc((num + 1) * sizeof(int));
	int* arr2 = (int*)malloc((num + 1) * sizeof(int));
	for (int i = 0; i < num; i += 2)
	{
		int temp1;
		int temp2;
		scanf("%d %d", &temp1, &temp2);
		arr2[pos2++] = temp1;
		arr2[pos2++] = temp2;
		if (temp1 > temp2)
			arr[pos++] = temp1;
		else
			arr[pos++] = temp2;
	}
	for (int i = 0; i < n - 2; i++)
	{
		int countrynum = pos;
		pos = 0;
		for (int j = 0; j < countrynum; j += 2)
		{
			int temp1 = arr[j];
			int temp2 = arr[j + 1];
			if (temp1 > temp2)
				arr[pos++] = temp1;
			else
				arr[pos++] = temp2;
		}
	}
	int temp1 = arr[0];
	int temp2 = arr[1];
	int result = temp1 < temp2 ? temp1 : temp2;
	for (int i = 0; i < num; i++)
	{
		if (arr2[i] == result)
		{
			printf("%d\n", i + 1);
			break;
		}
	}
	free(arr);
	free(arr2);
	return 0;
}
```

---

# （四）二叉树深度

## 题目信息

题目链接：[https://www.luogu.com.cn/problem/P4913](https://www.luogu.com.cn/problem/P4913)

知识点：二叉树、迭代遍历、深度统计

## 题目简述

> 给出一棵共有 $n$ 个结点的二叉树，根结点编号固定为 `1`。对于每个结点，输入其左儿子和右儿子的编号；若某个结点是叶子，则输入 `0 0`。
>
> 需要在整棵树建立完成后，求出这棵二叉树的深度，也就是从根到叶子最多经过的层数。
>
> 对于全部数据，$n \leq 10^6$。
>
> 1.00s，128MB。

## 题目分析

### 1. 读题
题目输入的其实是一棵已经确定结构的二叉树，我们要做的只是从根结点出发，找到最深的那一层。由于每个结点的左右孩子编号都已经直接给出，因此建树本身并不复杂。

### 2. 性质观察
二叉树深度本质上就是“从根出发遍历整棵树时，遇到的最大层数”。无论采用深度优先还是广度优先，都能得到答案。

但本题的结点数可达到 $10^6$。如果树退化成一条长链，递归 DFS 可能产生很深的调用栈，不够稳妥，因此更适合使用队列 BFS 或显式栈进行迭代遍历。

### 3. 程序设计思路
可以先用两个数组分别存每个结点的左儿子和右儿子，然后从根结点 `1` 开始做层次遍历：
1. 根结点入队，并记录当前层数为 `1`；
2. 每次取出一个结点时，查看它的左右儿子；
3. 若左儿子存在，就把它与“当前层数加一”一起入队；
4. 若右儿子存在，也做同样处理；
5. 在遍历过程中不断更新遇到的最大层数；
6. 队列清空后，最大层数就是整棵树的深度。

### 4. 数据结构与算法选择
本题适合使用数组存树，再配合队列进行广度优先遍历。数组便于按编号直接访问孩子结点，BFS 又能自然按层推进，并避免递归造成的栈深问题。

### 5. 时空复杂度分析
- 时间复杂度：$O(n)$，每个结点最多只会入队、出队各一次。
- 空间复杂度：$O(n)$，需要存储整棵树的左右儿子信息，遍历时队列最坏也可能达到线性规模。

在 $10^6$ 级别数据下，线性遍历是合理且必要的做法。

## 代码实现

```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int n = 0;
	scanf("%d", &n);
	int* left = (int*)calloc((n+1) , sizeof(int));
	int* right = (int*)calloc((n+1) , sizeof(int));
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &left[i], &right[i]);
	}
	int* queue = (int*)malloc((n+1) * sizeof(int));
	queue[0] = 1;
	int front = 0;
	int rear = 1;
	int depth = 0;
	while (front < rear)
	{
		depth++;
		int size = rear - front;
		for (int i = 0; i < size; i++)
		{
			int temp = queue[front];
			if (left[temp] != 0)
			{
				queue[rear++] = left[temp];
			}
			if (right[temp] != 0)
			{
				queue[rear++] = right[temp];
			}
			front++;
		}
	}
	free(left);
	free(right);
	free(queue);
	printf("%d\n", depth);
	return 0;
}
```
