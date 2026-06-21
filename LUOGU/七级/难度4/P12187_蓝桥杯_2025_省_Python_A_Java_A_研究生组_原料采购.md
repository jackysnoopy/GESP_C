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
