# Devu and Flowers

## 题目描述

Devu 想用花来装饰他的花园。他买了 `n` 个盒子，第 `i` 个盒子里有 `f_i` 朵花。每个盒子里的花都是同一种颜色，因此在同一个盒子里的花没有区别。而且不同盒子里的花颜色也不相同。

现在，Devu 想要从这些盒子中恰好选出 `s` 朵花来装饰他的花园。他想知道，有多少种不同的选取方式可以从每个盒子中选花。由于这个数可能非常大，请你输出答案对 `(10^9+7)` 取模的结果。

如果存在至少一个盒子，在两种选法中选择的花的数量不同，Devu 就认为这两种方式是不同的。

## 输入格式

输入的第一行包含两个用空格分隔的整数 `n` 和 `s`（`1 \leq n \leq 20`，`0 \leq s \leq 10^{14}`）。

第二行包含 `n` 个用空格分隔的整数 `f_1, f_2, \dots, f_n`（`0 \leq f_i \leq 10^{12}`）。

## 输出格式

输出一个整数，表示 Devu 可以选择 `s` 朵花的不同方法数，结果对 `(10^9+7)` 取模。

## 样例

### 样例输入
```
2 3
1 3
```

### 样例输出
```
2
```

## 提示

样例 1：有两种选 `3` 朵花的方法：`\{1,2\}` 和 `\{0,3\}`。

样例 2：选 `4` 朵花的方法只有一种：`\{2,2\}`。

样例 3：选 `5` 朵花的方法有三种：`\{1,2,2\}`，`\{0,3,2\}` 和 `\{1,3,1\}`。

由 ChatGPT 5 翻译

## 解题思路

### 问题分析

从 n 种花中选 s 朵，第 i 种最多 fi 朵，求方案数。

### 核心思路

1. 不考虑上限时方案数 = C(s+n-1, n-1)（隔板法）。
2. **容斥原理**：减去超过上限的方案。对每个子集 S，令 S 中每种花多选 fi+1 朵。
3. 答案 = sum((-1)^|S| * C(s-sum(fi+1)+n-1, n-1))。

### 算法流程

1. 读入 n, s 和 fi
2. 枚举所有子集（2^n）
3. 容斥计算
4. 输出答案

### 复杂度分析

时间 O(2^n * n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

long long comb(long long n, long long k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    long long num = 1, den = 1;
    for (long long i = 0; i < k; ++i) {
        num = num * ((n - i) % MOD) % MOD;
        den = den * ((i + 1) % MOD) % MOD;
    }
    return num * power(den, MOD - 2, MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long s;
    cin >> n >> s;
    vector<long long> f(n);
    for (int i = 0; i < n; ++i) cin >> f[i];
    long long ans = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        long long sum = 0;
        int bits = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i)) { sum += f[i] + 1; bits++; }
        if (sum > s) continue;
        long long c = comb(s - sum + n - 1, n - 1);
        if (bits & 1) ans = (ans - c + MOD) % MOD;
        else ans = (ans + c) % MOD;
    }
    cout << ans << '\n';
    return 0;
}
```
