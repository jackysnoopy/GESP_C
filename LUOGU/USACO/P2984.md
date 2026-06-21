# P2984 - Dijkstra

## 题目描述

参见洛谷原题。

## 解题思路

### 问题分析

本题属于 **最短路** 类问题。

### 核心思路

Dijkstra求到1的最短路，输出dist[p]+dist[q]。

### 时间复杂度

取决于具体算法实现。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, b;
    cin >> n >> m >> b;
    vector<vector<pair<int,int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<long long> dist(n + 1, 1e18);
    dist[1] = 0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    for (int i = 0; i < b; i++) {
        int p, q; cin >> p >> q;
        cout << dist[p] + dist[q] << "\n";
    }
    return 0;
}

```
