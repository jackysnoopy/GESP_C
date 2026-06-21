# [ICPC-Hefei 2008 Online] The Luckiest Number

## 题目描述

中国人认为“8”是幸运数字。Bob 也喜欢数字“8”。此外，Bob 有自己的幸运数字 `L`。现在，他想构造出自己的最幸运的数字，即所有仅由数字“8”组成且是 `L` 的倍数的正整数中的最小值。

## 输入格式

多个测试用例组成（不超过 `10` 组）。每个测试用例包含一行，其中包含 `L`（`1 ≤ L ≤ 2,000,000,000`）。

最后一个测试用例后跟着一行，其中包含零。

## 输出格式

对于每个测试用例，输出一行，包含测试用例编号（从 `1` 开始），后跟一个整数，该整数是 Bob 最幸运的数字的长度。如果 Bob 无法构造他最幸运的数字，则输出零。

翻译来自于：[ChatGPT](https://chatgpt.com/)

## 样例

### 样例输入
```
8
11
16
0
```

### 样例输出
```
Case 1: 1
Case 2: 2
Case 3: 0
```

## 提示



## 解题思路

### 问题分析

找最小的全8数是 L 的倍数。全8数 = 8*(10^k-1)/9，即找最小 k 使 10^k ≡ 1 (mod 9*L/gcd(8,L))。

### 核心思路

1. 设答案为 (10^k-1)/9 * 8，需要 (10^k-1)/9 * 8 ≡ 0 (mod L)。
2. 令 g = gcd(8, L)，条件变为 10^k ≡ 1 (mod 9*L/g)。
3. 注意 10 和模数必须互质，否则无解。
4. 求 10 模 m 的阶（最小正整数 k 使 10^k ≡ 1 mod m），枚举 phi(m) 的因数。

### 算法流程

1. 读入 L（多组，0 结束）
2. 计算 m = 9*L/gcd(8,L)
3. 检查 gcd(10,m)==1，否则无解
4. 求 10 模 m 的阶
5. 输出答案

### 复杂度分析

时间 O(sqrt(phi(m)) * log(m))

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long L;
    int cs = 0;
    while (cin >> L && L) {
        long long g = gcd(8LL, L);
        long long m = 9LL * L / g;
        if (gcd(10LL, m) != 1) {
            cout << "Case " << ++cs << ": 0" << endl;
            continue;
        }
        long long phi = m, tmp = m;
        for (long long p = 2; p * p <= tmp; ++p) {
            if (tmp % p == 0) {
                phi = phi / p * (p - 1);
                while (tmp % p == 0) tmp /= p;
            }
        }
        if (tmp > 1) phi = phi / tmp * (tmp - 1);
        long long ans = phi;
        vector<long long> divs;
        for (long long d = 1; d * d <= phi; ++d) {
            if (phi % d == 0) {
                divs.push_back(d);
                if (d * d != phi) divs.push_back(phi / d);
            }
        }
        sort(divs.begin(), divs.end());
        for (long long d : divs) {
            if (power(10, d, m) == 1) { ans = d; break; }
        }
        cout << "Case " << ++cs << ": " << ans << endl;
    }
    return 0;
}
```
