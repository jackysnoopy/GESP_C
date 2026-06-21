# [NERC 2020] Guide

## 题目描述

Mister Gooti is the world-famous guide of The Freezing Isles. The topology of the Isles can be represented as a tree with cities at the vertices and two-way roads between them. 
Gooti prepares a new sightseeing tour over the Isles. He wants to find the shortest path that starts in the capital and visits $k$ different cities, including the capital. Please, help him.

## 输入格式

The first line of the input contains the number of tests $T$ ($1 \leq T \leq 100$). Each test consists of two lines. The first line contains the overall number of cities $n$ in the Isles and the requested number of cities $k$ for the tour ($1 \leq k \leq n \leq 100$). The second line contains the description of the tree in a rooted manner: $n - 1$ integers where the $i$-th integer, $p_i$, is the parent of the city $i + 1$ ($1 \leq p_i \leq i$). The capital is the city with the number $1$ --- the root of the tree.

## 输出格式

For each test, the first line of the output shall contain the length of the path $l$. The second line shall contain $l + 1$ integers --- the cities that lie on the path in the order of the traversal.

## 样例

### 样例输入 1
```
3
6 2
1 1 2 2 3
6 6
1 1 2 2 3
6 4
1 2 3 4 5
```

### 样例输出 1
```
1
1 2
8
1 3 6 3 1 2 5 2 4
3
1 2 3 4
```

## 提示

The following pictures illustrate all the three tests from the example.

![](https://cdn.luogu.com.cn/upload/image_hosting/93kgqe0s.png)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> children(n + 1);
        vector<int> par(n + 1, 0), dep(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            cin >> par[i];
            children[par[i]].push_back(i);
        }
        function<void(int, int)> compute_dep = [&](int u, int d) {
            dep[u] = d;
            for (int v : children[u]) compute_dep(v, d + 1);
        };
        compute_dep(1, 0);
        int maxdep = 0;
        for (int i = 1; i <= n; i++) maxdep = max(maxdep, dep[i]);
        int d = min(maxdep, k - 1);
        int endpoint = 1;
        for (int i = 1; i <= n; i++) {
            if (dep[i] == d) { endpoint = i; break; }
        }
        vector<int> path;
        { int cur = endpoint; while (cur != 0) { path.push_back(cur); cur = par[cur]; } reverse(path.begin(), path.end()); }
        vector<bool> on_path(n + 1, false);
        for (int node : path) on_path[node] = true;
        vector<bool> selected(n + 1, false);
        vector<int> bfs_queue;
        for (int node : path) { selected[node] = true; bfs_queue.push_back(node); }
        int count = path.size();
        int qi = 0;
        while (count < k && qi < (int)bfs_queue.size()) {
            int u = bfs_queue[qi++];
            for (int v : children[u]) {
                if (!selected[v]) { selected[v] = true; count++; bfs_queue.push_back(v); if (count >= k) break; }
            }
        }
        vector<int> walk;
        function<void(int)> dfs_walk = [&](int u) {
            walk.push_back(u);
            int path_child = -1;
            if (on_path[u] && u != endpoint) {
                for (int v : children[u]) { if (selected[v] && on_path[v]) { path_child = v; break; } }
            }
            for (int v : children[u]) {
                if (!selected[v] || v == path_child) continue;
                dfs_walk(v); walk.push_back(u);
            }
            if (path_child != -1) dfs_walk(path_child);
        };
        dfs_walk(1);
        cout << walk.size() - 1 << "\n";
        for (int i = 0; i < (int)walk.size(); i++) cout << walk[i] << (i < (int)walk.size() - 1 ? " " : "\n");
    }
    return 0;
}
```
