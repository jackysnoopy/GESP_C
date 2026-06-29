# P13219 [GCJ 2015 #1B] Noisy Neighbors

## 题目描述

You are a landlord who owns a building that is an $R \times C$ grid of apartments; each apartment is a unit square cell with four walls. You want to rent out $N$ of these apartments to tenants, with exactly one tenant per apartment, and leave the others empty. Unfortunately, all of your potential tenants are noisy, so whenever any two occupied apartments share a wall (and not just a corner), this will add one point of unhappiness to the building. For example, a $2 \times 2$ building in which every apartment is occupied has four walls that are shared by neighboring tenants, and so the building's unhappiness score is $4$.

If you place your $N$ tenants optimally, what is the minimum unhappiness value for your building?



## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow; each contains three space-separated integers: $R$, $C$, and $N$.



## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from $1$) and $y$ is the minimum possible unhappiness for the building.


## 样例

**输入样例 1**
```
4
2 3 6
4 1 2
3 3 8
5 2 0
```
**输出样例 1**
```
Case #1: 7
Case #2: 0
Case #3: 8
Case #4: 0
```

**输入样例 1**
```
4
2 3 6
4 1 2
3 3 8
5 2 0
```
**输出样例 1**
```
Case #1: 7
Case #2: 0
Case #3: 8
Case #4: 0
```

**输入样例 1**
```
4
2 3 6
4 1 2
3 3 8
5 2 0
```
**输出样例 1**
```
Case #1: 7
Case #2: 0
Case #3: 8
Case #4: 0
```



## 提示

**Sample Explanation**

In Case #1, every room is occupied by a tenant and all seven internal walls have tenants on either side.

In Case #2, there are various ways to place the two tenants so that they do not share a wall. One is illustrated below.

In Case #3, the optimal strategy is to place the eight tenants in a ring, leaving the middle apartment unoccupied.

Here are illustrations of sample cases 1-3. Each red wall adds a point of unhappiness.

![](https://cdn.luogu.com.cn/upload/image_hosting/sivst9rm.png)

**Sample Explanation**

- $1 \leq T \leq 1000$.
- $0 \leq N \leq R \times C$.

**Small dataset(12 Pts)**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq R \times C \leq 16$.

**Large dataset(15 Pts)**

- Time limit: ~~480~~ 10 seconds.
- $1 \leq R \times C \leq 10000$.


## 题解

（待补充）

## 解题思路

### 问题分析

R×C 网格中放置 N 个租户，相邻（共享边）租户产生 1 点不幸福感。求最小不幸福感。

### 核心思路

- 两种策略取较优者：
  - 策略一（棋盘填充）：先填棋盘色1的格子（最多 ⌈R×C/2⌉ 个），若 N 未满则填色2的格子。对色2格子按邻居数（2/3/4）排序，优先填邻居少的。
  - 策略二（满填后删除）：假设全部填满，不幸福感 = 内部墙壁数。然后贪心删除 (R×C - N) 个格子，优先删除度数高的（内部4、边缘3、角落2）。
- 答案为两种策略的较小值。

### 算法流程

1. 计算总格子数 total = R×C，内部墙壁数 = (R-1)×C + R×(C-1)。
2. 策略一：先占满色1格子，剩余 N 按邻居数从小到大填充色2格子，累加不幸福感。
3. 策略二：全部填满后，按度数从大到小排序所有格子，贪心删除 (total-N) 个格子。
4. 输出 min(ans1, ans2)。

### 复杂度分析

- 时间复杂度：O(R×C)，遍历所有格子。
- 空间复杂度：O(R×C)，存储格子度数。
