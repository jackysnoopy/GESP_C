# [ICPC 2023 Nanjing R] 背包

## 题目描述

小青鱼，一位没有经验的商人，最近开了一家名叫“皇后有机珠宝”（QOJ）的店。这家珠宝店共有 $n$ 枚宝石，其中第 $i$ 枚售价为 $w_i$ 元，美丽度为 $v_i$。进入商店之前，您准备了 $W$ 元用来买下美丽度总和尽量高的宝石。

有趣的是，小青鱼的店今天正在促销。任何顾客都可以任选 $k$ 枚宝石并免费获得它们。有了这样的机会，您很想知道，如果您使用最佳策略，用 $W$ 元到底能获得美丽度总和多高的宝石。

请注意，每枚宝石独此一份，您不能多次获取同一枚宝石。另外，您无需花完所有的钱。

## 输入格式

每个测试文件仅有一组测试数据。

第一行输入三个整数 $n$，$W$ 和 $k$（$1 \leq n \leq 5 \times 10^3$，$1 \leq W \leq 10^4$，$0 \leq k \leq n$），表示商店中宝石的总数，您拥有的金钱数以及您可以免费获得的宝石数量。

对于接下来 $n$ 行，第 $i$ 行输入两个整数 $w_i$ 和 $v_i$（$1 \leq w_i \leq W$，$1 \leq v_i \leq 10^9$），表示第 $i$ 枚宝石的售价和美丽度。

## 输出格式

输出一行一个整数表示答案。

## 样例

### 样例输入 1
```
4 10 1
9 10
10 1
3 5
5 20
```

### 样例输出 1
```
35
```

### 样例输入 2
```
5 13 2
5 16
5 28
7 44
8 15
8 41
```

### 样例输出 2
```
129
```

## 提示

对于第一组样例数据，小青鱼的商店有 $4$ 枚宝石，您可以免费获得其中 $1$ 枚。一种最优策略是免费获取第一枚宝石，并购买第三和第四枚宝石。

$$\begin{array}{ | c | c | c | c | } \hline
    \bf{宝石} &
    \bf{售价 w_i} &
    \bf{美丽度 v_i} &
    \bf{操作} \\ \hline
    1 & 9 & 10 & 免费获取 \\ \hline
    2 & 10 & 1 & / \\ \hline
    3 & 3 & 5 & 购买 \\ \hline
    4 & 5 & 20 & 购买 \\ \hline
  \end{array}$$
  
所以答案是 $10 + 5 + 20 = 35$。

## 解题思路

### 问题分析

有 $n$ 件物品，每件有价格 $w_i$ 和价值 $v_i$。预算为 $W$，可以免费拿 $k$ 件。目标是最大化总价值。

### 核心思路

贪心策略：按性价比 $v_i/w_i$ 从高到低排序。先免费拿性价比最高的 $k$ 件，再用预算购买剩余性价比最高的物品。

### 算法流程

1. 将所有物品按性价比 $v_i/w_i$ 降序排序
2. 前 $k$ 件直接免费获取，累加价值
3. 从第 $k+1$ 件开始，若预算足够则购买，累加价值并扣除价格
4. 输出总价值

### 复杂度分析

- 时间复杂度：$O(n \log n)$，排序主导
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

    int n, W, k;
    cin >> n >> W >> k;

    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int x, int y) {
        return (double)v[x] / w[x] > (double)v[y] / w[y];
    });

    long long ans = 0;
    int used = 0;
    int budget = W;

    for (int i = 0; i < n && used < n; i++) {
        int idx = order[i];
        if (used < k) {
            ans += v[idx];
            used++;
        } else if (budget >= w[idx]) {
            ans += v[idx];
            budget -= w[idx];
            used++;
        }
    }

    cout << ans << "\n";
    return 0;
}
```
