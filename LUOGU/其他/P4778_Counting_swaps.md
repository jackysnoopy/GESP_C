# Counting swaps

## 题目描述

给定一个排列 `p_1, \ldots, p_n`，它是数字 `1` 到 `n` 的一个排列。在每一步中，你可以选择两个数字 `x < y` 并交换 `p_x` 和 `p_y`。

设 `m` 为将给定排列排序所需的最小交换次数。计算恰好用 `m` 次交换来排序给定排列的不同序列的数量。由于这个数量可能很大，计算它对 `10^9 + 9` 取模的结果。

## 输入格式

输入文件的第一行包含一个整数 `t`，表示测试用例的数量。每个测试用例前有一个空行。

每个测试用例由两行组成。第一行包含整数 `n`。第二行包含序列 `p_1, \ldots, p_n`：这是 `1, \ldots, n` 的一个排列。

在简单子问题 C1 中，`1 \leq n \leq 10`。

在困难子问题 C2 中，`1 \leq n \leq 10^5`。

## 输出格式

对于每个测试用例，输出一行，包含一个整数：`x \bmod 10^9 + 9`，其中 `x` 是用尽可能少的交换次数来排序给定序列的方法数。

## 样例

### 样例输入
```
3

3
2 3 1

4
2 1 4 3

2
1 2
```

### 样例输出
```
3
2
1
```

## 提示

在第一个测试用例中，我们可以通过两次交换来排序排列。我们可以任意进行第一次交换；对于每种情况，恰好有一种最佳的第二次交换。例如，三个最短解之一是“交换 `p_1` 和 `p_2`，然后交换 `p_1` 和 `p_3`”。

在第二个测试用例中，最佳解涉及交换 `p_1` 和 `p_2`，以及交换 `p_3` 和 `p_4`。我们可以以任意顺序进行这两次交换。

第三个序列已经排序。最佳交换次数为 `0`，因此唯一的最佳解是空的交换序列。

题目来源：[IPSC2016](https://ipsc.ksp.sk/2016/real/problems/c.html)

题面翻译由 ChatGPT-4o 提供。

## 解题思路

### 问题分析

求恰好用最少交换次数排序排列的不同方案数。

### 核心思路

1. 最少交换次数 = n - 置换环个数。
2. 每个长度为 k 的环需要 k-1 次交换，方案数为 k!（环内所有交换序列）。
3. 不同环之间的交换顺序也需考虑。
4. 答案 = 各环方案数之积，取模。

### 算法流程

1. 读入排列
2. 分解为置换环
3. 对每个环计算方案数
4. 求积并取模

### 复杂度分析

时间 O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000009;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> p(n + 1);
        for (int i = 1; i <= n; ++i) cin >> p[i];
        vector<bool> vis(n + 1, false);
        vector<int> cycles;
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) continue;
            int cnt = 0, cur = i;
            while (!vis[cur]) { vis[cur] = true; cur = p[cur]; cnt++; }
            if (cnt > 1) cycles.push_back(cnt);
        }
        long long ans = 1;
        vector<long long> fact(n + 1, 1);
        for (int i = 2; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
        for (int c : cycles) ans = ans * fact[c] % MOD;
        cout << ans << '\n';
    }
    return 0;
}
```
