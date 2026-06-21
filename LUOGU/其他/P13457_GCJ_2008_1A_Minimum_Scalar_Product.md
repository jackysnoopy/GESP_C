# [GCJ 2008 #1A] Minimum Scalar Product

## 题目描述

You are given two vectors $v_1 = (x_1, x_2, ..., x_n)$ and $v_2 = (y_1, y_2, ..., y_n)$. The scalar product of these vectors is a single number, calculated as $x_1y_1 + x_2y_2 + ... + x_ny_n$.

Suppose you are allowed to permute the coordinates of each vector as you wish. Choose two permutations such that the scalar product of your two new vectors is the smallest possible, and output that minimum scalar product.

## 输入格式

The first line of the input file contains integer number $T$ - the number of test cases. For each test case, the first line contains integer number $n$. The next two lines contain $n$ integers each, giving the coordinates of $v_1$ and $v_2$ respectively.

## 输出格式

For each test case, output a line

Case #$X$: $Y$

where $X$ is the test case number, starting from 1, and $Y$ is the minimum scalar product of all permutations of the two given vectors.

## 样例

### 样例输入1
```2
3
1 3 -5
-2 4 1
5
1 2 3 4 5
1 0 1 0 1
```

### 样例输出1
```Case #1: -25
Case #2: 6
```

## 提示

**Limits**

**Small dataset (5 Pts, Test set 1 - Visible)**

- $T = 1000$
- $1 \leq n \leq 8$
- $-1000 \leq x_i, y_i \leq 1000$

**Large dataset (10 Pts, Test set 2 - Hidden)**

- $T = 10$
- $100 \leq n \leq 800$
- $-100000 \leq x_i, y_i \leq 100000$

## 解题思路

### 问题分析

最小化向量点积。

### 核心思路

排序：一个升序一个降序配对。

### 算法流程

1. 排序v1升序，v2降序
2. 对应位置相乘求和

### 复杂度分析

O(n log n)时间，O(n)空间。
