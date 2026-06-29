# [SWERC 2025] Adjusting Drones

## 题目描述

You are managing a fleet of $n$ drones, each with an energy level $a_1, \dots, a_n$. You are also given a positive integer $k$, which represents the maximum number of drones allowed to share the same energy level.

To prevent overloads, the drones automatically perform energy balancing operations as follows. While there exists an energy level that appears strictly more than $k$ times, they execute the following steps:

- first, every drone $i$ whose energy $a_i$ has already appeared before (that is, there exists $j < i$ with $a_j = a_i$) is marked;
- then, for each marked drone, its energy is increased by 1 unit;
- then, the marks are removed.

The process stops once no energy level appears more than $k$ times. Determine how many energy balancing operations will be performed.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains two integers $n, k$ ($1 \le k \le n \le 2 \cdot 10^5$) — the number of drones and the maximum allowed number of drones with the same energy level.

The second line of each test case contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 2n$) — the initial energy levels of the drones.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

## 输出格式

For each test case, output a single line containing an integer: the number of energy balancing operations performed.

## 样例

### 样例输入 1
```
5
6 3
1 1 1 1 1 1
5 1
1 3 2 1 4
16 2
6 3 7 5 13 6 7 6 3 5 13 7 6 4 3 6
16 3
6 3 7 5 13 6 7 6 3 5 13 7 6 4 3 6
16 4
6 3 7 5 13 6 7 6 3 5 13 7 6 4 3 6
```

### 样例输出 1
```
3
4
14
5
4
```

## 提示

### Explanation of sample 1.

In the first test case, the drones’ energy levels evolve as follows:

- at the beginning, $[1, 1, 1, 1, 1, 1]$;
- after 1 operation, $[1, 2, 2, 2, 2, 2]$;
- after 2 operations, $[1, 2, 3, 3, 3, 3]$;
- after 3 operations, $[1, 2, 3, 4, 4, 4]$.

After 3 operations, every energy level appears at most 3 times, so the process stops.

In the second test case, the energy levels change as follows: $[1, 3, 2, 1, 4] \to [1, 3, 2, 2, 4] \to [1, 3, 2, 3, 4] \to [1, 3, 2, 4, 4] \to [1, 3, 2, 4, 5]$. The process stops after 4 operations.

## 解题思路

### 问题分析
给定 n 个无人机的能量值，当某个能量值出现超过 k 次时，将所有已出现过的该能量值的无人机能量+1。求总操作次数。

### 核心思路
贪心模拟：按顺序处理每个无人机的能量值，用计数数组记录每个能量值出现的次数。当某个能量值的计数超过 k 时，将其计数-1，能量+1 的计数+1，操作次数+1。由于能量只会增加，不会回退，模拟过程自然终止。

### 算法流程
1. 初始化计数数组 count，操作次数 ops = 0
2. 对每个无人机的能量 a[i]：
   - count[a[i]]++
   - 若 count[a[i]] > k：ops++，count[a[i]]--，count[a[i]+1]++
3. 输出 ops

### 复杂度分析
- 时间复杂度：O(N)，每个元素处理一次
- 空间复杂度：O(N)，计数数组大小

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> count(2 * n + 1, 0);
    int ops = 0;

    for (int i = 0; i < n; i++) {
        count[a[i]]++;
        if (count[a[i]] > k) {
            ops++;
            count[a[i]]--;
            count[a[i] + 1]++;
        }
    }

    cout << ops << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
有n个无人机，每个有能量值。当某个能量值出现超过k次时，需要进行平衡操作：将重复的无人机能量+1。求总共需要多少次操作。

### 核心思路
逐个处理无人机，维护每个能量值的计数。每当加入一个无人机导致该能量值超过k时，将其能量+1并记录一次操作。由于能量值可能级联增加，但总数有限，可以使用数组记录。

### 算法流程
1. 初始化计数数组（大小2n+1以处理能量值溢出）
2. 遍历每个无人机的能量值
3. 若该能量值计数超过k，执行操作：计数-1，下一能量值计数+1，操作次数+1
4. 输出总操作次数

### 复杂度分析
- 时间复杂度：O(n)
- 空间复杂度：O(n)
