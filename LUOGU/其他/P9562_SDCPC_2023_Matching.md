# [SDCPC 2023] Matching

## 题目描述

Given an integer sequence $a_1, a_2, \cdots, a_n$ of length $n$, we construct an undirected graph $G$ from the sequence. More precisely, for all $1 \le i < j \le n$, if $i - j = a_i - a_j$, there will be an undirected edge in $G$ connecting vertices $i$ and $j$. The weight of the edge is $(a_i + a_j)$.

Find a matching of $G$ so that the sum of weight of all edges in the matching is maximized, and output this maximized sum.

Recall that a matching of an undirected graph means that we choose some edges from the graph such that any two edges have no common vertices. Specifically, not choosing any edge is also a matching.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($2 \le n \le 10^5$) indicating the length of the sequence.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($-10^9 \le a_i \le 10^9$) indicating the sequence.

It's guaranteed that the sum of $n$ of all test cases will not exceed $5 \times 10^5$.

## 输出格式

For each test case output one line containing one integer indicating the maximum sum of weight of all edges in a matching.

## 样例

### 样例输入1
```3
9
3 -5 5 6 7 -1 9 1 2
3
-5 -4 -3
3
1 10 100
```

### 样例输出1
```30
0
0
```

## 提示

For the first sample test case, the optimal choice is to choose the three edges connecting vertex $3$ and $5$, vertex $4$ and $7$, and finally vertex $8$ and $9$. The sum of weight is $(5 + 7) + (6 + 9) + (1 + 2) = 30$.

For the second sample test case, as all edges have negative weights, the optimal matching should not choose any edge. The answer is $0$.

For the third sample test case, as there is no edge in the graph, the answer is $0$.

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
