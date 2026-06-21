# [GKS 2020 #G] Maximum Coins

## 题目描述

Mike has a square matrix with $N$ rows and $N$ columns. Cell $(i,j)$ denotes the cell present at row $i$ and column $j$. Cell $(1,1)$ denotes the top left corner of the matrix. Each cell has some amount of coins associated with it and Mike can collect them only if he visits that cell. $C_{i,j}$ represents the number of coins in cell with row $i$ and column $j$. From a cell $(i,j)$, Mike can decide to go to cell $(i+1,j+1)$ or cell $(i-1,j-1)$, as long as the cell lies within the boundaries of the matrix and has not been visited yet. He can choose to start the journey from any cell and choose to stop at any point. Mike wants to maximize the number of coins he can collect. Please help him determine the maximum number of coins he can collect.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing the integer $N$. The next $N$ lines contain $N$ integers each. The $j$-th integer in the $i$-th line represents the number of coins $C_{i,j}$ in cell $(i,j)$.

## 输出格式

For each test case, output one line containing Case #$x$: $y$, where $x$ is the test case number (starting from $1$) and $y$ is the maximum number of coins Mike can collect.

## 样例

### 样例输入1
```2
3
1 2 5
3 6 1
12 2 7
5
0 0 0 0 0
1 1 1 1 0
2 2 2 8 0
1 1 1 0 0
0 0 0 0 0
```

### 样例输出1
```Case #1: 14
Case #2: 9
```

## 提示

In Sample Case #$1$, the maximum number of coins collected can be $14$, if Mike follows this path:

$(1,1) \to (2,2) \to (3,3)$

In Sample Case #$2$, the maximum number of coins collected can be $9$, if Mike follows this path:

$(2,3) \to (3,4)$.

### Limits

$1 \le T \le 100$.

$0 \le C_{i,j} \le 10^7$.

**Test Set $1$**

$1 \le N \le 100$.

**Test Set $2$**

$1 \le N \le 10^3$ in at most $10$ cases.

$1 \le N \le 100$ in all other cases.

## 解题思路

### 问题分析

N*N 矩阵，可沿对角线 (i+1,j+1) 或 (i-1,j-1) 移动，求最大收集金币数。

### 核心思路

沿 i-j=const 的对角线收集，每条对角线求和取最大。

### 算法流程

1. 枚举所有对角线 (i-j 从 -(n-1) 到 n-1)
2. 每条对角线求和
3. 取最大值

### 复杂度分析

时间 O(n^2)，空间 O(n^2)
