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

## 解题思路

### 问题分析
在树上放置k个加油站，使得任意两点间路径上相邻加油站（或起点/终点）的距离不超过d。求最小的d。

### 核心思路
二分答案d。对于给定的d，贪心放置加油站：从根节点开始，每当距离超过d就放置一个加油站。检查放置数量是否≤k。

### 算法流程
1. 构建树，计算每个节点到根的距离
2. 二分d的范围[0, max_dist]
3. 对于每个mid：
   - 贪心放置加油站，计数placed
   - 若placed≤k则hi=mid，否则lo=mid+1
4. 输出lo

### 复杂度分析
- 时间复杂度：O(n × log(max_dist))
- 空间复杂度：O(n)

## 解题思路

### 问题分析

给定一棵 $n$ 个节点的树，需要在节点上放置 $k$ 个加油站，使得任意两个加油站之间（或起点/终点到最近加油站）的距离不超过 $d$，求 $d$ 的最小值。

### 核心思路

这是一个典型的二分答案问题。对于给定的 $d$，贪心地检查是否能用不超过 $k$ 个加油站覆盖整棵树。

- 将树上的节点按深度排序
- 贪心策略：从最深的未覆盖节点开始放置加油站
- 如果两个节点的距离超过 $d$，就需要在当前位置放置一个加油站

### 算法流程

1. BFS/DFS 计算每个节点到根的距离
2. 二分搜索答案 $d$（范围 $[0, \text{树的直径}]$）
3. 对于每个 $d$，贪心检查需要多少个加油站
4. 如果需要的加油站数 $\le k$，则 $d$ 可行

### 复杂度分析

- 时间复杂度：$O(n \log D)$，其中 $D$ 是树的直径
- 空间复杂度：$O(n)$
