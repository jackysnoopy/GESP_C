# [GKS 2020 #A] Allocation

## 题目描述

There are $N$ houses for sale. The $i$-th house costs $A_i$ dollars to buy. You have a budget of $B$ dollars to spend.

What is the maximum number of houses you can buy?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a single line containing the two integers $N$ and $B$. The second line contains $N$ integers. The $i$-th integer is $A_i$, the cost of the $i$-th house.

## 输出格式

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum number of houses you can buy.

## 样例

### 样例输入1
```3
4 100
20 90 40 90
4 50
30 30 10 10
3 300
999 999 999
```

### 样例输出1
```Case #1: 2
Case #2: 3
Case #3: 0
```

## 提示

In Sample Case #1, you have a budget of $100$ dollars. You can buy the 1st and 3rd houses for $20+40=60$ dollars.

In Sample Case #2, you have a budget of $50$ dollars. You can buy the 1st, 3rd and 4th houses for $30+10+10=50$ dollars.

In Sample Case #3, you have a budget of $300$ dollars. You cannot buy any houses (so the answer is $0$).

### Limits

$1 \le T \le 100$.

$1 \le B \le 10^5$.

$1 \le A_i \le 1000$, for all $i$.

**Test Set 1**

$1 \le N \le 100$.

**Test Set 2**

$1 \le N \le 10^5$.

## 解题思路

### 问题分析

N 栋房子价格 A_i，预算 B，求最多买几栋。

### 核心思路

贪心：按价格排序，从便宜的开始买，直到超预算。

### 算法流程

1. 排序
2. 累加价格，若 <= B 则计数+1

### 复杂度分析

时间 O(n log n)，空间 O(n)
