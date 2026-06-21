# [USACO08OPEN] Cow Cars S

## 题目描述

N (1 <= N <= 50,000) cows conveniently numbered 1..N are driving in separate cars along a highway in Cowtopia. Cow i can drive in any of M different high lanes (1 <= M <= N) and can travel at a maximum speed of S\_i (1 <= S\_i <= 1,000,000) km/hour.

After their other bad driving experience, the cows hate collisions and take extraordinary measures to avoid them. On this highway, cow i reduces its speed by D (0 <= D <= 5,000) km/hour for each cow in front of it on the highway (though never below 0 km/hour). Thus, if there are K cows in front of cow i, the cow will travel at a speed of max[S\_i - D \* K, 0]. While a cow might actually travel faster than a cow directly in front of it, the cows are spaced far enough apart so crashes will not occur once cows slow down as

described,

Cowtopia has a minimum speed law which requires everyone on the highway to travel at a a minimum speed of L (1 <= L <= 1,000,000) km/hour so sometimes some of the cows will be unable to take the highway if they follow the rules above. Write a program that will find the maximum number of cows that can drive on the highway while obeying the minimum speed limit law.

## 输入格式

\* Line 1: Four space-separated integers: N, M, D, and L

\* Lines 2..N+1: Line i+1 describes cow i's initial speed with a single integer: S\_i

## 输出格式

\* Line 1: A single integer representing the maximum number of cows that can use the highway

## 样例

### 样例输入1
```3 1 1 5 
5 
7 
5
```

### 样例输出1
```2
```

## 提示

There are three cows with one lane to drive on, a speed decrease of 1, and a minimum speed limit of 5.


Two cows are possible, by putting either cow with speed 5 first and the cow with speed 7 second.

## 解题思路

### 问题分析

N 牛 M 车道，速度 S_i 减去前方牛数*D，需 >= L，求最多牛数。

### 核心思路

贪心：按速度降序分配到车道（优先分配到当前牛数少的车道），检查速度是否足够。

### 算法流程

1. 速度降序排序
2. 贪心分配到最小负载车道
3. 检查 S - D*k >= L

### 复杂度分析

时间 O(n log n)，空间 O(n)
