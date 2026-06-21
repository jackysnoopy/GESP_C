# [ICPC 2025 Xi'an R] Grand Voting

## 题目描述

Dada organized a contest, but it received heavy downvotes. He decided to start manipulating the comments.

This contest has $s$ votes, initially set to $0$.

There are $n$ participants, each with a voting parameter $a_i$. When it's their turn to vote:

- If $s \geq a_i$, they cast an upvote, incrementing $s$ by $1$.
- If $s < a_i$, they cast a downvote, decrementing $s$ by $1$.

Dada can control the voting order of these $n$ people. He wants to know the maximum and minimum possible vote count $s$ in this contest.

## 输入格式

The first line of input contains a single integer $n$ ($1 \leq n \leq 10^5$), representing the number of voters.

The next line of input contains $n$ integers $a_1, a_2, \cdots, a_n$ ($|a_i| \leq 10^5$), separated by spaces.

## 输出格式

Output one line containing two integers separated by a space, representing the maximum and minimum vote count $s$ in this contest.

## 样例

### 样例输入1
```5
-1 0 1 2 3
```

### 样例输出1
```5 -5
```

## 提示

For example, if you rearrange $a$ to $[-1, 0, 1, 2, 3]$, initially $s = 0$. Since $s \geq a_1 = -1$, the first voter casts an upvote, making $s = 1$. Similarly, the remaining four voters also satisfy $s \geq a_i$, so all cast upvotes. The final value of $s$ is $5$, which is the maximum possible.

Conversely, if you rearrange $a$ to $[1, 2, 0, 3, -1]$, then for each voter from left to right, $s < a_i$ holds, so all cast downvotes, resulting in $s = -5$. This is the minimum possible. Another arrangement such as $[3, 2, 1, 0, -1]$ also leads to $s = -5$.

## 解题思路

### 问题分析

投票问题，找多数元素。

### 核心思路

Boyer-Moore多数投票算法。

### 算法流程

1. 维护候选和计数
2. 相同+1，不同-1，归零换候选
3. 验证候选是否真正多数

### 复杂度分析

O(n)时间，O(1)空间。
