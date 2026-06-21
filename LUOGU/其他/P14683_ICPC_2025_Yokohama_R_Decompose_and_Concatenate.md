# [ICPC 2025 Yokohama R] Decompose and Concatenate

## 题目描述

You are given an integer greater than or equal to 2. When this number is decomposed into the sum of two **positive integers**, a new integer number can be formed as the concatenation of the decimal representations of the two integers. Find the maximum possible number formed in this way.

For example, 102 can be decomposed and concatenated as follows.

$$
1 + 101 \ \rightarrow \ 1101
$$
$$
2 + 100 \ \rightarrow \ 2100
$$
$$
3 + 99 \ \rightarrow \ 399
$$
$$
4 + 98 \ \rightarrow \ 498
$$
$$
\vdots
$$
$$
101 + 1 \ \rightarrow \ 1011
$$

Among them, $92 + 10 \ \rightarrow \ 9210$ is the largest.

## 输入格式

The input consists of a single test case in a single line. The line contains an integer between $2$ and $10^{17}$, inclusive, which is the integer to be decomposed and concatenated.

## 输出格式

Output the maximum possible number in a line.

## 样例

### 样例输入1
```8
```

### 样例输出1
```71
```

### 样例输入2
```2025
```

### 样例输出2
```10251000
```

### 样例输入3
```102
```

### 样例输出3
```9210
```

### 样例输入4
```99999999999999999
```

### 样例输出4
```8999999999999999910000000000000000
```

## 提示



## 解题思路

### 问题分析

字符串分解拼接问题。

### 核心思路

统计唯一字符。

### 算法流程

1. 统计字符串中不同字符数
2. 输出计数

### 复杂度分析

O(n)时间，O(1)空间。
