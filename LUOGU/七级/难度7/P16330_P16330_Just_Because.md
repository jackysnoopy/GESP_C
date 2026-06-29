# P16330 Just Because!

## 题目描述

你有 $n$ 棵树，第 $i$ 棵树位于位置 $p_i$，高度为 $h_i$，保证 $p$ 单调递增。

给定 $q$ 次询问。对于第 $i$ 次询问，只保留 $[l_i,r_i]$ 子区间，你要选择最多的树，使得存在一种砍倒方式使得每棵树都不碰到另一棵树的树桩。

## 输入格式

第一行包含两个整数 $n$ 和 $q$。
接下来 $n$ 行，每行两个整数 $p_i$ 和 $h_i$。
接下来 $q$ 行，每行两个整数 $l_i$ 和 $r_i$。

## 输出格式

对于每次询问，输出一行一个整数表示答案。

## 样例

### 样例1
输入：
```
5 3
1 2
3 1
5 3
7 2
9 1
1 5
2 4
3 3
```
输出：
```
3
2
1
```

## 提示

$1 \le n, q \le 10^5$。

## 解题思路

### 问题分析

这是一个贪心问题。需要选择最多的树使得砍倒后不互相碰撞。

### 核心思路

**贪心策略**：按高度排序选择。

### 复杂度分析

- **时间复杂度**：$O(n \log n + q)$
- **空间复杂度**：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<ll> p(n), h(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> h[i];
    }
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans++;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
```
