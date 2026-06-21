# [GCJ 2015 #3] Smoothing Window

## 题目描述

Adamma is a climate scientist interested in temperature. Every minute, she records the current temperature as an integer, creating a long list of integers: $x_{1}, x_{2}, \ldots, x_{\mathrm{N}}$. (Adamma uses her own special temperature scale rather than a familiar one like Celsius or Kelvin, so it's possible for the values to be large and negative!) She often plots these temperatures on her computer screen.

This morning, she decided to compute a sliding average of this list in order to get a smoother plot. She used a smoothing window of size $\mathbf{K}$, which means that she converted the sequence of $\mathbf{N}$ temperatures into a sequence of $(\mathbf{N}-\mathbf{K}+1)$ average temperatures: $s_{1}, s_{2}, \ldots, s_{\mathbf{N}-\mathbf{K}+1}$. Each $s_{i}$ is the average of the values $x_{i}, x_{i+1}, \ldots, x_{i+\mathbf{K}-1}$. The original $x_{i}$ values were all integers, but some of the $s_{i}$ may be fractional.

Unfortunately, Adamma forgot to save the original sequence of temperatures! And now she wants to answer a different question -- what was the difference between the largest temperature and the smallest temperature? In other words, she needs to compute $\max \left\{x_{1}, \ldots, x_{\mathrm{N}}\right\}-\min \left\{x_{1}, \ldots, x_{\mathrm{N}}\right\}$. But she only has $\mathrm{N}, \mathrm{K}$, and the smoothed sequence.

After some thinking, Adamma has realized that this might be impossible because there may be several valid answers. In that case, she wants to know the smallest possible answer among all of the possible original sequences that could have produced her smoothed sequence with the given values of $\mathrm{N}$ and $\mathrm{K}$.

## 样例

--- Sample 1 ---
Input:
3
10 2
1 2 3 4 5 6 7 8 9
100 100
-100
7 3
0 12 0 12 0
Output:
Case #1: 5
Case #2: 0
Case #3: 12

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
