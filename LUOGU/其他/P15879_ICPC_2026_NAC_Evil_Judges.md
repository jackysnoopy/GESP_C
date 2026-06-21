# [ICPC 2026 NAC] Evil Judges

## 题目描述

The evil judges preparing the ICPC problem sets are tired of seeing the talented contestants AC their problems and AK ("all kill") their problem sets. They have grown so tired of this that they've started to dislike any strings where $\texttt{AC}$ or $\texttt{AK}$ appear as subsequences. The judges just found a string $s$ consisting of only the characters $\texttt{A}$, $\texttt{C}$, and $\texttt{K}$ and are determined to destroy these subsequences!

In one operation, the judges are able to swap two adjacent characters in the string $s$. To be more precise, the judges may choose an index $i$ ($1 \le i < |s|$) and swap $s_i$ and $s_{i+1}$. The judges are very busy and don't have much time, so they can only do this operation up to $M$ times (independently choosing an index $i$ each time).

The judges' goal is to minimize the number of subsequences ($\textbf{possibly non-contiguous}$) that are $\texttt{AC}$ or $\texttt{AK}$. Help them calculate the number of $\texttt{AC}$ and $\texttt{AK}$ subsequences that remain within $s$ after the judges perform an optimal sequence of up to $M$ swap operations.

## 输入格式

The first line of input contains the string $s$ $(1 \leq |s| \leq 2\cdot 10^5)$. The string consists only of the characters $\texttt{A}$, $\texttt{C}$, and $\texttt{K}$.

The second line contains an integer $M$ $(0 \leq M \leq 2\cdot 10^9)$, the maximum number of swaps the judges can perform.

## 输出格式

Print the minimum total number of $\texttt{AC}$ and $\texttt{AK}$ subsequences that remain in $s$ after an optimal sequence of at most $M$ swap operations.

## 样例

### 样例输入1
```ACAACCAK
5
```

### 样例输出1
```6
```

### 样例输入2
```CCKKAKCKCK
1000000000
```

### 样例输出2
```0
```

### 样例输入3
```AAAAAAAAACCCCCCCCC
13
```

### 样例输出3
```68
```

## 提示

### Explanation of Sample Input 1

In Sample Input 1, the string $s$ initially has seven different $\texttt{AC}$ subsequences and four different $\texttt{AK}$ subsequences. One optimal choice of five swaps yields the new string $\texttt{ACCCAAKA}$ which only has three $\texttt{AC}$ subsequences and three $\texttt{AK}$ subsequences left.

## 解题思路

### 问题分析

字符串仅含 A/C/K，最多 M 次相邻交换，求最小 AC+AK 子序列数。

### 核心思路

枚举 6 种字母分组排列（如 K-A-C、C-A-K 等），计算每种排列的交换代价和子序列数。代价 <= M 中取最小子序列数。

### 算法流程

1. 统计 A/C/K 各自数量
2. 枚举 6 种排列，计算交换代价（逆序对）
3. 取代价 <= M 中子序列数最小的

### 复杂度分析

时间 O(n)，空间 O(n)
