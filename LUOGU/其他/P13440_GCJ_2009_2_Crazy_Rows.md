# [GCJ 2009 #2] Crazy Rows

## 题目描述

You are given an $N \times N$ matrix with $0$ and $1$ values. You can swap any two adjacent rows of the matrix.

Your goal is to have all the $1$ values in the matrix below or on the main diagonal. That is, for each $X$ where $1 \leq X \leq N$, there must be no $1$ values in row $X$ that are to the right of column $X$.

Return the minimum number of row swaps you need to achieve the goal.

## 输入格式

The first line of input gives the number of cases, $T$. $T$ test cases follow.

The first line of each test case has one integer, $N$. Each of the next $N$ lines contains $N$ characters. Each character is either $0$ or $1$.

## 输出格式

For each test case, output

Case #X: K

where $X$ is the test case number, starting from $1$, and $K$ is the minimum number of row swaps needed to have all the $1$ values in the matrix below or on the main diagonal.

You are guaranteed that there is a solution for each test case.

## 样例

### 样例输入1
```3
2
10
11
3
001
100
010
4
1110
1100
1100
1000
```

### 样例输出1
```Case #1: 0
Case #2: 2
Case #3: 4
```

## 提示

**Limits**

- $1 \leq T \leq 60$

**Small dataset(6 Pts)**

- $1 \leq N \leq 8$

**Large dataset(10 Pts)**

- $1 \leq N \leq 40$

## 解题思路

### 问题分析

行交换使1都在主对角线以下。

### 核心思路

贪心：每行找最右边的1，安排到合适位置。

### 算法流程

1. 计算每行最右边1的位置
2. 从上到下，找满足条件的行交换上来

### 复杂度分析

O(n²)时间，O(n)空间。
