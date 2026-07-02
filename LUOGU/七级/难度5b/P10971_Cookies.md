# Cookies

## 题目描述
圣诞老人共有 $M$ 个饼干，准备全部分给 $N$ 个孩子。

每个孩子有一个贪婪度，第 $i$ 个孩子的贪婪度为 $g_i$。

如果有 $a_i$ 个孩子拿到的饼干数比第 $i$ 个孩子多，那么第 $i$ 个孩子会产生 $g_i\times a_i$ 的怨气。

给定 $N$、$M$ 和序列 $g$，圣诞老人请你帮他安排一种分配方式，使得每个孩子至少分到一块饼干，并且所有孩子的怨气总和最小。

## 输入格式
第一行包含两个整数 $N,M$。

第二行包含 $N$ 个整数表示 $g_1,g_2,\dots,g_n$。

## 输出格式
第一行一个整数表示最小怨气总和。

第二行 $N$ 个空格隔开的整数表示每个孩子分到的饼干数，若有多种方案，输出任意一种均可。

## 样例
**样例输入 1：**
```
3 20
1 2 3
```
**样例输出 1：**
```
2
2 9 9
```

## 提示
数据保证，$1\leq N\leq 30$，$N\leq M\leq 5000$，$1\leq g_i\leq 10^7$。

## 解题思路

### 问题分析
将 M 个饼干分给 N 个孩子，每个孩子至少 1 个，使得总怨气最小。怨气 = 每个孩子的 g_i × (比它多的孩子数)。

### 核心思路
1. 按 g_i 降序排序
2. 用分组 DP：将孩子分成若干组，每组孩子获得相同数量的饼干
3. 组内饼干数递减，前面的组获得更多饼干

### 算法流程
1. 按 g_i 降序排序
2. DP 状态：dp[i][j] = 前 i 个孩子用 j 个饼干的最小怨气
3. 转移：给下一组 k 个孩子分配 c 个饼干
4. 组的怨气贡献 = (组内 g 之和) × (前面孩子数)

### 复杂度分析
- 时间复杂度：$O(N^2 \times M)$
- 空间复杂度：$O(N \times M)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> g(n);
    for (int i = 0; i < n; i++) cin >> g[i];

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) { return g[a] > g[b]; });

    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + g[order[i]];
    }

    const long long INF = 1e18;
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == INF) continue;
            for (int k = 1; k <= n - i; k++) {
                for (int c = 1; j + k * c <= m; c++) {
                    long long anger = (pref[i + k] - pref[i]) * i;
                    dp[i + k][j + k * c] = min(dp[i + k][j + k * c], dp[i][j] + anger);
                }
            }
        }
    }

    cout << dp[n][m] << "\n";

    vector<int> cookies(n, 1);
    int remaining = m - n;
    for (int i = n - 1; i >= 0 && remaining > 0; i--) {
        int add = min(remaining, m - n);
        cookies[i] += add;
        remaining -= add;
    }

    for (int i = 0; i < n; i++) {
        cout << cookies[i] << (i + 1 < n ? " " : "\n");
    }

    return 0;
}
```
