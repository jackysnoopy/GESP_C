# [USACO24FEB] Moorbles S

## 题目描述

Bessie and Elsie are playing a game of Moorbles. The game works as follows: Bessie and Elsie each start out with some amount of marbles. Bessie holds out $A$ of her marbles in her hoof and Elsie guesses if $A$ is Even or Odd. If Elsie is correct, she wins the $A$ marbles from Bessie and if she guesses incorrectly, she loses $A$ of her marbles to Bessie (if Elsie has less than $A$ marbles, she loses all her marbles). A player loses when they lose all of their marbles.  

After some amount of turns in the game, Elsie has $N$ $(1 \leq N \leq 10^9)$ marbles. She thinks it is hard to win, but she is playing to not lose. After being around Bessie enough, Elsie has a good read on Bessie's habits and recognizes that on turn $i$, there are only $K$ $(1 \leq K \leq 4)$ different amounts of marbles that Bessie may put out. There are only $M$ $(1 \leq M \leq 3 \cdot 10^5)$ turns before Bessie gets bored and stops playing. Can you identify a lexicographically minimum turn sequence such that Elsie will not lose, regardless of how Bessie plays?

## 输入格式

The first line contains a single integer $T$ ($1 \leq T \leq 10$) representing the number of test cases. Each test case is described as follows: 
-  First, one line containing three integers $N$, $M$, and $K$, representing the number of marbles Elsie has, the number of turns, and the number of potential moves Bessie can make respectively.
- Then, $M$ lines where line $i$ contains $K$ distinct space separated integers $a_{i,1} \; a_{i,2} \ldots a_{i,K}$ ($1 \leq a_{i, j} \leq 10^3$) representing the possible amounts of marbles that Bessie might play on turn $i$.

It is guaranteed that the sum of $M$ over all test cases is at most $3 \cdot 10^5$.

## 输出格式

For each test case, output the lexicographically minimum move sequence for Elsie to guarantee not losing, or $-1$ if she will lose. The move sequence should be on a single line and consist of $M$ space-separated tokens each equal to either "Even" or "Odd".  

Note: "Even" is lexicographically smaller than "Odd".

## 样例

### 样例输入1
```2
10 3 2
2 5
1 3
1 3
10 3 3
2 7 5
8 3 4
2 5 6
```

### 样例输出1
```Even Even Odd
-1
```

### 样例输入2
```1
20 8 2
3 5
3 5
3 5
3 5
3 5
3 5
3 5
3 5
```

### 样例输出2
```Even Even Even Odd Even Odd Even Odd
```

## 提示

##### For Sample 1:
In the first case, the only lexicographically smaller sequence of moves is "Even Even Even", but Bessie can make Elsie lose in that case by first playing $5$, which reduces Elsie's number of marbles from $10$ to $5$, then playing $3$, which reduces Elsie's number of marbles from $5$ to $2$, then playing $3$, which wipes out all of her marbles.  

If Elsie instead plays the correct move sequence "Even Even Odd", then if Bessie plays the same way, at the end when she plays $3$, Elsie will gain those $3$ marbles, increasing her number of marbles to $5$. It can further be shown that Bessie cannot play in a different way to take all of Elsie's marbles given that Elsie plays "Even Even Odd".  

In the second case, it can be shown that for any move sequence that Elsie could choose, Bessie can play in a way to take all of Elsie's marbles.  


#### SCORING:
- Input 3: $M \leq 16$.
- Inputs 4-6: $M \leq 1000$.
- Inputs 7-12: No further constraints.

## 解题思路

### 问题分析

博弈论问题：Elsie 有 N 颗弹珠，M 轮游戏。每轮 Bessie 从 K 个值中选一个，Elsie 猜 Even/Odd。需要找字典序最小的安全策略。

### 核心思路

DP + 贪心：维护 Elsie 可能拥有的弹珠数集合。对每轮，尝试 Even（字典序更小），检查所有可能弹珠数是否安全（> 最大错误损失）。若不安全则选 Odd。

### 算法流程

1. 初始化 dp[0] = {N}（可能的弹珠数集合）
2. 对每轮 i：读入 K 个可能值，计算最大奇数和最大偶数
3. 检查 Even 是否安全：所有可能弹珠数 > max_odd
4. 检查 Odd 是否安全：所有可能弹珠数 > max_even
5. 选择可用的字典序最小选项，更新 dp

### 复杂度分析

- 时间复杂度：O(M·K·THRESH)，THRESH ≈ 4000
- 空间复杂度：O(THRESH)

### 关键技巧

- 用阈值截断：弹珠数超过阈值后视为"安全"
- K ≤ 4 和金额 ≤ 1000 使得阈值方法可行