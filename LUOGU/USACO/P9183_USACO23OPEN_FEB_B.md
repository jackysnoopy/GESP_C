# [USACO23OPEN] FEB B

## 题目描述

Bessie and Elsie are plotting to overthrow Farmer John at last! They plan it out
over $N$ text messages. Their conversation can be
represented by a string $S$ of length $N$ where $S_i$ is either `B` or `E`,
meaning the $i$ th message was sent by Bessie or Elsie, respectively. 

However, Farmer John hears of the plan and attempts to intercept their
conversation. Thus, some letters of $S$ are `F`, meaning Farmer John obfuscated
the message and the sender is unknown.

The  **excitement level** of a non-obfuscated conversation is the number of
times a cow double-sends - that is, the number of occurrences of substring `BB`
or `EE` in $S$. You want to find the excitement level of the original message,
but you don’t know which of Farmer John’s messages were actually Bessie’s
/ Elsie’s. Over all possibilities, output all possible excitement levels of
$S$.

## 输入格式

The first line will consist of one integer $N$.

The next line contains $S$.

## 输出格式

First output $K$, the number of distinct excitement levels possible. On the next
$K$ lines, output the excitement levels, in increasing order.

## 样例

### 样例输入1
```4
BEEF
```

### 样例输出1
```2
1
2
```

### 样例输入2
```9
FEBFEBFEB
```

### 样例输出2
```2
2
3
```

### 样例输入3
```10
BFFFFFEBFE
```

### 样例输出3
```3
2
4
6
```

## 提示

$1\le N\le 2\cdot 10^5$.

- Inputs 4-8: $N\le 10$.
- Inputs 9-20: No additional constraints.

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
