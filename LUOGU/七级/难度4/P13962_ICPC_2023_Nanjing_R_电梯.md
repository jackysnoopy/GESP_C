# [ICPC 2023 Nanjing R] 电梯

## 题目描述

有 $n$ 组包裹需要被配送。第 $i$ 组共有 $c_i$ 个包裹，每个包裹的重量为 $w_i$（$w_i$ 等于 $1$ 或 $2$），并且需要被送到第 $f_i$ 层。

有一台电梯，每趟能运送总重量不超过 $k$（$k$ 是偶数）的包裹。电梯会从地面层出发，渐渐移动到这一趟所有包裹的目标楼层的最高层 $h$，最后返回地面层。这一趟运送将消耗 $h$ 单位的电能。

更正式地，令 $(w, f)$ 表示一个重量为 $w$，且目的地为第 $f$ 层的包裹。一个由包裹组成的多重集合（一种可能含有重复元素的集合）$\mathbb{P}$ 能在同一趟被运送，若 $\sum\limits_{(w, f) \in \mathbb{P}} w \le k$。这一趟运送将消耗 $\max\limits_{(w, f) \in \mathbb{P}} f$ 单位的电能。

求将所有包裹运送到目的地最少一共需要多少单位的电能？

请注意，每一趟运送的包裹可以来自不同组，每一组包裹也可以分成多趟运送。您可以认为一共有 $\sum\limits_{i=1}^n c_i$ 个包裹需要被运送，只不过一些包裹可能有相同的重量以及相同的目的地。

## 输入格式

有多组测试数据。第一行输入一个整数 $T$ 表示测试数据组数，对于每组测试数据：

第一行输入两个整数 $n$ 与 $k$（$1 \le n \le 10^5$，$2 \le k \le 2 \times 10^{10}$，$k$ 是偶数）表示组数以及电梯的最大载重。

对于接下来 $n$ 行，第 $i$ 行输入三个整数 $c_i$，$w_i$ 与 $f_i$（$1 \le c_i \le 10^5$，$w_i \in \{1, 2\}$，$1 \le f_i \le 10^5$）表示第 $i$ 组包裹的数量，每个包裹的重量以及目的地。

保证所有数据中 $n$ 之和不超过 $3 \times 10^5$。

## 输出格式

每组数据输出一行一个整数，表示将所有包裹运送到目的地最少一共需要多少单位的电能。

## 样例

### 样例输入 1
```
2
4 6
1 1 8
7 2 5
1 1 7
3 2 6
8 1200000
100000 1 100000
100000 1 12345
100000 2 100000
100000 2 12345
100000 1 100000
100000 1 12345
100000 2 100000
100000 2 12345
```

### 样例输出 1
```
24
100000
```

## 提示

对于第一组样例数据，我们可以遵循以下策略：

- 第一趟运送包裹 $(2, 6)$，$(2, 6)$ 与 $(2, 5)$。这一趟消耗 $6$ 单位的电能。
- 第二趟运送包裹 $(1, 8)$，$(1, 7)$，$(2, 6)$ 与 $(2, 5)$。这一趟消耗 $8$ 单位的电能。
- 第三趟运送包裹 $(2, 5)$，$(2, 5)$ 与 $(2, 5)$。这一趟消耗 $5$ 单位的电能。
- 第四趟运送包裹 $(2, 5)$ 与 $(2, 5)$。这一趟消耗 $5$ 单位的电能。

一共需要 $6 + 8 + 5 + 5 = 24$ 单位的电能。可以证明这是最少一共需要的电能。

对于第二组样例数据，所有包裹可以在同一趟被运送。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, k;
        cin >> n >> k;

        vector<pair<int, int>> items;
        for (int i = 0; i < n; i++) {
            int c, w, f;
            cin >> c >> w >> f;
            for (int j = 0; j < c; j++) {
                items.push_back({f, w});
            }
        }

        sort(items.begin(), items.end(), greater<pair<int, int>>());

        long long ans = 0;
        int idx = 0;

        while (idx < (int)items.size()) {
            int remaining = k;
            int max_floor = items[idx].first;

            while (idx < (int)items.size() && remaining >= items[idx].second) {
                remaining -= items[idx].second;
                idx++;
            }

            ans += max_floor;
        }

        cout << ans << "\n";
    }

    return 0;
}
```
