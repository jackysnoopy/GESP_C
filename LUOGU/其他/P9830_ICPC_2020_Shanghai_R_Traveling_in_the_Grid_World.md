# [ICPC 2020 Shanghai R] Traveling in the Grid World

## 题目描述

Consider a grid pattern with $n$ rows and $m$ columns. There are $(n+1)\times(m+1)$ grid points in total which is the intersections of $n+1$ horizontal lines and $m+1$ vertical lines. We number the horizontal lines from $0$ to $n$ from top to bottom. We number the vertical lines from $0$ to $m$ from left to right. The intersection of horizontal line $i$ and vertical line $j$ is named $(i, j)$ ($0\le i\le n, 0\le j\le m$).

There are some constraints when you travel in the grid world. When you are located at point $(x,y)$, you can choose a destination $(x',y')$ and walk to it along the line segment between $(x, y)$ and $(x', y')$. We call this operation a $\textit{walk}$. A walk is forbidden if there exists another grid point different from $(x, y)$ and $(x', y')$ lying on the line segment between them. You can walk as many times as you want but the directions of two consecutive walks cannot be the same. (Specifically, if you walk from $(x_0, y_0)$ to $(x_1, y_1)$ and then walk from $(x_1, y_1)$ to $(x_2, y_2)$, you must make sure that $(x_0-x_1)(y_1-y_2)\neq (x_1-x_2)(y_0-y_1)$.) The length of a walk from $(x, y)$ to $(x', y')$ is defined as the Euclidean distance between the two endpoints, $\sqrt{(x-x')^2+(y'-y)^2}$.

Starting from $(0,0)$, you are planning to arrive at $(n,m)$ by several walks. Because of the annoying rules, you may need some turning points to achieve your goal. Please find the minimum total length of your walks.

## 样例

--- Sample 1 ---
Input:
2
2 2
2 3
Output:
3.236067977499790
3.605551275463989

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
