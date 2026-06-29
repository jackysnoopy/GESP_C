# Full Tank?

## 题目描述

有 n 座城市，m 条道路，每座城市有各自的油价。你有一个容量为 P 的油箱，每次可以在当前城市加 1 单位油（花费该城市的油价），也可以沿道路行驶到相邻城市（消耗与道路长度相同单位的油）。给定多组查询，每组给出油箱容量、起点和终点，求从起点到终点的最小花费。若无法到达则输出 "impossible"。

## 输入格式

- 多组测试数据，每组第一行包含三个整数 n, m, P
- 接下来 n 个整数，表示每座城市的油价
- 接下来 m 行，每行三个整数 u, v, d，表示城市 u 和 v 之间有一条长度为 d 的道路
- 接下来一个整数 q，表示查询数
- 每组查询包含三个整数 cap, s, t，表示油箱容量、起点、终点
- 输入以 EOF 结束

## 输出格式

对于每组查询，输出从起点到终点的最小花费，若无法到达则输出 "impossible"

## 样例

```
输入：
4 4 10
5 2 8 3
0 1 2
0 2 5
1 2 3
2 3 4
2
10 0 3
5 0 3

输出：
12
impossible
```

## 提示

- 状态定义为 (城市, 当前油量)，使用 Dijkstra 算法求最短路
- 加油操作：在当前城市加 1 单位油，花费为该城市油价
- 行驶操作：沿道路移动到相邻城市，油量减少道路长度，不产生额外花费

## 解题思路

### 问题分析

这是一个带资源约束的最短路问题。油箱容量限制了状态空间，需要在状态中加入油量维度。

### 核心思路

将状态定义为 (城市编号, 当前油量)，构建状态图后使用 Dijkstra 算法。每种状态有两种转移：
1. **加油**：在当前城市加 1 单位油（油量不超过容量），花费为该城市油价
2. **行驶**：沿道路移动到相邻城市，油量减少道路长度，花费为 0

### 算法流程

1. 初始化 dist[所有城市][0..P] = INF，dist[起点][0] = 0
2. 使用优先队列进行 Dijkstra，状态为 (花费, 城市, 油量)
3. 对于每个出队状态 (d, u, fuel)：
   - 若 fuel < P，尝试加油：dist[u][fuel+1] = min(dist[u][fuel+1], d + price[u])
   - 对每条边 (u, v, cost)：若 fuel >= cost，尝试行驶：dist[v][fuel-cost] = min(dist[v][fuel-cost], d)
4. 第一次到达终点时的花费即为答案

### 复杂度分析

- 时间复杂度：O(P × (n + m) × log(P × n))
- 空间复杂度：O(P × n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, P;
    while (cin >> n >> m >> P) {
        vector<int> price(n);
        for (int i = 0; i < n; ++i) cin >> price[i];
        vector<vector<pair<int,int>>> adj(n);
        for (int i = 0; i < m; ++i) {
            int u, v, d; cin >> u >> v >> d;
            adj[u].push_back({v, d});
            adj[v].push_back({u, d});
        }
        int q; cin >> q;
        while (q--) {
            int cap, s, t; cin >> cap >> s >> t;
            if (s == t) { cout << 0 << '\n'; continue; }
            vector<vector<int>> dist(n, vector<int>(cap + 1, INF));
            dist[s][0] = 0;
            priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
            pq.emplace(0, s, 0);
            int ans = INF;
            while (!pq.empty()) {
                auto [d, u, fuel] = pq.top(); pq.pop();
                if (d > dist[u][fuel]) continue;
                if (u == t) { ans = d; break; }
                if (fuel < cap && dist[u][fuel + 1] > d + price[u]) {
                    dist[u][fuel + 1] = d + price[u];
                    pq.emplace(d + price[u], u, fuel + 1);
                }
                for (auto [v, cost] : adj[u]) {
                    if (fuel >= cost && dist[v][fuel - cost] > d) {
                        dist[v][fuel - cost] = d;
                        pq.emplace(d, v, fuel - cost);
                    }
                }
            }
            if (ans == INF) cout << "impossible\n";
            else cout << ans << '\n';
        }
    }
    return 0;
}
```
