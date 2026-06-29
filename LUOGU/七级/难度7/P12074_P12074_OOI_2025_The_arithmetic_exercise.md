# P12074 [OOI 2025] The arithmetic exercise

## 题目描述

You are given an array $a$ of length $n$, where initially all values are zero. You are also given $m$ numbers $x_1,\ x_2,\ \ldots\ x_m$. Then, for each $i$ from $1$ to $m$, you choose some index $j_i$ and make the change $a_{j_i} = x_i - a_{j_i}$.

Help Oleg and Dasha determine what the maximum possible sum of the elements of array $a$ can be after all the changes, if the choices are made optimally.

## 输入格式

第一行包含一个整数 $t$。
每组数据的第一行包含两个整数 $n$ 和 $m$。
第二行包含 $m$ 个整数 $x_1, x_2, \ldots, x_m$。

## 输出格式

对于每组数据，输出一行一个整数，表示数组 $a$ 的最大可能和。

## 样例

### 样例1
输入：
```
2
1 4
1 2 3 4
2 7
10 3 7 1 4 6 3
```
输出：
```
2
18
```

## 提示

- $1 \le t \le 10\,000$；
- $1 \le n, m \le 300\,000$；
- $-10^9 \le x_i \le 10^9$。

## 解题思路

### 问题分析

这是一个贪心问题。每次操作选择一个位置 $j$，执行 $a[j] = x[i] - a[j]$。

### 核心思路

**贪心策略**：每次选择使数组和增加最多的位置。

### 算法流程

```
对于每个x[i]:
    选择使和增加最多的位置j
    执行操作 a[j] = x[i] - a[j]
输出最终和
```

### 复杂度分析

- **时间复杂度**：$O(m \cdot n)$
- **空间复杂度**：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        vector<ll> x(m);
        for (int i = 0; i < m; i++) {
            cin >> x[i];
        }
        
        ll sum = 0;
        vector<ll> a(n, 0);
        
        for (int i = 0; i < m; i++) {
            ll best_j = 0;
            ll best_delta = x[i] - 2 * a[0];
            
            for (int j = 1; j < n; j++) {
                ll delta = x[i] - 2 * a[j];
                if (delta > best_delta) {
                    best_delta = delta;
                    best_j = j;
                }
            }
            
            a[best_j] = x[i] - a[best_j];
        }
        
        ll total = accumulate(a.begin(), a.end(), 0LL);
        cout << total << "\n";
    }
    
    return 0;
}
```
