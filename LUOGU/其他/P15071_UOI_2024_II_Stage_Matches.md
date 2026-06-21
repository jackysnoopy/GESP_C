# [UOI 2024 II Stage] Matches

## 题目描述

Anton has invented a new team sport called waterball (similar to paintball, but with water). He wants to share his invention with his $n$ friends. Anton has good relationships with all his friends, but it's not guaranteed that his friends have the same relationships with each other. Specifically, we know that friend number $a_i$ conflicts with friend $b_i$.

Anton was given a list of $m$ conflicting pairs ($a_i;b_i$). Now, it seems like it would be possible to divide the players into two teams, but it's not that simple for Anton...

He wants to divide these $m$ conflicting pairs into segments in such a way that:

- each conflicting pair belongs to exactly one segment;
- considering only the relationships within each segment, it should be possible to divide all the people into two teams in such a way that there are no two conflicting people in the same team.

For example, let's say we have an array of conflicting pairs $[(1, 2), (2, 3), (1, 3)]$. We can take the first two pairs in the first segment. In this case, we can form the teams: $[1, 3]$ and $[2]$. In the second segment, we can take the last pair. $1$ and $3$ must be in different teams, and $2$ can be in either team. Alternatively, we can assign the first pair to the first segment, and the last two to the second segment. Note that we cannot assign the first and third pairs to the same segment, and the second pair to another. This is because a segment should only contain consecutive pairs. We also cannot assign all pairs to the same segment, as there would always be a team where people conflict.

Anton has made the statement complicated again, and now he can't solve the problem. Help him by telling him the minimum number of segments into which he can divide the pairs to satisfy the above conditions.

## 样例

--- Sample 1 ---
Input:
3 3
1 2
2 3
1 3
Output:
2
--- Sample 2 ---
Input:
5 10
2 4
1 2
3 4
1 3
1 5
4 5
2 3
3 5
1 4
2 5
Output:
3

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
