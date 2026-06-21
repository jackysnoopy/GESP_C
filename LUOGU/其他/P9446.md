# P9446 - ICPC 2021 WF Prehistoric Programs

## 题目描述

参见洛谷原题。

## 解题思路

### 问题分析

n 个括号串，排列成合法括号序列。求排列方案或判断 impossible。

### 核心思路

贪心 + 匹配。计算每个串的 balance 和 min_balance。按 balance 分类，贪心拼接。

### 复杂度分析

时间复杂度：O(n log n + total_length)，空间复杂度：O(n)

### 关键技巧

关键：先放 balance ≥ 0 的串（按 min_balance 降序），再放 balance < 0 的串（按 min_balance 升序）。

## 参考代码

请参见同目录下的 `P9446.cpp`。
