# [NOI Online #1 提高组] 最小环

## 题目描述

给定长度为 $n$ 的正整数序列，视为环。给定 $k$，可以重排序列，使得距离为 $k$ 的数对乘积之和最大。求最大值。

距离定义：在环上，位置 $i$ 和位置 $j$ 的距离为 $\min(|i-j|, n-|i-j|)$。

## 输入格式

第一行两个整数 $n, m$。  
第二行 $n$ 个整数 $a_i$。  
接下来 $m$ 行，每行一个整数 $k_i$。

## 输出格式

$m$ 行，每行一个整数，表示对应 $k$ 的最大乘积和。

## 样例

**输入：**
```
6 4
1 2 3 4 5 6
0
1
2
3
```

**输出：**
```
91
82
85
88
```

## 提示

$1 \le m \le n \le 2 \times 10^5$，$0 \le k \le n/2$，$1 \le a_i \le 10^9$。

## 解题思路

### 问题分析

- 对于给定的 $k$，需要重排序列使 $\sum a_i \cdot a_j$（$j$ 与 $i$ 距离为 $k$）最大
- 距离为 $k$ 的数对构成若干个环（cycle），每个环的长度为 $n / \gcd(n, k)$
- 共有 $\gcd(n, k)$ 个这样的环

### 核心思路

**关键观察：** 距离为 $k$ 的数对在环上形成 $\gcd(n, k)$ 个独立的环，每个环长度为 $n / \gcd(n, k)$。

**最优排列策略：**

1. 将数组从大到小排序
2. 将最大的 $n/2$ 个数放在偶数位，最小的 $n/2$ 个数放在奇数位
3. 这样大数与大数相邻，乘积和最大

**具体实现：**

- $k = 0$ 时，距离为 0 的数对就是每个数与自身，答案为 $\sum a_i^2$
- $k > 0$ 时，将排序后的数按"大-小-大-小"交替排列到环上
- 对于每个 $k$，计算距离为 $k$ 的数对乘积之和

### 算法流程

1. 将数组排序
2. 按最优策略重排：偶数位放大数，奇数位放小数
3. 对于每个查询 $k$，计算所有距离为 $k$ 的数对乘积之和

### 复杂度分析

- 时间复杂度：$O(n \log n + m \cdot n)$（排序 + 每次查询线性扫描）
- 空间复杂度：$O(n)$

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

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    vector<long long> b(n);
    int lo = 0, hi = n - 1;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            b[i] = a[hi--];
        } else {
            b[i] = a[lo++];
        }
    }

    vector<long long> pre(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + b[i] * b[i];
    }

    vector<long long> ans(n + 1, 0);
    ans[0] = pre[n];

    for (int k = 1; k <= n / 2; k++) {
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += b[i] * b[(i + k) % n];
        }
        ans[k] = sum;
    }

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        if (k > n / 2) k = n - k;
        cout << ans[k] << "\n";
    }

    return 0;
}
```
