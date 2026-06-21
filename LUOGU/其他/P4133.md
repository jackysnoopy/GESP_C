# P4133 - Zeckendorf+DP

## 题目描述

参见洛谷原题。

## 解题思路

### 问题分析

本题属于 **数论+DP** 类问题。

### 核心思路

Zeckendorf分解+DP计算方案数。

### 时间复杂度

取决于具体算法实现。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    // Zeckendorf representation + DP
    // Fibonacci numbers
    vector<long long> fib;
    fib.push_back(1);
    fib.push_back(2);
    while (fib.back() < n) fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
    // Greedy Zeckendorf decomposition
    vector<int> zeck;
    long long rem = n;
    for (int i = (int)fib.size() - 1; i >= 0; i--) {
        if (fib[i] <= rem) {
            zeck.push_back(i);
            rem -= fib[i];
        }
    }
    // zeck[0] > zeck[1] > ... 
    // DP: f[i] = number of representations from position i
    int m = zeck.size();
    vector<long long> dp(m + 1);
    dp[m] = 1;
    for (int i = m - 1; i >= 0; i--) {
        if (i == m - 1) {
            dp[i] = 1;
        } else {
            int gap = zeck[i] - zeck[i+1] - 1;
            // Can split this Fibonacci into smaller ones
            // Use DP on the gap
            dp[i] = dp[i+1]; // keep as is
            if (gap > 0) {
                // Number of ways to fill gap
                long long ways = 1;
                for (int j = 0; j < gap; j++) ways *= 2;
                dp[i] = dp[i+1] * (gap + 1); // simplified
            }
        }
    }
    // Actually need proper DP
    // Let's use the standard approach
    // dp[pos][canUsePrev] where pos goes through Fibonacci positions
    vector<long long> used(fib.size(), 0);
    for (int x : zeck) used[x] = 1;
    // Recompute with proper DP
    // f(i, tight) = ways from Fibonacci index i
    int maxIdx = zeck.empty() ? 0 : zeck[0] + 1;
    vector<long long> f(maxIdx + 2, 0);
    f[maxIdx + 1] = 1;
    for (int i = maxIdx; i >= 0; i--) {
        if (used[i]) {
            if (i + 1 <= maxIdx) f[i] = f[i+1] + f[i+2];
            else f[i] = f[i+1];
        } else {
            f[i] = f[i+1];
        }
    }
    cout << f[0] << "\n";
    return 0;
}

```
