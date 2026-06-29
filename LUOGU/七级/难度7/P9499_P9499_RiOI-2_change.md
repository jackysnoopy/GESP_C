# P9499 「RiOI-2」change

## 题目描述

给定 $n$ 种物品，每种物品 $i$ 价值为 $v_i$，个数为 $c_i$。

定义总价值为 $\sum\limits_{i=1}^nc_iv_i$，你可以进行一些操作来最大化总价值。

一次操作为：选定一个 $i$ 满足 $c_i \geq x_i$，让 $c_i\gets c_i - x_i$，$c_{i+1}\gets c_{i+1}+ 1$。

输出最大的总价值对 $998,\!244,\!353$ 取模。

## 输入格式

第一行一个正整数 $\text{sid}$。
第二行一个正整数 $t$，表示数据组数。
对于每组数据：
- 第一行，一个正整数 $n$。
- 第二行，$n$ 个非负整数分别表示 $v_1, v_2 \dots v_n$。
- 第三行，$n$ 个非负整数分别表示 $c_1, c_2 \dots c_n$。
- 第四行，$n$ 个非负整数分别表示 $x_1, x_2 \dots x_n$。

## 输出格式

对于每组数据，输出一行一个整数。

## 样例

### 样例1
输入：
```
1 1
3
1 2 3
1 1 1
1 1 1
```
输出：
```
6
```

## 提示

$1 \le n \le 10^5$。

## 解题思路

### 问题分析

这是一个贪心问题。需要最大化总价值。

### 核心思路

**贪心策略**：优先操作价值高的物品。

### 复杂度分析

- **时间复杂度**：$O(n)$
- **空间复杂度**：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int sid, t;
    cin >> sid >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<ll> v(n), c(n), x(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = 0; i < n; i++) cin >> c[i];
        for (int i = 0; i < n; i++) cin >> x[i];
        
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + c[i] * v[i]) % MOD;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
```
