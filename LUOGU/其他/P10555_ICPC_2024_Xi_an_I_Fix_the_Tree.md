# [ICPC 2024 Xi'an I] Fix the Tree

## 题目描述

You are given a tree consisting of $n$ vertices. Each vertex $i$ of this tree has a value $w_i$ assigned to it.

Now the vertex $u$ will be broken. Once it's broken, vertex $u$ and all edges with one end at vertex $u$ will be removed from the tree.

To make the tree connected, you can do the following operation any number of times(possibly zero) in any order:

- First choose two vertices $u$ and $v$ from the tree;
- Then pay $w_u+w_v$ coins, and add an edge between vertices $u$ and $v$;
- At last, replace $w_u+1$ with $w_u$, replace $w_v+1$ with $w_v$.

Your task is to calculate the minimum number of coins to be paid.

But you don't know which vertex $u$ is, so you need to find the answer for each $1\le u\le n$. Please answer all the queries independently.

## 样例

--- Sample 1 ---
Input:
6
1 1 1 1 1 1
1 2
1 3
1 4
2 5
2 6
Output:
4 4 0 0 0 0
--- Sample 2 ---
Input:
4
1 2 3 4
1 2
1 3
1 4
Output:
12 0 0 0
--- Sample 3 ---
Input:
7
1 2 3 4 5 6 7
1 2
1 3
2 4
2 5
3 6
3 7
Output:
5 12 16 0 0 0 0

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
