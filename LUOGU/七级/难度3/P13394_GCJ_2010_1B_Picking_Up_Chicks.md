# [GCJ 2010 #1B] Picking Up Chicks

## 题目描述

A flock of chickens are running east along a straight, narrow road. Each one is running with its own constant speed. Whenever a chick catches up to the one in front of it, it has to slow down and follow at the speed of the other chick. You are in a mobile crane behind the flock, chasing the chicks towards the barn at the end of the road. The arm of the crane allows you to pick up any chick momentarily, let the chick behind it pass underneath and place the picked up chick back down. This operation takes no time and can only be performed on a pair of chicks that are immediately next to each other, even if 3 or more chicks are in a row, one after the other.

Given the initial locations ($X_i$) at time 0 and natural speeds ($V_i$) of the chicks, as well as the location of the barn ($B$), what is the minimum number of swaps you need to perform with your crane in order to have at least $K$ of the $N$ chicks arrive at the barn no later than time $T$?

You may think of the chicks as points moving along a line. Even if 3 or more chicks are at the same location, next to each other, picking up one of them will only let one of the other two pass through. Any swap is instantaneous, which means that you may perform multiple swaps at the same time, but each one will count as a separate swap.

## 输入格式

The first line of the input gives the number of test cases, $C$. $C$ test cases follow. Each test case starts with 4 integers on a line -- $N$, $K$, $B$ and $T$. The next line contains the $N$ different integers $X_i$, in increasing order. The line after that contains the $N$ integers $V_i$. All distances are in meters; all speeds are in meters per second; all times are in seconds.

## 输出格式

For each test case, output one line containing "Case #$x$: $S$", where $x$ is the case number (starting from 1) and $S$ is the smallest number of required swaps, or the word "IMPOSSIBLE".

## 样例

### 样例输入 1
```
3
5 3 10 5
0 2 5 6 7
1 1 1 1 4
5 3 10 5
0 2 3 5 7
2 1 1 1 4
5 3 10 5
0 2 3 4 7
2 1 1 1 4
```

### 样例输出 1
```
Case #1: 0
Case #2: 2
Case #3: IMPOSSIBLE
```

## 提示

**Limits**

- $1 \leqslant C \leqslant 100;$
- $1 \leqslant B \leqslant 1,000,000,000;$
- $1 \leqslant T \leqslant 1,000;$
- $0 \leqslant X_i < B;$
- $1 \leqslant V_i \leqslant 100;$
- All the $X_i$'s will be distinct and in increasing order.

**Small dataset (13 Pts, Test set 1 - Visible)**

- $1 \leqslant N \leqslant 10;$
- $0 \leqslant K \leqslant \min(3, N);$

**Large dataset (17 Pts, Test set 2 - Hidden)**

- $1 \leqslant N \leqslant 50;$
- $0 \leqslant K \leqslant N;$

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int C;
    cin >> C;
    for (int tc = 1; tc <= C; tc++) {
        int N, K, B, T;
        cin >> N >> K >> B >> T;
        vector<int> X(N), V(N);
        for (int i = 0; i < N; i++) cin >> X[i];
        for (int i = 0; i < N; i++) cin >> V[i];
        int slow = 0, swaps = 0, got = 0;
        bool impossible = false;
        for (int i = N - 1; i >= 0; i--) {
            bool canReach = (X[i] + (long long)V[i] * T >= B);
            if (canReach) {
                swaps += slow;
                got++;
                if (got >= K) break;
            } else {
                slow++;
            }
        }
        cout << "Case #" << tc << ": ";
        if (got >= K) cout << swaps << "\n";
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}
```

## 解题思路

### 问题分析

题目要求在 $N$ 只小鸡中，通过交换相邻小鸡的位置（使用起重机），使至少 $K$ 只小鸡在时间 $T$ 内到达谷仓（距离 $B$）。每只小鸡有初始位置 $X_i$ 和自然速度 $V_i$，但会被前面较慢的小鸡挡住。需要求最小交换次数。

### 核心思路

参考代码采用了从后往前贪心的策略。核心观察是：只有能自行到达谷仓的小鸡才值得考虑（即满足 $X_i + V_i \times T \ge B$）。从最后一只小鸡开始向前扫描，统计不能到达的小鸡数量（`slow`），当遇到能到达的小鸡时，它需要越过所有在它前面的慢小鸡，因此交换次数累加 `slow`。这种方法确保我们优先选择最容易到达的小鸡，同时最小化所需交换次数。

### 算法流程

1. 读入测试用例数量 $C$
2. 对每组测试用例，读入 $N, K, B, T$ 以及位置数组 $X$ 和速度数组 $V$
3. 从最后一只小鸡开始向前遍历：
   - 判断该小鸡是否能在时间 $T$ 内到达谷仓：$X_i + V_i \times T \ge B$
   - 如果能到达：交换次数累加当前慢小鸡数量 `slow`，已获得数量 `got` 加 1
   - 如果不能到达：慢小鸡数量 `slow` 加 1
4. 如果 `got >= K`，输出交换次数；否则输出 `IMPOSSIBLE`

### 复杂度分析

- **时间复杂度**：$O(N)$，每组测试用例只需一次线性扫描
- **空间复杂度**：$O(N)$，用于存储位置和速度数组
