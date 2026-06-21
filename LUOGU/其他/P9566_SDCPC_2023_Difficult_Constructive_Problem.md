# [SDCPC 2023] Difficult Constructive Problem

## 题目描述

Given a string $s_1s_2\cdots s_n$ of length $n$ where $s_i \in \{\text{0}, \text{1}, \text{?}\}$ and an integer $k$, please fill out all the $\text{?}$ with $\text{0}$ or $\text{1}$ such that the number of indices $i$ satisfying $1 \le i < n$ and $s_i \ne s_{i+1}$ equals to $k$. Different $\text{?}$ can be replaced with different characters.

To make this problem even more difficult, we ask you to find the answer with the smallest possible lexicographic order if it exists.

Recall that a string $a_1a_2\cdots a_n$ of length $n$ is lexicographically smaller than another string $b_1b_2\cdots b_n$ of length $n$ if there exists an integer $k$ ($1 \le k \le n$) such that $a_i = b_i$ for all $1 \le i < k$ and $a_k < b_k$.

## 样例

--- Sample 1 ---
Input:
5
9 6
1?010??01
9 5
1?010??01
9 6
100101101
9 5
100101101
9 3
????????1

Output:
100100101
Impossible
100101101
Impossible
000000101

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
