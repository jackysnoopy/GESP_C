# [GKS 2015 #D] Virtual Rabbit

## 题目描述

Alice just bought a virtual pet rabbit. The rabbit hops around on a screen and can be "fed" by pressing a button. Alice is fond of the rabbit, but she is also busy, and doesn't want to spend too much time taking care of it. However, if the rabbit goes without "food" for too long, it "dies" and Alice loses the game.

Every day, Alice gets up at time $G$, goes to work at time $W$, returns home at time $H$, and goes to bed at time $B$. Alice cannot feed the rabbit while she is at work or asleep -- that is, in the intervals $[W, H)$ and $[B, G)$. Note that times $W$ and $B$ themselves are not valid feeding times, whereas times $H$ and $G$ are. In any other second, Alice can either push a button to instantly feed the rabbit, or not push the button. Between every two seconds, the rabbit determines the number of consecutive seconds in which it has not been fed, and "dies" if that duration is equal to $X$.

It is currently 00:00:00 on Day 0, and the rabbit has just been delivered to Alice's house by the mail service. (The mail carrier pushes the button at 00:00:00, even if Alice is asleep, and then leaves.) Alice wants to make sure the rabbit is still "alive" at 00:00:00 on day $D$. What is the minimal number of times that she needs to feed the rabbit, if she can keep the rabbit "alive" at all?

## 样例

--- Sample 1 ---
Input:
3
08:00:00
09:00:00
18:00:00
22:00:00
12:00:00
100
08:00:00
09:00:00
18:00:00
22:00:00
01:00:00
1
00:00:00
12:00:00
12:00:01
23:59:59
00:00:02
2
Output:
Case #1: 200
Case #2: -1
Case #3: 86401

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
