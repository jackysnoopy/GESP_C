# 【MX-X9-T5】『GROI-R3』Star Trip

## 题目描述
给定一个连通无向图（$n$ 个点 $m$ 条边），点编号 $1\sim n$。对于路径 $p_1,\ldots,p_k$，定义其**权值**为前缀最大值个数（即满足 $p_i > \max(p_1,\ldots,p_{i-1})$ 的位置数）。$q$ 次询问，每次给定 $s,t$，求从 $s$ 到 $t$ 的路径的最小权值。路径可以非简单（可重复经过节点和边）。

## 输入格式
第一行 $n,m,q$。接下来 $m$ 行边 $u,v$。接下来 $q$ 行询问 $s,t$。

## 输出格式
$q$ 行，每行一个正整数。

## 样例
输入：
```
8 10 4
1 8
2 5
3 6
2 6
3 8
1 6
2 1
4 8
3 4
6 7
2 7
4 3
5 4
3 8
```
输出：
```
2
1
2
2
```

## 提示
$1\le n,m,q\le 2\times 10^5$。图连通，可能有重边和自环。

## 解题思路

### 问题分析
权值 = 前缀最大值个数，第一个元素总是前缀最大值。要最小化权值，需要尽量让路径上的节点按非递减顺序排列。

### 核心思路
定义 $comp(v)$ 为 $v$ 在子图（仅含编号 $\le v$ 的节点）中的连通分量。若 $t \in comp(s)$，则答案为 1。否则，定义 $exit(v) = \{u > v : u \text{ 与 } comp(v) \text{ 中某点相邻}\}$，构建层级图：边 $v \to u$ 当且仅当 $u \in exit(v)$。答案 = 层级图中 $s$ 到满足 $t \in comp(v)$ 的最近节点 $v$ 的距离 + 1。

### 算法流程
1. 用 DSU 按编号升序合并，预处理每个节点的 $comp(v)$
2. 对每次询问从 $s$ 开始 BFS：检查 $t \in comp(v)$，若否则计算 $exit(v)$ 并扩展
3. BFS 找到目标即输出距离+1

### 复杂度分析
- 时间：$O((n+m+q) \log n)$ 均摊
- 空间：$O(n+m)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
int parent[MAXN], rnk[MAXN];
vector<int> adj[MAXN];
int compRoot[MAXN];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (rnk[a] < rnk[b]) swap(a, b);
    parent[b] = a;
    if (rnk[a] == rnk[b]) rnk[a]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }
    for (int v = 1; v <= n; v++) {
        for (int u : adj[v]) {
            if (u < v) unite(v, u);
        }
        compRoot[v] = find(v);
    }
    vector<vector<int>> compMembers(n + 1);
    for (int v = 1; v <= n; v++) {
        compMembers[compRoot[v]].push_back(v);
    }
    while (q--) {
        int s, t;
        cin >> s >> t;
        if (s == t) { cout << 1 << "\n"; continue; }
        if (compRoot[s] == compRoot[t] && t <= s) { cout << 1 << "\n"; continue; }
        vector<bool> visited(n + 1, false);
        vector<int> dist(n + 1, 0);
        vector<int> bfsQueue;
        bfsQueue.push_back(s);
        visited[s] = true;
        bool found = false;
        int head = 0;
        while (head < (int)bfsQueue.size() && !found) {
            int v = bfsQueue[head++];
            int d = dist[v];
            if (compRoot[v] == compRoot[t] && t <= v) {
                cout << d + 1 << "\n";
                found = true;
                break;
            }
            int root = compRoot[v];
            for (int w : compMembers[root]) {
                for (int u : adj[w]) {
                    if (u > v && !visited[u]) {
                        visited[u] = true;
                        dist[u] = d + 1;
                        bfsQueue.push_back(u);
                    }
                }
            }
        }
        if (!found) cout << -1 << "\n";
    }
    return 0;
}
```
