# P1550 - Kruskal+虚拟节点

## 题目描述

参见洛谷原题。

## 解题思路

### 问题分析

本题属于 **MST（虚拟源点）** 类问题。

### 核心思路

将挖井费用作为虚拟源点到各点的边权，做MST。

### 时间复杂度

取决于具体算法实现。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge { int u, v, w; };
int fa[305];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    vector<Edge> edges;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int p; cin >> p;
            if (i < j && p > 0) edges.push_back({i, j, p});
        }
    // Add virtual node 0 representing well-digging
    for (int i = 1; i <= n; i++) edges.push_back({0, i, w[i]});
    int total = n + 1;
    for (int i = 0; i <= n; i++) fa[i] = i;
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    int ans = 0, cnt = 0;
    for (auto& e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) { fa[fu] = fv; ans += e.w; cnt++; if (cnt == total - 1) break; }
    }
    cout << ans << "\n";
    return 0;
}

```
