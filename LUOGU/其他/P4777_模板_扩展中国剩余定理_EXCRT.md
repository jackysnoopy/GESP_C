# 【模板】扩展中国剩余定理（EXCRT）

## 题目描述

给定 `n` 组非负整数 `a_i, b_i` ，求解关于 `x` 的方程组的最小非负整数解。
$`\begin{cases}x\equiv b_1\pmod{a_1}\\x\equiv b_2\pmod{a_2}\\\dots\\x\equiv b_n\pmod{a_n}\end{cases}`$

## 输入格式

输入第一行包含整数 `n`。

接下来 `n` 行，每行两个非负整数 `a_i, b_i`。

## 输出格式

输出一行，为满足条件的最小非负整数 `x`。

## 样例

### 样例输入
```
3
11 6
25 9
33 17
```

### 样例输出
```
809
```

## 提示

对于 `100 \%` 的数据，`1 \le n \le {10}^5`，`1 \le a_i \le {10}^{12}`，`0\leq b_i \leq 10^{12}`，保证所有 `a_i` 的最小公倍数不超过 `{10}^{18}`。

**请注意程序运行过程中进行乘法运算时结果可能有溢出的风险。**

数据保证有解。

## 解题思路

### 问题分析

求解同余方程组 x ≡ bi (mod ai)，模数不一定互质，用 EXCRT。

### 核心思路

1. **扩展中国剩余定理（EXCRT）**：依次合并两个同余方程。
2. 已知 x ≡ r1 (mod m1) 和 x ≡ r2 (mod m2)，设 x = r1 + m1 * t。
3. 代入得 m1*t ≡ r2-r1 (mod m2)，用 exgcd 求解 t。
4. 合并为 x ≡ r1 + m1*t (mod lcm(m1,m2))。

### 算法流程

1. 读入 n 组 (ai, bi)
2. 依次合并同余方程
3. 输出最小非负整数解

### 复杂度分析

时间 O(n * log(max(a_i)))

## 参考代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long r = 0, m = 1;
    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        long long x, y;
        long long g = exgcd(m, a, x, y);
        if ((b - r) % g != 0) { cout << -1 << '\n'; return 0; }
        long long t = (b - r) / g * (x % (a / g));
        r += m * t;
        m = m / g * a;
        r = (r % m + m) % m;
    }
    cout << r << '\n';
    return 0;
}
```
