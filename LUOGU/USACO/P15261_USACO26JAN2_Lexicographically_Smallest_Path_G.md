# [USACO26JAN2] Lexicographically Smallest Path G

## 题目描述

Bessie is given an undirected graph with $N$ ($1\le N\le 2 \cdot 10^5$) vertices labeled $1\dots N$ and $M$ edges ($N - 1\le M\le 2 \cdot 10^5$). Each edge is described by two integers $u, v$ ($1\le u, v \le N$) describing an undirected edge between nodes $u$ and $v$ and a lowercase Latin letter $c$ in the range a..z that is the value on the edge. The graph given is guaranteed to be connected. There may be multiple edges or self-loops.

Define $f(a, b)$ as the lexicographically smallest concatenation of edge values over all paths starting from node $a$ and ending at node $b$. A path may contain the same edge more than once (i.e., cycles are allowed).

For each $i$ ($1\le i \le N$), help Bessie determine the length of $f(1, i)$. Output this length if it is finite, otherwise output $-1$.

## 样例

--- Sample 1 ---
Input:
2
1 0
2 2
1 1 a
2 1 b
Output:
0
0 -1
--- Sample 2 ---
Input:
2
7 7
1 2 a
1 3 a
2 4 b
3 5 a
5 6 a
6 7 a
7 4 a
4 3
1 2 z
2 3 x
3 4 y
Output:
0 1 1 5 2 3 4
0 1 2 -1

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
