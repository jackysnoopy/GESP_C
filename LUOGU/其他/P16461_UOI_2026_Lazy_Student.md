# [UOI 2026] Lazy Student

## 题目描述

Kozak Vus is a student at a university. In the first semester, he has $n$ subjects and $m$ weeks of study ahead of him. Vus knows all the assignments in advance, and for convenience he has estimated their difficulty. He made a table of size $n \times m$, where for the $i$-th subject in the $j$-th week he has to complete an assignment of difficulty $a_{i, j}$. Note that all difficulty values are $\textbf{pairwise distinct}$ across the entire table.

Vus calls the $\textit{difficulty of a week}$ the total difficulty of the assignments from all subjects in that week.

Vus did not get enough vacation to rest, so he wants to avoid working too hard, at least at the beginning of the semester. Fortunately, this year students were allowed to adjust their study plan. Vus can perform the following operation at most $k$ times: choose a subject $i$ and two different weeks $j_1$ and $j_2$, then swap the assignments of this subject. Thus, in the table, the values $a_{i, j_1}$ and $a_{i, j_2}$ exchange places.

Vus's goal is to make the difficulty of the first week as small as possible. If there are several such ways, he wants to minimize the difficulty of the second week. If there are still several ways, he wants to minimize the difficulty of the third week, and so on.

More formally, let $b_j$ be the difficulty of the $j$-th week:
$$b_j = a_{1, j} + a_{2, j} + \dots + a_{n, j}$$
Kozak Vus wants to apply no more than $k$ operations so that the resulting array of weekly difficulties $B = [b_1, b_2, \dots, b_m]$ becomes lexicographically minimal. Help him find this array.

## 样例

--- Sample 1 ---
Input:
3 3 1
7 1 3
6 8 4
5 2 9
Output:
12 17 16
--- Sample 2 ---
Input:
3 4 2
9 1 7 4
2 8 3 10
5 6 11 12
Output:
8 18 21 31

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
