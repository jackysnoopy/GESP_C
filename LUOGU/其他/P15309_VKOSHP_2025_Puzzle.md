# [VKOSHP 2025] Puzzle

## 题目描述

You are presented with a puzzle. Given a table of $n$ rows and $m$ columns filled with zeros and ones. 

Only one type of move is allowed: within any column, you can rearrange the elements freely,  changing the order of the rows in that column in any way. The number of zeros and ones in each column remains the same.

You are allowed to make as many such moves as you want. The goal of the puzzle is to obtain as many completely identical rows as possible.

Determine the maximum number of rows that can be made completely identical using the described moves.

## 输入格式

The first line contains two integers $n$ and $m$ ($1 \le n, m \le 10^5$; $nm \le 2 \cdot 10^5$) --- the number of rows and columns.

Each of the following $n$ lines contains $m$ characters $\tt{0}$ or $\tt{1}$ --- the elements of the initial table.

## 输出格式

Output a single integer --- the maximum number of identical rows that can be obtained.

## 样例

### 样例输入1
```3 4
0101
0010
0100
```

### 样例输出1
```2
```

## 提示



## 解题思路

### 问题分析

可自由重排每列的 0/1，求最多能有多少行完全相同。

### 核心思路

每列有固定数量的 0 和 1。要使 k 行相同，需要每列至少有 k 个相同的值。对每列取 max(ones, zeros)，取所有列的最小值。

### 算法流程

1. 统计每列的 1 的个数
2. 每列可提供的最大相同行数 = max(ones, n-ones)
3. 取所有列的最小值

### 复杂度分析

时间 O(nm)，空间 O(m)
