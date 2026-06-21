# [CCC 2026 S1] Baby Hop, Giant Hop

## 题目描述

Samantha the Frog is hopping between lily pads arranged in a straight line, evenly spaced. There are an infinite number of lily pads. The lily pads are numbered, in order, using integers. For every integer, there is also a lily pad.

Samantha starts on a lily pad numbered $A$ and would like to hop onto a lily pad numbered $B$. She can take a giant hop of length $K$, or a baby hop of length 1. Each hop can be either forwards or backwards.

Samantha would like to know the fewest number of hops needed to get from $A$ to $B$. But sometimes, she would like to know the second fewest number of hops needed.

## 输入格式

The first line of input contains a single integer, $A$, the starting lily pad ($-10^{18} \le A \le 10^{18}$).

The second line of input contains a single integer, $B$, the ending lily pad ($-10^{18} \le B \le 10^{18}$).

The third line of input contains a single integer, $K$, the distance of a giant hop ($2 \le K \le 10^{18}$).

The fourth line of input contains the integer, $T$, which is either 1 or 2, indicating if the fewest (when $T = 1$) or second fewest (when $T = 2$) number of steps should be found.

## 输出格式

On a single line, output:
- the fewest number of hops, if $T = 1$
- the second fewest number of hops, if $T = 2$

required to move from lily pad $A$ to lily pad $B$.

## 样例

### 样例输入1
```0
10
3
1
```

### 样例输出1
```4
```

### 样例输入2
```0
11
4
1
```

### 样例输出2
```4
```

### 样例输入3
```0
11
4
2
```

### 样例输出3
```5
```

### 样例输入4
```0
0
3
1
```

### 样例输出4
```0
```

## 提示

#### Explanation of Output for Sample Input 1

Samantha hops to lily pads labeled $3$, $6$, and $9$, with three giant hops, and then hops to the lily pad labeled $10$ with one baby hop.

#### Explanation of Output for Sample Input 2

Samantha hops to lily pads labeled $4$, $8$, and $12$, with three giant hops, and then hops to the lily pad labeled $11$ with one (backwards) baby hop.

#### Explanation of Output for Sample Input 3

The fewest number of hops needed ($4$) was found in Sample 2. In this input, the second fewest number of steps is to be found, since $T = 2$. Samantha hops to lily pads labeled $4$ and $8$ with two giant hops, and then hops to the lily pad labeled $11$ with three baby hops.


The following table shows how the 15 available marks are distributed:

| Marks Awarded | Bounds on $A, B$ | Bounds on $K$ | Bounds on $T$ | Additional Restrictions |
|:-:|:-:|:-:|:-:|:-:|
| 5 marks | $0 \le A, B \le 10$ | $K = 2$ | $T = 1$ | Only hops in the positive direction needed |
| 6 marks | $-10^{18} \le A, B \le 10^{18}$ | $2 \le K \le 10^{18}$ | $T = 1$ | None |
| 2 marks | $0 \le A, B \le 100$ | $2 \le K \le 4$ | $T = 1$ or $T = 2$ | None |
| 2 marks | $-10^{18} \le A, B \le 10^{18}$ | $2 \le K \le 10^{18}$ | $T = 1$ or $T = 2$ | None |

Note that for full marks, solutions will need to handle 64-bit integers. For example:
- in C/C++, the type **long long** should be used;
- in Java, the type **long** should be used.

## 解题思路

### 问题分析

青蛙从 A 到 B，可走长度 1（baby）或 K（giant），方向任意，求最少或第二少步数。

### 核心思路

最少步数：d = |A-B|。d = qK + r，答案为 q+r 或 q+1+K-r 取较小值。第二少步数枚举更多候选方案取次小值。

### 算法流程

1. 计算 d = |A-B|
2. T=1：取 min(q+r, q+1+K-r)
3. T=2：枚举更多步数组合取第二小

### 复杂度分析

时间 O(1)，空间 O(1)
