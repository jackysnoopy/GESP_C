# [ICPC 2020 Shanghai R] Rice Arrangement

## 题目描述

Wowo is a hospitable Xinjiang uncle. $k$ guests will have Uyghur Polo (a traditional Uyghur food) in Wowo's house around a big round table. $n$ ($n\ge k$) chairs are placed around the table uniformly. Each guest sits on a chair and no two guests sit on the same chair. $k$ bowls of Uyghur Polo are on the table. Each bowl is next to some chair ($\textbf{with or without}$ some guest sitting on it). No two bowls locate at the same position.

![](https://cdn.luogu.com.cn/upload/image_hosting/q3gqhsvq.png)

As a waiter, you are supposed to assign each person with exactly one bowl of Uyghur Polo. The table can be rotated, so each time you can turn it $\frac{2\pi}{n}$ degrees clockwise or counterclockwise. The bowls turn with the table while the chairs and guests do not move. When one bowl of Uyghur Polo is in front of a guest, he can either take it or wait for another.

You want to minimize the total times of table rotating so that everybody can have meals as quickly as possible.

(Formal definition: The boundary of the table is a circle. $n$ chairs are at $n$ points on the circle whose convex hull is a regular polygon with $n$ vertices. We name the points $0,\ldots, n-1$ in counterclockwise order. The $i$-th bowl is at point $b_i$ ($0\le b_i<n$) initially. The $i$-th guest is at point $a_i$ ($0\le a_i < n$) initially. If you turn the table counterclockwise, the bowl at point $b_i$ ($1\le i\le k$) will be moved to point $(b_i+ 1) \bmod n$ after the rotation. If you turn the table clockwise, the bowl at point $b_i$ ($1\le i\le k$) will be moved to point $(b_i-1) \bmod n$ after the rotation. ($x\bmod n$ is defined as the smallest nonnegative integer $r$ such that $x-r$ is a multiple of $n$.))

## 样例

--- Sample 1 ---
Input:
1
4 2
0 3
1 2
Output:
2
--- Sample 2 ---
Input:
1
14 5
0 12 13 8 9
9 2 6 13 5
Output:
6

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
