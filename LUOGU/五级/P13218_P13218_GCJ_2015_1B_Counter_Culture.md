# P13218 [GCJ 2015 #1B] Counter Culture

## 题目描述

In the Counting Poetry Slam, a performer takes the microphone, chooses a number $N$, and counts aloud from $1$ to $N$. That is, she starts by saying $1$, and then repeatedly says the number that is $1$ greater than the previous number she said, stopping after she has said $N$.

It's your turn to perform, but you find this process tedious, and you want to add a twist to speed it up: sometimes, instead of adding $1$ to the previous number, you might reverse the digits of the number (removing any leading zeroes that this creates). For example, after saying "16", you could next say either "17" or "61"; after saying "2300", you could next say either "2301" or "32". You may reverse as many times as you want (or not at all) within a performance.

The first number you say must be $1$; what is the fewest number of numbers you will need to say in order to reach the number $N$? $1$ and $N$ count toward this total. If you say the same number multiple times, each of those times counts separately.


## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow. Each has one integer $N$, the number you must reach.



## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from $1$) and $y$ is the minimum number of numbers you need to say.


## 样例

**输入样例 1**
```
3
1
19
23
```
**输出样例 1**
```
Case #1: 1
Case #2: 19
Case #3: 15
```

**输入样例 1**
```
3
1
19
23
```
**输出样例 1**
```
Case #1: 1
Case #2: 19
Case #3: 15
```

**输入样例 1**
```
3
1
19
23
```
**输出样例 1**
```
Case #1: 1
Case #2: 19
Case #3: 15
```



## 提示

**Sample Explanation**

In Case #2, flipping does not help and the optimal strategy is to just count up to $19$.

In Case #3, the optimal strategy is to count up to $12$, flip to $21$, and then continue counting up to $23$. That is, the numbers you will say are $1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 21, 22, 23$.

**Limits**

- $1 \leq T \leq 100$.

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq N \leq 10^6$.

**Large dataset**

- Time limit: ~~480~~ 10 seconds.
- $1 \leq N \leq 10^{14}$.


## 题解

（待补充）

## 解题思路

### 问题分析

从数字 1 开始，每次可 +1 或反转数字（去除前导零），求到达 N 的最少步数。

### 核心思路

- 对小规模 N（≤10000）使用 BFS 求精确解。每次从当前数 x 可转移到 x+1 或 rev(x)，所有边权为 1。
- 对大规模 N，核心观察：翻转操作在"到达某个中间值后反转能跳到更大值"时有用。最优策略是将 N 拆分为高位 a 和低位 b，先通过翻转策略快速到达 a×10^l 附近的数，再线性 +1 到达 N。
- 递归/贪心方法：将 N 按位数分段，利用翻转加速跨越高位区间。

### 算法流程

1. 若 N ≤ 10000，BFS 求解：从 1 出发，每次松弛 +1 和 rev(x) 两种转移。
2. 对大规模 N，按位数分段处理：
   - 计算高位 a 和低位 b。
   - 递归求解到 a×10^l 的最小步数。
   - 加上 b 步到达 N。
3. 输出最小步数。

### 复杂度分析

- BFS 方案：时间 O(N)，空间 O(N)，适用于小规模。
- 递归方案：时间 O(log N)，空间 O(log N)，适用于大规模。
