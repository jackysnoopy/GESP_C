# [蓝桥杯 2025 省 Python A/Java A/研究生组] 原料采购

## 题目描述

小蓝负责一家工厂的原料采购。

工厂有一辆运货卡车，其容量为 $m$。

工厂附近的采购点都在同一条路的同一方向上，一共有 $n$ 个，每个采购点和工厂的距离各不相同。其中，第 $i$ 个采购点的价格为 $a_i$, 库存为 $b_i$, 距离为 $c_i$。

卡车每行驶一单位长度的路径就需要额外花费 $o$。（返程没有花费，你也可以认为 $o$ 实际是行驶两单位长度的花费）

请计算将卡车装满最少需要花费多少钱，如果没有任何方案可以装满请输出 $-1$。

## 输入格式

输入的第一行包含三个正整数 $n, m, o$，相邻整数之间使用一个空格分隔。

接下来 $n$ 行，每行包含三个正整数 $a_i, b_i, c_i$ 表示一个采购点，相邻整数之间使用一个空格分隔。

## 输出格式

输出一行包含一个整数表示答案，即装满卡车所需的最小花费。

## 样例

### 样例输入 1
```
3 5 1
99 9 1
3 4 99
1 2 190
```

### 样例输出 1
```
201
```

## 提示

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$n \leq 5000$, $m \leq 50000$;
- 对于 $60\%$ 的评测用例，$m \leq 10^5$;
- 对于所有评测用例，$1 \leq n \leq 10^5$, $1 \leq m, o \leq 10^9$, $1 \leq a_i, b_i, c_i \leq 10^9$, 保证对于 $i > 1$, 一定有 $c_{i-1} < c_i$。

## 参考代码

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

struct Fenwick {
    int n;
    vector<ll> bit;
    Fenwick(int n) : n(n), bit(n + 1, 0) {}
    void add(int i, ll v) {
        for (i++; i <= n; i += i & -i) bit[i] += v;
    }
    ll sum(int i) {
        if (i < 0) return 0;
        ll s = 0;
        for (i++; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
    int lower_bound(ll v) {
        int pos = 0;
        ll acc = 0;
        int pw = 1;
        while (pw <= n) pw <<= 1;
        for (; pw; pw >>= 1) {
            if (pos + pw <= n && acc + bit[pos + pw] < v) {
                pos += pw;
                acc += bit[pos];
            }
        }
        return pos;
    }
};

int main() {
    int n;
    ll m, o;
    scanf("%d %lld %lld", &n, &m, &o);

    vector<ll> a(n), b(n), c(n);
    vector<ll> prices;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
        prices.push_back(a[i]);
    }

    sort(prices.begin(), prices.end());
    prices.erase(unique(prices.begin(), prices.end()), prices.end());
    int P = prices.size();

    Fenwick cnt(P), sm(P);
    ll total = 0;
    ll ans = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        int idx = (int)(lower_bound(prices.begin(), prices.end(), a[i]) - prices.begin());
        cnt.add(idx, b[i]);
        sm.add(idx, b[i] * a[i]);
        total += b[i];

        if (total >= m) {
            int pos = cnt.lower_bound(m);
            ll cnt_before = cnt.sum(pos - 1);
            ll sum_before = sm.sum(pos - 1);
            ll need = m - cnt_before;
            ll cost = sum_before + need * prices[pos];
            ans = min(ans, o * c[i] + cost);
        }
    }

    printf("%lld\n", ans == LLONG_MAX ? -1LL : ans);
    return 0;
}
```

## 解题思路

### 问题分析

工厂有一辆容量为 m 的卡车，沿路有 n 个采购点（价格 a_i、库存 b_i、距离 c_i），卡车行驶每单位距离花费 o。要求装满卡车的最小花费，若无法装满输出 -1。采购点按距离递增排列，卡车从工厂出发可以到达任意前缀的采购点。

### 核心思路

卡车从工厂出发，依次经过采购点。当到达第 i 个采购点时，可以获取所有前 i 个采购点的原料。为了花费最小，应该优先使用最便宜的原料。使用两棵树状数组维护按价格排序后的库存数量和价格总和，通过 `lower_bound` 在树状数组上二分找到恰好装满 m 单位原料的位置，贪心计算最小原料成本。对于每个采购点 i，若总库存 >= m，则计算以 o * c[i] 为行驶费用、加上最便宜 m 单位原料费用的总花费，取所有情况的最小值。

### 算法流程

1. 读入 n 个采购点的信息，将所有价格收集并离散化
2. 初始化两棵 Fenwick 树：cnt（库存数量）和 sm（库存价格总和）
3. 从左到右遍历采购点：
   - 将当前采购点的库存和价格加入对应的树状数组
   - 更新总库存量
   - 若总库存 >= m，利用树状数组的 `lower_bound` 找到恰好凑够 m 的价格分界点
   - 计算原料花费 = 低于分界点的所有价格之和 + 剩余需求 × 分界点价格
   - 更新最小总花费 = min(ans, 行驶费用 + 原料花费)
4. 输出最小总花费（若为无穷大则输出 -1）

### 复杂度分析

- 时间复杂度：O(n log n)，离散化 O(n log n)，每个采购点的树状数组操作 O(log n)
- 空间复杂度：O(n)，存储采购点信息和树状数组
