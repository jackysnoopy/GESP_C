# [TOPC 2024] Animal Farm

## 题目描述

On Animal Farm, the animals have rebelled against their human owner and have taken over the management of the farm. To ensure equality and fairness among all the animals, they have decided to create a new set of rules. However, as the new leaders, the pigs have started making changes to the rules to favor themselves.

The farm maintains a hierarchy of animals based on their species, with each animal assigned a specific influence level. This influence level, represented as a positive integer, determines the animal’s priority in decision-making. Within a group, an animal can make decisions if it has the highest influence level among the members.

The pigs have a plan to maximize their collective influence in the leadership council by selecting a specific group of animals. Given a list of animals with their species and influence levels, you are tasked to form the most influential leadership council while adhering to the following rules:

1. Only one pig species is allowed in the council to avoid power conflicts among the pigs.
2. Every council member of non-pig species should have an influence level less than the influence level of the only pig’s in the council.

Determine the maximum total influence levels of the council that can be formed under these rules.

## 输入格式

The first line contains an integer $n$, representing the number of animals. The next $n$ lines each contain a string `species` and a positive integer `influence`:

- `species` is a string representing the species of the animal, e.g., “pig”, “horse”, “cow”, etc.
- `influence` is an integer representing the influence level of the animal.

## 输出格式

Output a single integer, the maximum total influence levels of the leadership council that can be formed following the rules.

## 样例

### 样例输入1
```5
pig 10
horse 15
pig 5
cow 20
sheep 25
```

### 样例输出1
```10
```

### 样例输入2
```5
pig 10
horse 15
pig 15
cow 15
sheep 10
```

### 样例输出2
```25
```

## 提示

- $1 \le n \le 10^5$.
- The length of `species` is at most $10$.
- `species` consists of only English characters in lowercase.
- At least one animal’s species is pig.
- `influence` is at most $10^8$.

## 解题思路

### 问题分析

选一个猪和若干其他动物组 council，其他动物影响力 < 猪的影响力，求最大总影响力。

### 核心思路

对每个猪的影响力，计算所有影响力低于它的动物的总和，取最大值。

### 算法流程

1. 分离猪和其他动物的影响力
2. 对每个猪值，二分查找影响力 < 它的动物数
3. 用前缀和计算总和

### 复杂度分析

时间 O(n log n)，空间 O(n)
