# [ICPC 2024 Tehran R] Boat

## 题目描述

A river separates Upper Barareh from Lower Barareh. To transport people between these two towns, a **two-seater** (a boat that can carry at most two people) with a certain weight capacity has been provided. This boat must be steered by at least one person. i.e. it can not move across the river without any passengers.

The National Barareh Festival is scheduled to be held in Upper Barareh. All Lower Barareh residents want to participate in this celebration and need to move to Upper Barareh as quickly as possible. Your task is to help them move to Upper Barareh with the minimum number of boat trips across the river.

## 输入格式

The first line of the input contains two integers $n$ and $w$, where $n$ is the number of Lower Barareh residents ($1 \leq n \leq 1000$), and $w$ is the maximum weight the boat can carry ($1 \leq w \leq 10^6$). The next line contains $n$ space-separated integers, describing the weights of the residents of Lower Barareh. All the weights are positive integers not exceeding $10^6$.

## 输出格式

If it is not possible to transfer all the residents of Lower Barareh, print a single line containing $-1$ in the output. Otherwise, print the minimum number of times the boat must travel between Lower Barareh and Upper Barareh (in both directions) in order to transfer all residents of Lower Barareh to Upper Barareh.

## 样例

### 样例输入1
```3 7
1 3 4
```

### 样例输出1
```3
```

### 样例输入2
```3 4
2 3 4
```

### 样例输出2
```-1
```

## 提示



## 解题思路

### 问题分析

过河问题，最少渡河次数。

### 核心思路

经典过河问题公式。

### 算法流程

1. n<=2: 1次
2. n>=3: 2n-3次

### 复杂度分析

O(1)时间，O(1)空间。
