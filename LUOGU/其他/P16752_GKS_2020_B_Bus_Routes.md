# [GKS 2020 #B] Bus Routes

## 题目描述

Bucket is planning to make a very long journey across the countryside by bus. Her journey consists of $N$ bus routes, numbered from 1 to $N$ in the order she must take them. The buses themselves are very fast, but do not run often. The $i$-th bus route only runs every $X_i$ days.

More specifically, she can only take the $i$-th bus on day $X_i$, $2X_i$, $3X_i$ and so on. Since the buses are very fast, she can take multiple buses on the same day.

Bucket must finish her journey by day $D$, but she would like to start the journey as late as possible. What is the latest day she could take the first bus, and still finish her journey by day $D$?

It is guaranteed that it is possible for Bucket to finish her journey by day $D$.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing the two integers $N$ and $D$. Then, another line follows containing $N$ integers, the $i$-th one is $X_i$.

## 输出格式

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the latest day she could take the first bus, and still finish her journey by day $D$.

## 样例

### 样例输入1
```3
3 10
3 7 2
4 100
11 10 5 50
1 1
1
```

### 样例输出1
```Case #1: 6
Case #2: 99
Case #3: 1
```

## 提示

In Sample Case #1, there are $N = 3$ bus routes and Bucket must arrive by day $D = 10$. She could:

*   Take the 1st bus on day $6$ ($X_1 = 3$),
*   Take the 2nd bus on day $7$ ($X_2 = 7$) and
*   Take the 3rd bus on day $8$ ($X_3 = 2$).

In Sample Case #2, there are $N = 4$ bus routes and Bucket must arrive by day $D = 100$. She could:

*   Take the 1st bus on day $99$ ($X_1 = 11$),
*   Take the 2nd bus on day $100$ ($X_2 = 10$),
*   Take the 3rd bus on day $100$ ($X_3 = 5$) and
*   Take the 4th bus on day $100$ ($X_4 = 50$),

In Sample Case #3, there is $N = 1$ bus route and Bucket must arrive by day $D = 1$. She could:

*   Take the 1st bus on day $1$ ($X_1 = 1$).

### Limits

$1 \le T \le 100$.

$1 \le X_i \le D$.

$1 \le N \le 1000$.

It is guaranteed that it is possible for Bucket to finish her journey by day $D$.

**Test Set 1**

$1 \le D \le 100$.

**Test Set 2**

$1 \le D \le 10^{12}$.

## 解题思路

### 问题分析

N 班公交各每 X_i 天一班，最晚第 D 天到达，求最晚出发日。

### 核心思路

逆向贪心：从最后一天 D 开始，每班车取 <= 当前天的最大 X_i 的倍数。

### 算法流程

1. day = D
2. 从最后一班车逆向：day = (day / X[i]) * X[i]
3. 输出 day

### 复杂度分析

时间 O(n)，空间 O(n)
