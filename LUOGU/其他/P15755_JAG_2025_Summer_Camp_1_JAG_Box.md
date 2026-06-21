# [JAG 2025 Summer Camp #1] JAG Box

## 题目描述

The JAG Box is an ordinary rectangular box that is currently popular around the world. There are $N$ JAG Boxes. For each $i = 1, 2, \ldots, N$, the $i$-th box has an integer weight $A_i$.

You will build a vertical stack by repeatedly choosing one remaining box and inserting it at the very bottom of the current stack. When a box of weight $w$ is inserted at the bottom of the existing stack whose total weight is $x$, that box receives load equal to $\left\lfloor \frac{x}{w} \right\rfloor$.

Determine the minimum possible total load over all boxes.

## 输入格式

The input is given in the following format:

$$\begin{aligned} &N \\ &A_1 \ A_2 \ \ldots \ A_N \end{aligned}$$

- $2 \leq N \leq 200\,000$
- $1 \leq A_i \leq 10^9$ ($1 \leq i \leq N$)
- All input values are integers.

## 输出格式

Output the answer in a single line.

## 样例

### 样例输入1
```5
3 1 4 1 5
```

### 样例输出1
```3
```

## 提示



## 解题思路

### 问题分析

N 个箱子依次放到底部，负载 = floor(上面总重/当前箱重)，求最小总负载。

### 核心思路

从重到轻排列，重的在下面减少负载。贪心排序后模拟。

### 算法流程

1. 按重量降序排序
2. 模拟放置，累加负载
3. 输出总负载

### 复杂度分析

时间 O(n log n)，空间 O(n)
