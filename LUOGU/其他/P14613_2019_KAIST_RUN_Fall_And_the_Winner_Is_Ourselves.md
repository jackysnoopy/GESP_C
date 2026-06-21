# [2019 KAIST RUN Fall] And the Winner Is... Ourselves!

## 题目描述

Let us remind you about how the total penalties are calculated for this contest:

- When you solve a problem at $T$ minutes, $T+20V$ is added to your penalty, where $V$ is the number of incorrect verdicts (except compile errors) received on that problem.
- If you do not solve a problem before the contest ends, the incorrect verdicts on that problem are not counted as penalties.

Here is a bad news for all of you: we, the problem setters, are planning to join the competition and solve our own problems!

We know our problems really well, so we can solve all the problems before the contest ends. Furthermore, we can precisely predict how long it takes to solve each problem, and how many incorrect verdicts (except compile errors) we get in each problem. Depending on the order of the problems we solve, our total penalty might differ. What is the minimum penalty if we solve all problems?

## 输入格式

11 lines are given as the input. The $i$-th line contains two integers, $D_i$ and $V_i$, where $D_i$ is the amount of minutes required to solve the $i$-th problem, and $V_i$ is the number of incorrect verdicts on the $i$-th problem.

For each $i$, $1 \leq D_i$ and $0 \leq V_i \leq 1000$. Also, $\sum_{i=1}^{11} D_i \leq 300$.

## 输出格式

Output the minimum penalty if we solve all problems.

## 样例

### 样例输入1
```20 1
20 0
20 3
10 0
10 0
10 0
30 0
30 0
30 0
20 0
20 10
```

### 样例输出1
```1360
```

## 提示

The sample input does not necessarily reflect the actual difficulties of the problems.

The problem statement does not necessarily reflect the actual situation of the contest.

## 解题思路

### 问题分析

卡牌游戏最大化收益。

### 核心思路

贪心选择最高价值卡牌。

### 算法流程

1. 排序降序
2. 选奇数位置的牌

### 复杂度分析

O(n log n)时间，O(n)空间。
