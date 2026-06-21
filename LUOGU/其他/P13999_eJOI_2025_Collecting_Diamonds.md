# [eJOI 2025] Collecting Diamonds

## 题目描述

A diamond deposit has been discovered in the Rhodope Mountains. For simplicity, we will assume that the deposit has $N$ halls, labeled with integers from $0$ to $N-1$. There are $M$ one-way corridors connecting some of the halls such that there is at least one corridor going out of each hall. Each corridor has a certain number of diamonds that can be mined when passing through it. This number **does not change** when passing through the corridor – it remains the same for subsequent passes.

It is possible that a corridor connects a hall to itself, and there may be multiple corridors between the same pair of halls (possibly in the same direction). It is also not guaranteed that the halls are connected; i.e., there may be a pair of halls $(x, y)$ such that $y$ cannot be reached from $x$.

Petar will pass through $K$ corridors to mine diamonds. He will choose some hall $s$ to begin with, then move to a hall by passing through a corridor starting from $s$, and so on until he has passed through exactly $K$ corridors. Note that he can repeat halls and corridors, and that the number of diamonds he collects from a corridor does not change upon repetition. Notice that there is always going to be a way for him to pass through $K$ corridors consecutively.

Petar will choose $s$ and the path he will follow in the following way: First, he wants to maximize the number of diamonds he will collect from the first corridor he passes through. Among all such options, he will choose the one that maximizes the number of diamonds he will collect from the second corridor. This repeats $K$ times. In other words, Petar wants to choose a lexicographically greatest path. He wonders what the total number of diamonds he will collect is if he chooses such a path. Help him calculate this.

### Implementation details

You should implement the function `calculate_diamonds`:

```cpp
long long int calculate_diamonds(int N, int M, int K, std::vector<int> u, std::vector<int> v, std::vector<int> d)
```

- $N$: the number of halls in the diamond deposit;
- $M$: the number of corridors between the halls;
- $K$: the number of corridors Petar will pass;
- $u$, $v$, $d$: vectors of $M$ integers, representing the starting halls, ending halls, and diamonds for the corridors.

This function will be called once for each test and has to return one number – the total number of diamonds Petar will collect using his strategy.

## 样例

--- Sample 1 ---
Input:
5 6 4
2 0 12
0 4 8
4 1 9
2 3 12
3 1 8
1 4 10
Output:
39
--- Sample 2 ---
Input:
5 5 4
0 1 7
1 0 6
2 3 7
3 4 7
4 2 1
Output:
22

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
