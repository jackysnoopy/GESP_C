# [SDCPC 2019] Stones in the Bucket

## 题目描述

There are $n$ buckets on the ground, where the $i$-th bucket contains $a_i$ stones. Each time one can perform one of the following two operations:

- Remove a stone from one of the non-empty buckets.
- Move a stone from one of the buckets (must be non-empty) to any other bucket (can be empty).

What's the minimum number of times one needs to perform the operations to make all the buckets contain the same number of stones?

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^5$), indicating the number of buckets.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($0 \le a_i \le 10^9$), indicating the number of stones in the buckets.

It's guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.

## 输出格式

For each test case output one line containing one integer, indicating the minimum number of times needed to make all the buckets contain the same number of stones.

## 样例

### 样例输入1
```4
3
1 1 0
4
2 2 2 2
3
0 1 4
1
1000000000
```

### 样例输出1
```2
0
3
0
```

## 提示

For the first sample test case, one can remove all the stones in the first two buckets.

For the second sample test case, as all the buckets have already contained the same number of stones, no operation is needed.

For the third sample test case, one can move 1 stone from the 3rd bucket to the 1st bucket and then remove 2 stones from the 3rd bucket.

## 解题思路

### 问题分析

桶中石头均等化，最小操作数。

### 核心思路

均值分，超出均值的部分即为答案。

### 算法流程

1. 计算总和和均值
2. 累加所有超出均值的量

### 复杂度分析

O(n)时间，O(n)空间。
