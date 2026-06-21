# P1547 - Kruskal算法

## 题目描述

参见洛谷原题。

## 解题思路

### 问题分析

本题属于 **MST（最小生成树）** 类问题。

### 核心思路

求最小生成树中最长边，Kruskal按权值升序加入，最后加入的边即为答案。

### 时间复杂度

取决于具体算法实现。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge { int u, v, w; };
int fa[2005];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) cin >> edges[i].u >> edges[i].v >> edges[i].w;
    for (int i = 1; i <= n; i++) fa[i] = i;
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    int ans = 0, cnt = 0;
    for (auto& e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) { fa[fu] = fv; ans = e.w; cnt++; if (cnt == n - 1) break; }
    }
    cout << ans << "\n";
    return 0;
}

```
