# [SCCPC 2021] True Story

## 题目描述

Chengdu Shuangliu International Airport is the major international airport serving Chengdu, the capital of Sichuan province, China. It handled 55.9 million passengers in 2019, being among the world's 25 busiest airports in 2019, the fourth-busiest in mainland China, and the busiest in western China.

Ema and her friends are gonna be late for their flight. Now at the beginning of hour $0$, they are $x$ km away from the airport, and the boarding time is at the beginning of hour $p_0$. There are $n$ people in total (Ema herself included), and the $i$-th one can travel at a speed of $s_i$ km/h. They will have to reach the airport not later than the boarding time to catch the plane. 

However, all is not lost. Ema knows the boarding time will be postponed. The boarding time will be postponed $k$ times: The $i$-th one will be announced at the beginning of hour $t_i$, and postpone the time later to the beginning of hour $p_i$. There are still challenges, though, as everyone will only move when he/she can catch the plane in time. That is if the current time before boarding is not enough for him/her to arrive at the airport, he or she will stop moving and just stay at that point; Otherwise, he/she will move on again from where he/she has stopped, or just keep on moving.

Note that every time the boarding time is postponed, everyone will instantly change their action accordingly. Also, everyone only knows the postponement when it is announced, and cannot act on it beforehand.

Please calculate how many people can catch the plane in the end.

## 输入格式

There is only one test case in each test file.

The first line contains four integers $n$, $k$, $x$ and $p_0$ ($1 \le n,k \le 10^5$, $1 \le x,p_0 \le 10^9$) indicating the number of people, the number of postponement, the distance from the starting point to the airport and the initial boarding time.

The second line contains $n$ integers $s_1, s_2, \cdots, s_n$ ($1 \le s_i \le 10^9$) indicating the speed of the $i$-th person.

The third line contains $k$ integers $t_1, t_2, \cdots, t_k$ ($1 \le t_i \le 10^9$, $t_i < t_{i+1}$, $t_i < p_{i-1}$) indicating the hour when the $i$-th postponement is announced.

The fourth line contains $k$ integers $p_1, p_2, \cdots, p_k$ ($1 \le p_i \le 10^9$, $p_i < p_{i+1}$) indicating the hour the boarding time is postponed to in the $i$-th announcement.

## 输出格式

Output one line containing one integer indicating the number of people that can catch the plane eventually.

## 样例

### 样例输入1
```4 3 10 4
1 5 2 1
3 4 5
7 9 10
```

### 样例输出1
```2
```

### 样例输入2
```1 3 10 3
1
2 3 4
5 8 10
```

### 样例输出2
```0
```

## 提示

For the first sample test case, at the beginning of hour $0$ only the person with speed $5$km/h starts moving an arrives at the airport at the beginning of hour $2$. Then at the beginning of hour $4$ the person with speed $2$km/h also starts moving an arrives at the airport at the beginning of hour $9$. Only these two people can catch the plane and the other two never moves, as none of the three postponements allow them to arrive in time.

For the second sample test case the only person never moves. If he were to start moving from the very beginning he would catch the plane, however he chose to give up. This story tells us that not all efforts result in success, but giving up is sure to result in failure.

## 解题思路

### 问题分析

机场赶飞机，延期后最多能到多少人。

### 核心思路

二分或枚举延期次数，检查能到的人数。

### 算法流程

1. 枚举0到k次延期
2. 计算新截止时间
3. 统计速度足够的人数

### 复杂度分析

O(n×k)时间，O(n)空间。
