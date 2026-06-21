# [GKS 2018 #E] Yogurt

## 题目描述

Yogurt can be a nutritious part of an appetizer, main course, or dessert, but it must be consumed before it expires, and it might expire quickly! Moreover, different cups of yogurt might expire on different days.

Lucy loves yogurt, and she has just bought $N$ cups of yogurt, but she is worried that she might not be able to consume all of them before they expire. The i-th cup of yogurt will expire $A_i$ days from today, and a cup of yogurt cannot be consumed on the day it expires, or on any day after that.

As much as Lucy loves yogurt, she can still only consume at most $K$ cups of yogurt each day. What is the largest number of cups of yogurt that she can consume, starting from today?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with one line containing two integers $N$ and $K$, as described above. Then, there is one more line with $N$ integers $A_i$, as described above.

## 输出格式

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum number of cups of yogurt that Lucy can consume, as described above.

## 样例

### 样例输入1
```2
2 1
1 1
5 1
3 2 3 2 3
```

### 样例输出1
```Case #1: 1
Case #2: 3
```

### 样例输入2
```2
2 2
1 1
6 2
1 1 1 7 7 7
```

### 样例输出2
```Case #1: 2
Case #2: 5
```

## 提示

In Sample Case #1, each of the two cups of yogurt will expire in one day. Today, Lucy can consume one of them, but she can only consume at most one cup each day, so she cannot consume both. Tomorrow, Lucy cannot consume the remaining cup of yogurt, because it will have expired.

### Limits

$1 \le T \le 100$.

$1 \le K \le N$.

$1 \le A_i \le 10^9$, for all $i$.

**Small dataset (Test set 1 - Visible)**

$1 \le N \le 1000$.

$K = 1$.

**Large dataset (Test set 2 - Hidden)**

$1 \le N \le 5000$.

## 解题思路

### 问题分析

N 杯酸奶，每杯 A_i 天后过期，每天最多喝 K 杯，求最多喝几杯。

### 核心思路

贪心：按过期时间排序，尽早喝过期的。维护当前天和当天已喝数量。

### 算法流程

1. 按过期时间升序排序
2. 依次尝试每杯：若当前天 < 过期天，喝掉
3. 每 K 杯推移一天

### 复杂度分析

时间 O(n log n)，空间 O(n)
