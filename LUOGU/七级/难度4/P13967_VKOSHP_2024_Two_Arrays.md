# [VKOSHP 2024] Two Arrays

## 题目描述

Let the maximum in the array $d$ be denoted as $\max(d)$ and the minimum as $\min(d)$.

Two arrays $a$ and $b$ of length $n$ are given. In one operation, you can choose an index $1 \leq i \leq n$ and simultaneously increase the elements $a_i$ and $b_i$ by one: $a_i = a_i + 1$, $b_i = b_i + 1$. It is necessary to use these operations to achieve the simultaneous fulfillment of two conditions:

- $\max(a) - \min(a) \leq x$,
- $\max(b) - \min(b) \leq y$.

Determine the minimum number of operations required to achieve the simultaneous fulfillment of the specified conditions, or find out that it is impossible.

## 输入格式

Each test consists of several test cases. The first line contains one integer $t$ --- the number of test cases ($1 \leq t \leq 10^5$). The description of the test cases follows.

The first line of each test case contains three integers: $n$, $x$, $y$ ($1 \leq n \leq 10^5$, $0 \leq x, y \leq 10^9$).

The second line of each test case contains $n$ integers $a_1, a_2, \dots a_n$ --- the elements of array $a$ ($-10^9 \leq a_i \leq 10^9$).

The third line of each test case contains $n$ integers $b_1, b_2, \dots b_n$ --- the elements of array $b$ ($-10^9 \leq b_i \leq 10^9$).

It is guaranteed that the sum of $n$ across all test cases does not exceed $10^5$.

## 输出格式

For each test case, output one integer --- the minimum possible number of operations required to satisfy both conditions. If it is impossible to satisfy both conditions simultaneously, output $-1$.

## 样例

### 样例输入 1
```
5
4 2 3
-1 -2 -3 -4
-1 -2 -3 -4
3 3 2
1 6 4
1 4 1
4 0 3
0 2 1 2
0 2 3 3
5 2 1
-1 0 1 2 3
2 2 2 2 2
3 66 77
235 -111 9
100 -200 -100
```

### 样例输出 1
```
1
3
3
-1
440
```

## 提示

难度：普及+/提高

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, x, y;
        cin >> n >> x >> y;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        int min_a = *min_element(a.begin(), a.end());
        int max_a = *max_element(a.begin(), a.end());
        int min_b = *min_element(b.begin(), b.end());
        int max_b = *max_element(b.begin(), b.end());

        if (max_a - min_a > x || max_b - min_b > y) {
            cout << "-1\n";
            continue;
        }

        int ops = 0;
        for (int i = 0; i < n; i++) {
            int need_a = max(0, a[i] - min_a);
            int need_b = max(0, b[i] - min_b);
            ops = max(ops, max(need_a, need_b));
        }

        cout << ops << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析
给定两个长度为 $n$ 的数组 $a$ 和 $b$，每次操作可以选择一个下标 $i$，同时将 $a_i$ 和 $b_i$ 增加 1。要求同时满足 $\max(a)-\min(a) \leq x$ 和 $\max(b)-\min(b) \leq y$，求最小操作次数，若不可能则输出 $-1$。

### 核心思路
首先检查原始数组是否已经违反约束条件（即 $a$ 的极差超过 $x$ 或 $b$ 的极差超过 $y$），若违反则直接判为不可能。否则，对每个下标 $i$ 分别计算将 $a_i$ 提升到 $\min(a)$ 之上所需的步数 $\text{need}_a$ 和将 $b_i$ 提升到 $\min(b)$ 之上所需的步数 $\text{need}_b$，由于操作同时增加两个数组的元素，因此每个下标所需的操作次数为 $\max(\text{need}_a, \text{need}_b)$。最终答案为所有下标操作次数的最大值。

### 算法流程
1. 读入数组 $a$ 和 $b$
2. 计算 $\min(a)$、$\max(a)$、$\min(b)$、$\max(b)$
3. 若 $\max(a)-\min(a) > x$ 或 $\max(b)-\min(b) > y$，输出 $-1$
4. 否则对每个下标 $i$，计算 $\max(0,\, a_i - \min(a))$ 和 $\max(0,\, b_i - \min(b))$，取两者最大值
5. 所有下标中的最大值即为答案

### 复杂度分析
- 时间复杂度：$O(n)$，每个测试用例仅需线性扫描
- 空间复杂度：$O(n)$，用于存储数组
