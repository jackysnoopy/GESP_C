# [SDOI2012] Longge 的问题

## 题目描述

现在问题来了：给定一个整数 $n$，你需要求出 $\sum\limits_{i=1}^n \gcd(i, n)$，其中 $\gcd(i, n)$ 表示 $i$ 和 $n$ 的最大公因数。

## 输入格式

输入只有一行一个整数，表示 $n$。

## 输出格式

输出一行一个整数表示答案。

## 样例

### 样例输入
```
6
```

### 样例输出
```
15
```

## 提示

#### 数据规模与约定

- 对于 $60\% $ 的数据，保证 $n\leq 2^{16}$。
- 对于 $100\% $ 的数据，保证 $1\leq n< 2^{32}$。

## 解题思路

### 问题分析

求 sum(gcd(i,n), i=1..n)。

### 核心思路

1. 令 g(d) = gcd(i,n)=d 的 i 的个数，则 g(d) = phi(n/d)（对 d|n）。
2. 答案 = sum(d * phi(n/d), d|n)。
3. 分解 n 的质因数，枚举所有因数，计算 phi。

### 算法流程

1. 读入 n
2. 分解质因数
3. 枚举所有因数 d，累加 d*phi(n/d)
4. 输出答案

### 复杂度分析

时间 O(sqrt(n))

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
long long phi(long long n) {
    long long res = n;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            res = res / p * (p - 1);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long n; cin >> n;
    long long ans = 0;
    for (long long d = 1; d * d <= n; ++d) {
        if (n % d == 0) {
            ans += d * phi(n / d);
            if (d != n / d) ans += (n / d) * phi(d);
        }
    }
    cout << ans << '\n';
    return 0;
}
```
