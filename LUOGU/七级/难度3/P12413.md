# 「YLLOI-R1-T2」圣诞星

## 题目描述

小 Y 要买 $n$ 个商品，第 $i$ 个价格 $a_i$ 元。买商品前可预先购买任意多张优惠券，每张价格 $w$ 元。每张优惠券在买任意商品时可抵 1 元（每个商品最低抵到 0 元，优惠券不算商品）。此外，**每付完一个商品的钱后还会再获得一张优惠券**。优惠券永久有效。

求买完全部商品所需的最少钱数。

## 输入格式

第一行两个整数 $n, w$。
第二行 $n$ 个整数 $a_i$。

## 输出格式

一个整数，表示最少所需钱数。

## 提示

- Subtask：$\forall a_i=i$；$w=1$；$n,a_i,w\le 10$；$\le 1000$；无特殊限制。
- 全部数据：$1\le n\le 10^5$，$1\le a_i,w\le 10^9$。
- 样例 1：$n=4,w=3$，$a=[3,4,5,5]$，先买 3 张券花 9 元，之后每个商品都 0 元，共 9。
- 样例 2：$n=4,w=3$，$a=[4,4,3,3]$，最优 7 元。

## 解题思路

### 问题分析

设预先购买 $c$ 张优惠券。决定 $c$ 后，买第 $k$ 个商品时（按某种顺序）手中已有 $c+k$ 张券（$c$ 张预购 + 之前 $k$ 个商品各送 1 张）。为省钱，对每个商品把现有券尽量用满（抵到 0 为止），于是第 $k$ 个商品实付 $\max(0, a_k-(c+k))$。

总花费 $= c\cdot w + \sum_k \max(0, a_k-(c+k))$。

**物品顺序的选择**：$n$ 个递增的券数 $c, c+1, \dots, c+n-1$ 要分配给 $n$ 个商品。由排序不等式，把较大的券数配给较大的 $a$ 能最小化正部分之和，故把 $a$ **升序排序**后，第 $k$ 小的商品恰用 $c+k$ 张券。

**$c$ 的最优值**：当 $c$ 增加 1 时，$c\cdot w$ 增加 $w$，而每个 $\max(0,a_k-c-k)$ 项要么减 1（若仍为正）要么不变（已为 0）；"仍为正"的项数随 $c$ 增大单调不增，因此总花费关于 $c$ 是**凸函数**，可用三分搜索求最小。

### 核心思路

把价格升序排序，第 $k$ 个商品（0 下标）用 $c+k$ 张券；总花费 $\text{cost}(c)=c\cdot w+\sum_{k=0}^{n-1}\max(0,a_k-c-k)$ 是关于 $c$ 的凸函数，用三分搜索在 $[0,\max a]$ 上求最小值。

### 算法流程

1. 读入 $n,w$ 与 $a$，把 $a$ 升序排序。
2. 定义 `cost(c) = c*w + sum_{k=0}^{n-1} max(0, a[k]-c-k)`。
3. 在 $c\in[0, a_{n-1}]$ 上对凸函数 `cost` 做三分搜索，缩到长度 $\le 3$ 的小区间后逐点取最小。
4. 输出最小 `cost`。

### 复杂度分析

排序 $O(n\log n)$；三分搜索 $O(\log V)$ 次，每次 `cost` 为 $O(n)$，故 $O(n\log V)$。总体 $O(n\log n)$，空间 $O(n)$。

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
    int n; ll w;
    cin >> n >> w;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    auto cost = [&](ll c) -> ll {
        ll total = c * w;
        for (int k = 0; k < n; k++)
            total += max(0LL, a[k] - c - k);
        return total;
    };
    ll lo = 0, hi = a[n - 1];
    while (hi - lo > 3) {
        ll m1 = lo + (hi - lo) / 3;
        ll m2 = hi - (hi - lo) / 3;
        if (cost(m1) < cost(m2)) hi = m2;
        else lo = m1;
    }
    ll ans = cost(lo);
    for (ll c = lo + 1; c <= hi; c++) ans = min(ans, cost(c));
    cout << ans << "\n";
    return 0;
}
```
