# [ICPC 2022 Xi'an R] Find Maximum

## 题目描述

We define a function $f(x)$ over all non-negative integer $x$ as follows:
$$
f(x) =
\begin{cases}
1 & (x = 0) \\
f(\frac{x}{3}) + 1 & (x > 0\land x\bmod3 = 0) \\
f(x - 1) + 1  & (x > 0\land x\bmod 3\neq 0)
\end{cases}
$$
Calculate $\max_{x = l} ^ r f(x)$.

You need to answer $T$ queries independently.

## 输入格式

The first line contains a single integer $T$ ($1\leq T\leq 10 ^ 4$).

Each of the next $T$ lines contains two integers $l$ and $r$ ($1\leq l\leq r\leq 10 ^ {18}$), representing a query.

## 输出格式

Output $T$ lines. The $i$-th line contains a single integer, representing the answer to the $i$-th query.

## 样例

### 样例输入1
```10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
```

### 样例输出1
```3
3
4
5
3
4
5
4
5
5
```

## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem E.

**Author**: MagicSpark.

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
