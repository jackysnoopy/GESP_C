# [ICPC 2020 Shanghai R] Traveling in the Grid World

## 题目描述

在 n×m 的网格中，从 (0,0) 走到 (n,m)。每次走直线到另一个格点，但线段上不能经过中间格点（即 gcd(|dx|,|dy|)=1）。连续两次走的方向不能相同（向量叉积≠0）。求最短总距离。

## 输入格式

第一行整数 T。
每组一行两个整数 n, m。

## 输出格式

每组一行，最小总距离，误差不超过 10^{-9}。

## 样例

### 样例 1
输入：
```
2
2 2
2 3
```
输出：
```
3.236067977499790
3.605551275463989
```

## 提示

- 1 ≤ n, m ≤ 10^6
- 所有测试的 max(n,m) 之和 ≤ 10^6

## 解题思路

### 问题分析

需要在网格上找从 (0,0) 到 (n,m) 的最短路径，满足每步 gcd(|dx|,|dy|)=1 且相邻步方向不同。

### 核心思路

类似欧几里得算法的递推。当 gcd(n,m)=1 时可直达，否则需要分解。

利用欧几里得算法结构，将大网格分解为小网格的组合，每步贡献 sqrt(n²+m²) 或 sqrt(2)*m 的距离。

### 算法流程

1. 若 m=0，返回 0
2. 设 q=n/m, r=n%m
3. 若 q≥2：贡献 (q-1)×√2×m，递归处理 (m+r, m)
4. 若 q=1：贡献 √(n²+m²)，递归处理 (m, r)

### 复杂度分析

- 时间复杂度：O(log(max(n,m)))（欧几里得算法步数）
- 空间复杂度：O(1)

## 参考代码

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

double solve(int n, int m) {
    if (n < m) swap(n, m);
    double result = 0;
    while (m > 0) {
        if (n < m) swap(n, m);
        if (m == 0) break;
        int q = n / m;
        int r = n % m;
        if (q >= 2) {
            result += (q - 1) * sqrt(2.0) * m;
            n = m + r;
        } else {
            result += sqrt((double)n * n + (double)m * m);
            n = m;
            m = r;
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    cout.precision(15);
    cout << fixed;
    while (T--) {
        int n, m;
        cin >> n >> m;
        if (n < m) swap(n, m);
        cout << solve(n, m) << "\n";
    }
    return 0;
}
```
