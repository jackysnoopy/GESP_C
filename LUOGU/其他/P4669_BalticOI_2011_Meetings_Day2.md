# [BalticOI 2011] Meetings (Day2)

## 题目描述

The Society for Saving the World has called their $N$ members to an emergency congress to finally agree on a plan for saving the world. To reach a common decision in any meeting at the congress, the meeting participants proceed as follows:

1.    Each of them has a proposal and takes $P$ minutes to present it to the others.

2.    After all participants have made their presentations, they vote for the best proposal, which takes $V$ minutes.

For example, if each proposal takes one minute $(P = 1)$ and voting also takes one minute $(V = 1)$, a meeting with $100$ participants would reach a decision in $101$ minutes. To speed up the overall decision-making process, the participants of the congress have decided to split into groups and work in parallel. Each group selects the best proposal among themselves using the procedure described above. Then the representatives of the groups meet and pick the final plan among the proposals voted best in each group. For example, if the $100$ participants would split into two groups of $40$ and $60$, respectively, the process could work as follows (again, $P = V = 1$):

-    the larger group takes $61$ minutes to select their best proposal;
-    the smaller group takes $41$ minutes to do the same and then has to wait for the larger group to finish;
-    then the two representatives of the groups meet and spend $2$ minutes presenting to each other and $1$ minute to vote.

The total time spent is thus $61 + 2 + 1 = 64$ minutes. But the groups might further divide themselves into subgroups and sometimes it could be useful to split into more than two groups. As a special case, a subgroup of $1$ member can decide in no time, as there is no need to present one’s own proposal to oneself. Write a program that, given presentation and voting times $P$ and $V$ , computes the minimal time needed for the $N$ participants of the congress to reach a common decision, assuming they organize their meetings and groups optimally.

## 样例

--- Sample 1 ---
Input:
9 1 1
Output:
8
--- Sample 2 ---
Input:
6 1 2
Output:
8
--- Sample 3 ---
Input:
6 2 1
Output:
12

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
