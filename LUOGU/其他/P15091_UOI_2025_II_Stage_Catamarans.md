# [UOI 2025 II Stage] Catamarans

## 题目描述

A group of $n$ people plans to go for a ride on catamarans.

As the leader of the group, you have been tasked with ordering the catamarans. You know that one catamaran can hold a weight of no more than $100$ kilograms, and you also know the weight of each group member.

You are aware that in your group, a person can weigh either $20$, $40$, $60$, $80$, or $100$ kilograms.

To spend as little money as possible, you decided to write a program that calculates the minimum number of catamarans needed.

## 输入格式

The first line contains one integer $n$ $(1 \le n \le 1\,000)$~--- the number of people in the group.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ $(a_i \in \{20, 40, 60, 80, 100\})$~--- the weight of each person.

## 输出格式

Output one integer --- the minimum number of catamarans needed.

## 样例

### 样例输入1
```4
20 40 80 80
```

### 样例输出1
```3
```

### 样例输入2
```4
20 40 20 20
```

### 样例输出2
```1
```

## 提示

In the first example, we can seat the first two people in one catamaran, the third person in the second catamaran, and the fourth person in the third catamaran. We cannot seat everyone in two catamarans because person $2$ cannot sit with person $3$ or $4$, and person $3$ cannot sit with person $4$ either.

In the second example, we can seat everyone in one catamaran because their total weight is equal to $100$ kilograms, which means the catamaran can hold them.

## 解题思路

### 问题分析

求排序后所有数对差值之和。

### 核心思路

排序后，每个 a[i] 被减去 (n-i-1) 次（作为较小值），被加了 i 次（作为较大值）。总贡献 = a[i] * (n-i-1)。

### 算法流程

1. 排序
2. 对每个位置 i，累加 a[i] * (n-i-1)

### 复杂度分析

时间 O(n log n)，空间 O(n)
