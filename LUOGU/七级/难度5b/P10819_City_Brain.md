# [EC Final 2020] City Brain

## 题目描述
Prof. Pang works for the City Brain program of Capital Grancel. The road network of Grancel can be represented by an undirected graph. Initially, the speed limit on each road is $1$m/s. Prof. Pang can increase the speed limit on a road by $1$m/s with the cost of $1$ dollar. Prof. Pang has $k$ dollars. He can spend any nonnegative integral amount of money on each road. If the speed limit on some road is $a$m/s, it takes $1/a$ seconds for anyone to go through the road in either direction.

After Prof. Pang spent his money, Prof. Du starts to travel from city $s_1$ to city $t_1$ and Prof. Wo starts to travel from city $s_2$ to city $t_2$. Help Prof. Pang to spend his money wisely to minimize the sum of minimum time of Prof. Du's travel and Prof. Wo's travel.

## 输入格式
The first line contains three integers $n$, $m$, $k$ ($1\le n \le 5000$, $0\le m \le 5000$, $0\le k\le 10^9$) separated by single spaces denoting the number of vertices, the number of edges in the graph and the number of dollars Prof. Pang has.

Each of the following $m$ lines contains two integers $a$, $b$ ($1\le a, b\le n, a\neq b$) separated by a single space denoting the two endpoints of one road.

The following line contains four integers $s_1$, $t_1$, $s_2$, $t_2$ ($1\le s_1, t_1, s_2, t_2\le n$) separated by single spaces.

## 输出格式
Output one decimal in the only line -- the minimum sum of Prof. Du's travel time and Prof. Wo's travel time.

## 样例
**样例输入 1：**
```
6 5 1
1 2
3 2
2 4
4 5
4 6
1 5 3 6
```
**样例输出 1：**
```
5.000000000000
```

**样例输入 2：**
```
1 0 100
1 1 1 1
```
**样例输出 2：**
```
0.000000000000
```

**样例输入 3：**
```
4 2 3
1 2
3 4
1 2 3 4
```
**样例输出 3：**
```
0.833333333333
```

## 提示
无

## 解题思路

### 问题分析
给定一个无向图，每条边初始速度为 1。可以用 k 美元提升边的速度（每美元提升 1）。目标是使两条最短路径（s1→t1 和 s2→t2）的时间总和最小。

### 核心思路
1. 找到两条最短路径
2. 统计每条边在两条路径中的使用次数（0、1 或 2 次）
3. 贪心分配升级：每次选择边际收益最大的边进行升级

### 算法流程
1. 用 Dijkstra 找到 s1→t1 和 s2→t2 的最短路径
2. 收集所有路径上的边，统计每条边的使用次数
3. 用优先队列贪心分配 k 次升级
4. 计算最终总时间

### 复杂度分析
- 时间复杂度：$O((n+m)\log n + k \log m)$
- 空间复杂度：$O(n+m)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAXN = 5005;
const long long INF = 1e18;

int n, m;
long long k;
vector<pair<int,int>> adj[MAXN];
long long dist[MAXN];
int prev_node[MAXN];

void dijkstra(int src) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        prev_node[i] = -1;
    }
    dist[src] = 0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev_node[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, 1});
        adj[b].push_back({a, 1});
    }

    int s1, t1, s2, t2;
    cin >> s1 >> t1 >> s2 >> t2;

    dijkstra(s1);
    vector<int> path1;
    for (int u = t1; u != -1; u = prev_node[u]) path1.push_back(u);
    reverse(path1.begin(), path1.end());

    dijkstra(s2);
    vector<int> path2;
    for (int u = t2; u != -1; u = prev_node[u]) path2.push_back(u);
    reverse(path2.begin(), path2.end());

    vector<pair<int,int>> edges_on_path;
    vector<int> usage;

    for (int i = 0; i + 1 < (int)path1.size(); i++) {
        int u = path1[i], v = path1[i+1];
        if (u > v) swap(u, v);
        edges_on_path.push_back({u, v});
        usage.push_back(1);
    }

    for (int i = 0; i + 1 < (int)path2.size(); i++) {
        int u = path2[i], v = path2[i+1];
        if (u > v) swap(u, v);
        bool found = false;
        for (int j = 0; j < (int)edges_on_path.size(); j++) {
            if (edges_on_path[j] == make_pair(u, v)) {
                usage[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            edges_on_path.push_back({u, v});
            usage.push_back(1);
        }
    }

    int E = edges_on_path.size();
    vector<int> upgrades(E, 0);
    priority_queue<pair<double, int>> pq;
    for (int i = 0; i < E; i++) {
        pq.push({1.0 / 2.0, i});
    }

    long long remaining = k;
    while (remaining > 0 && !pq.empty()) {
        auto [benefit, idx] = pq.top();
        pq.pop();
        if (benefit < 1e-15) break;
        upgrades[idx]++;
        remaining--;
        double new_speed = 1.0 + upgrades[idx];
        double next_benefit = 1.0 / (new_speed * (new_speed + 1.0));
        pq.push({next_benefit, idx});
    }

    double total_time = 0;
    for (int i = 0; i < E; i++) {
        double speed = 1.0 + upgrades[i];
        total_time += usage[i] / speed;
    }

    cout << fixed << setprecision(12) << total_time << "\n";
    return 0;
}
```
