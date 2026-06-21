# [GCJ 2012 Finals] Upstairs/Downstairs

## 题目描述

Konstantin and Ilia live in the same house. Konstantin lives upstairs, and enjoys activities that involve jumping, moving furniture around, and - in general - making noise. Ilia lives downstairs, and enjoys sleep.

In order to have a good evening, Konstantin wants to do at least $K$ activities. Last night, Ilia asked Konstantin to try not to wake him up; and because Konstantin is a very nice neighbor, he agreed. Unfortunately, he took Ilia's request a bit too literally, and he will choose his activities in such a way as to minimize the probability that Ilia is woken up after falling asleep.

Each possible activity for Konstantin has an associated probability $a_i / b_i$. If Konstantin performs this activity, then at the end of it, Ilia will be awake with probability $a_i / b_i$, and asleep otherwise, regardless of whether he was asleep at the start. Moreover, for each possible activity Konstantin can perform it at most $c_i$ times (more than that would be boring, and Konstantin won't have a good evening if he's bored).

Konstantin wants to choose a number of activities to do, in order, so that:

* The total number of activities done is at least $K$.
* The $i$th activity is performed no more than $c_i$ times.
* The probability $Q$ that Ilia is woken up one or more times during the course of the activities is as small as possible.

Ilia starts awake, so in order for him to be woken up, he must be asleep at the end of some activity, and then awake at the end of the next activity.

What is the smallest $Q$ Konstantin can achieve while having a good evening? Note that Konstantin cannot tell whether Ilia is awake or asleep, and so he cannot adapt his activities using that information.

## 样例

--- Sample 1 ---
Input:
3
4 1
1/2 3
1/5 2
2/5 1
2/2 2
3 2
1/2 2
1/3 2
3/4 2
3 3
99/100 1
1/2 2
1/50 3
Output:
Case #1: 0.000000000
Case #2: 0.083333333
Case #3: 0.015000000

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
