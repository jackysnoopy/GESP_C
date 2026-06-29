# P13286 [GCJ 2013 #1A] Manage your Energy

## 题目描述

You've got a very busy calendar today, full of important stuff to do. You worked hard to prepare and make sure all the activities don't overlap. Now it's morning, and you're worried that despite all of your enthusiasm, you won't have the energy to do all of this with full engagement.

You will have to manage your energy carefully. You start the day full of energy - $E$ joules of energy, to be precise. You know you can't go below zero joules, or you will drop from exhaustion. You can spend any non-negative, integer number of joules on each activity (you can spend zero, if you feel lazy), and after each activity you will regain $R$ joules of energy. No matter how lazy you are, however, you cannot have more than $E$ joules of energy at any time; any extra energy you would regain past that point is wasted.

Now, some things (like solving Code Jam problems) are more important than others. For the $i$th activity, you have a value $v_i$ that expresses how important this activity is to you. The gain you get from each activity is the value of the activity, multiplied by the amount of energy you spent on the activity (in joules). You want to manage your energy so that your total gain will be as large as possible.

Note that you cannot reorder the activities in your calendar. You just have to manage your energy as well as you can with the calendar you have.



## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case is described by two lines. The first contains three integers: $E$, the maximum (and initial) amount of energy, $R$, the amount you regain after each activity, and $N$, the number of activities planned for the day. The second line contains $N$ integers $v_i$, describing the values of the activities you have planned for today.



## 输出格式

For each test case, output one line containing "Case #x: $y$", where $x$ is the case number (starting from 1) and $y$ is the maximum gain you can achieve by managing your energy that day.


## 样例

**输入样例 1**
```
3
5 2 2
2 1
5 2 2
1 2
3 3 4
4 1 3 5
```
**输出样例 1**
```
Case #1: 12
Case #2: 12
Case #3: 39
```

**输入样例 1**
```
3
5 2 2
2 1
5 2 2
1 2
3 3 4
4 1 3 5
```
**输出样例 1**
```
Case #1: 12
Case #2: 12
Case #3: 39
```

**输入样例 1**
```
3
5 2 2
2 1
5 2 2
1 2
3 3 4
4 1 3 5
```
**输出样例 1**
```
Case #1: 12
Case #2: 12
Case #3: 39
```



## 提示

**Sample Explanation**

In the first case, we can spend all 5 joules of our energy on the first activity (for a gain of 10), regain 2 and spend them on the second activity. In the second case, we spend 2 joules on the first activity, regain them, and spend 5 on the second. In the third case, our regain rate is equal to the maximum energy, meaning we always recover all energy after each activity - so we can spend full 3 joules on each activity.

**Limits**

- $1 \leq T \leq 100 .$

**Small dataset (12 Pts, Test set 1 - Visible)**

- $1 \leq E \leq 5 .$
- $1 \leq R \leq 5 .$
- $1 \leq N \leq 10 .$
- $1 \leq v_{i} \leq 10 .$

**Large dataset (23 Pts, Test set 2 - Hidden)**

- $1 \leq E \leq 10^{7} .$
- $1 \leq R \leq 10^{7} .$
- $1 \leq N \leq 10^{4} .$
- $1 \leq v_{i} \leq 10^{7} .$


## 题解

（待补充）

## 解题思路

### 问题分析

初始有 E 焦耳能量，每完成一个活动后恢复 R 焦耳（不超过 E）。有 N 个活动，第 i 个活动价值 v_i，花费 e 焦耳获得 v_i × e 的收益。能量不能低于 0，活动顺序固定。求最大总收益。

### 核心思路

- 贪心策略：对每个活动 i，找到下一个价值严格大于 v_i 的活动 j。
- 若不存在更大的后续活动，则将当前所有能量全部用掉。
- 若存在，则需保留足够能量使得到达活动 j 时能量为 E（满能量），避免浪费恢复量。
- 保留能量 needed = E - dist × R（dist = j - i），若 needed ≤ 0 则说明到达 j 前会自然恢复满，可以全部用掉。

### 算法流程

1. 用单调栈从右向左求每个活动的 next_greater（下一个严格更大值的位置）。
2. 维护当前能量 energy，初始为 E。
3. 对每个活动 i：
   - 若无 next_greater，spend = energy。
   - 否则计算 needed = E - dist × R，spend = max(0, min(energy, energy - needed))。
4. 累加 spend × v_i 到总收益，更新 energy = energy - spend + R（capped at E）。

### 复杂度分析

- 时间复杂度：O(N)，单调栈和遍历各 O(N)。
- 空间复杂度：O(N)，存储 next_greater 数组。
