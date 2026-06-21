# [TOPC 2025] Gas Station

## 题目描述

Alex is planning rest area placements on a simplified model of Taiwan’s freeway system. The system contains $n$ interchanges, connected by $n - 1$ bidirectional roads. The network is connected, and there is exactly one shortest route between any pair of interchanges. The $i$-th road connects interchanges $u_i$ and $v_i$, and has a length of $l_i$.

Exactly $k$ rest areas with gas stations can be built, each located at an interchange. A driver may start a trip from any interchange and travel to any other, always following the unique shortest path. They begin each trip with a full tank of gas and can refuel only at interchanges that have a rest area.

Alex is curious about the smallest possible fuel tank capacity $d$ such that it’s possible to place the $k$ rest areas in a way that ensures no driver will ever run out of gas. On any trip, the driver must never have to travel more than $d$ units along the path without passing through a rest area, including at the beginning or end of the journey. The goal is to figure out the minimum such $d$, assuming the rest areas are placed in the best possible way.

## 输入格式

The first line contains two integers $n, k$.

Followed by $n - 1$ lines, the $i$-th of which contains three integers $u_i, v_i, l_i$, representing the $i$-th road connects interchanges $u_i$ and $v_i$ with a length $l_i$.

## 输出格式

Output one integer, the smallest possible fuel tank capacity $d$.

## 样例

### 样例输入 1
```
5 1
1 2 3
1 5 2
2 3 3
2 4 1
```

### 样例输出 1
```
5
```

### 样例输入 2
```
5 2
1 2 3
1 5 2
2 3 3
2 4 1
```

### 样例输出 2
```
3
```

## 提示

- $2 \le n \le 2 \times 10^5$
- $0 \le k \le n$
- $1 \le u_i, v_i \le n$
- $1 \le l_i \le 10^9$
- It is guaranteed that the input roads form a tree.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        adj[u].push_back({v, l});
        adj[v].push_back({u, l});
    }

    vector<long long> dist(n + 1, 0);
    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.push_back(1);
    parent[1] = 0;

    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (auto& [v, l] : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                dist[v] = dist[u] + l;
                order.push_back(v);
            }
        }
    }

    long long lo = 0, hi = dist[n];
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        int placed = 0;
        long long last = 0;

        for (int i = 1; i <= n; i++) {
            if (dist[i] - last > mid) {
                placed++;
                last = dist[i];
            }
        }

        if (placed <= k) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << "\n";
    return 0;
}
```
