# P2126 - Kruskal

## 题目描述

参见洛谷原题。

## 解题思路

### 问题分析

本题属于 **MST** 类问题。

### 核心思路

标准最小生成树，含虚拟节点0代表Mzc。

### 时间复杂度

取决于具体算法实现。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int fa[2305];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    struct Edge { int u, v, w; };
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) cin >> edges[i].u >> edges[i].v >> edges[i].w;
    // 0 = mzc, 1..n = workers
    for (int i = 0; i <= n; i++) fa[i] = i;
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    int total = 0, cnt = 0;
    for (auto& e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) { fa[fu] = fv; total += e.w; cnt++; if (cnt == n) break; }
    }
    cout << total << "\n";
    return 0;
}

```
