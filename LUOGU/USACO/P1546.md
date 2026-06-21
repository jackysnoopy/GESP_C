# P1546 - Kruskal算法

## 题目描述

参见洛谷原题。

## 解题思路

### 问题分析

本题属于 **MST（最小生成树）** 类问题。

### 核心思路

对所有边按权值排序，依次选边，用并查集维护连通性，直到选了n-1条边。

### 时间复杂度

取决于具体算法实现。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int fa[105];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Edge> edges;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int w; cin >> w;
            if (i < j && w > 0) edges.push_back({i, j, w});
        }
    for (int i = 1; i <= n; i++) fa[i] = i;
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    int ans = 0, cnt = 0;
    for (auto& e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) {
            fa[fu] = fv;
            ans += e.w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    cout << ans << "\n";
    return 0;
}

```
