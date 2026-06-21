# Tree

## 题目描述

给定一棵 $n$ 个节点的树，每条边有边权，求出树上两点距离小于等于 $k$ 的点对数量。

## 输入格式

第一行输入一个整数 $n$，表示节点个数。  

第二行到第 $n$ 行每行输入三个整数 $u,v,w$ ，表示 $u$ 与 $v$ 有一条边，边权是 $w$。  

第 $n+1$ 行一个整数 $k$ 。

## 输出格式

一行一个整数，表示答案。

## 样例

### 样例输入
```
7
1 6 13 
6 3 9 
3 5 7 
4 1 3 
2 4 20 
4 7 2 
10
```

### 样例输出
```
5
```

## 提示

**数据规模与约定**

对于全部的测试点，保证：  

- $1\leq n\leq 4	imes 10^4$。
- $1\leq u,v\leq n$。
- $0\leq w\leq 10^3$。
- $0\leq k\leq 2	imes 10^4$。

## 解题思路

### 问题分析

Tree，求树上距离 <= k 的点对数量。

### 核心思路

1. 点分治：找重心，计算经过重心的路径。2. 对每个子树计算到重心的距离，用双指针计数。3. 减去同子树内的非法贡献。

### 算法流程

1. 建树
2. 点分治
3. 输出答案

### 复杂度分析

时间 O(n * log^2 n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 20001;
vector<pair<int,int>> adj[MAXN];
int sz[MAXN], mx[MAXN], vis[MAXN], n, K;
long long ans;
void get_sz(int u, int p) {
    sz[u] = 1; mx[u] = 0;
    for (auto &e : adj[u]) {
        int v = e.first; if (v == p || vis[v]) continue;
        get_sz(v, u); sz[u] += sz[v]; mx[u] = max(mx[u], sz[v]);
    }
}
int get_cen(int u, int p, int tot) {
    mx[u] = max(mx[u], tot - sz[u]);
    for (auto &e : adj[u]) {
        int v = e.first;
        if (v == p || vis[v]) continue;
        int c = get_cen(v, u, tot);
        if (c >= 0) return c;
    }
    if (mx[u] <= tot / 2) return u;
    return -1;
}
vector<int> dists;
void get_dist(int u, int p, int d) {
    dists.push_back(d);
    for (auto &e : adj[u]) {
        int v = e.first, w = e.second;
        if (v == p || vis[v]) continue;
        get_dist(v, u, d + w);
    }
}
void calc(int u) {
    vis[u] = 1;
    vector<int> all = {0};
    for (auto &e : adj[u]) {
        int v = e.first, w = e.second;
        if (vis[v]) continue;
        dists.clear();
        get_dist(v, u, w);
        sort(dists.begin(), dists.end());
        for (int d : dists) {
            int cnt = upper_bound(all.begin(), all.end(), K - d) - all.begin();
            ans += cnt;
        }
        for (int d : dists) all.push_back(d);
        sort(all.begin(), all.end());
    }
    for (auto &e : adj[u]) {
        int v = e.first;
        if (vis[v]) continue;
        get_sz(v, 0);
        int c = get_cen(v, 0, sz[v]);
        if (c >= 0) calc(c);
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w}); adj[v].push_back({u, w});
    }
    cin >> K;
    get_sz(1, 0);
    int c = get_cen(1, 0, n);
    calc(c);
    cout << ans << '\n';
    return 0;
}
```
