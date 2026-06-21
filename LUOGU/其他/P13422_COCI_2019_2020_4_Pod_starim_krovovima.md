# [COCI 2019/2020 #4] Pod starim krovovima

## 题目描述

Setting: Legendary Zagrebian Inn called Kod Žnidaršića.

Time: The year 1936.

Plot summary: Franjo and his friends are discussing the current events in Abyssinia while enjoying a couple of drinks at the bar. His son, little Perica, is sitting at a small table in the corner of the bar. In front of Perica there are $N$ glasses conveniently numbered from $1$ to $N$. The volume (in nanoliters) of each glass is known as well as the amount of liquid that is currently inside it.

Problem: Little Perica wants to know what is the largest possible number of glasses that can be emptied by pouring the liquid between glasses. He can freely pour any integer number of nanoliters from one glass to another, as many times as he wants, as long as no liquid is spilled over.

Your task is to output the number of empty glasses along with one possible configuration of liquid in all glasses. If there are multiple configurations that yield the same number of empty glasses, output any of them. Note that it is not necessary to minimize the number of times liquid was poured between two glasses.

## 输入格式

The first line contains an integer $N$ ($1 \leq N \leq 1\,000$) from the task description.

Each of the next $N$ lines contains two integers $T_i$ ($0 \leq T_i \leq 10^9$) and $Z_i$ ($1 \leq Z_i \leq 10^9$) which, in that order, represent the current amount of liquid in the $i$-th glass and its volume. Both quantities are given in nanoliters and the current amount of liquid cannot be greater than the volume of the glass, i.e. $T_i \leq Z_i$ holds.

## 输出格式

In the first line you should output the largest number of glasses that can be emptied by pouring the liquid between glasses.

## 样例

### 样例输入1
```5
2 6
1 6
0 6
6 6
5 6
```

### 样例输出1
```2
6 6 2 0 0
```

### 样例输入2
```5
4 5
2 7
5 5
0 10
7 9
```

### 样例输出2
```3
0 0 0 10 8
```

### 样例输入3
```8
2 6
3 4
1 1
9 10
0 10
4 5
6 8
3 9
```

### 样例输出3
```5
0 0 0 9 10 0 0 9
```

## 提示

Clarification of the second example: One of the possible pouring configurations is the following:
1. pour everything from glass 1 into glass 2.
2. pour everything from glass 2 into glass 4.
3. pour four nanoliters from glass 3 into glass 4. pour one nanoliter from glass 3 into glass 5.
Glasses numbered 1, 2 and 3 are now empty.

## 解题思路

### 问题分析

倒酒问题：最大化空杯数。

### 核心思路

贪心：按容量从大到小填充，尽量填满大杯。

### 算法流程

1. 按容量降序排列
2. 依次填充，剩余液体传递给下一个
3. 无法填满的杯子变为空杯

### 复杂度分析

O(n log n)时间，O(n)空间。
