# P10193 [USACO24FEB] Bessla Motors G

## 思路

核心算法：多源Dijkstra + K近邻追踪

对每个充电站运行 Dijkstra，但不分别运行（太慢），而是维护每个节点的前 K 个最近充电站距离。

- 状态：`(距离, 节点, 来源充电站)`
- 对每个节点维护最多 K 个 `(距离, 来源)` 对，按距离排序
- 从所有充电站同时出发（距离 0），用优先队列推进
- 弹出 `(d, v, src)` 时：若 `v` 已有 K 个距离都 ≤ d 则跳过；若 `src` 已处理过则跳过；否则加入 `best[v]`
- 最终对每个非充电节点 `v`，若 `best[v]` 大小 ≥ K 且第 K 小距离 ≤ R，则该节点可达

时间复杂度 O(KM log(KM))，空间 O(KN + KM)。

## 解题思路

### 问题分析
给定 n 个节点的无向图，前 c 个是充电站。一个非充电站节点可达当且仅当存在至少 k 个不同的充电站，每个充电站到该节点的距离 ≤ R。求所有可达节点。

### 核心思路
多源 Dijkstra + K 近邻追踪：从所有充电站同时出发，对每个节点维护最近的 K 个充电站距离。

### 算法流程
1. 将所有充电站以距离 0 加入优先队列
2. 扩展优先队列：
   - 弹出 (距离 d, 节点 v, 来源充电站 src)
   - 若 v 已有 K 个距离都 ≤ d，跳过
   - 若 src 已在 v 的 best 列表中，跳过
   - 否则将 (d, src) 加入 best[v]，保持按距离排序
3. 对每个非充电站节点，若 best[v] 大小 ≥ K 且第 K 小距离 ≤ R，则可达

### 复杂度分析
- 时间复杂度：O(KM log(KM))，M 为边数
- 空间复杂度：O(KN + KM)

```cpp

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> State;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, c;
    ll r;
    int k;
    cin >> n >> m >> c >> r >> k;
    
    vector<vector<pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll l;
        cin >> u >> v >> l;
        adj[u].push_back(make_pair(v, l));
        adj[v].push_back(make_pair(u, l));
    }
    
    vector<vector<pair<ll, int>>> best(n + 1);
    
    priority_queue<State, vector<State>, greater<State>> pq;
    
    for (int i = 1; i <= c; i++) {
        pq.push(State(0, i, i));
    }
    
    while (!pq.empty()) {
        State s = pq.top();
        pq.pop();
        ll d = get<0>(s);
        int v = get<1>(s);
        int src = get<2>(s);
        
        if ((int)best[v].size() == k && best[v].back().first <= d) {
            continue;
        }
        
        bool found = false;
        for (size_t i = 0; i < best[v].size(); i++) {
            if (best[v][i].second == src && best[v][i].first <= d) {
                found = true;
                break;
            }
        }
        if (found) continue;
        
        best[v].push_back(make_pair(d, src));
        sort(best[v].begin(), best[v].end());
        if ((int)best[v].size() > k) {
            best[v].pop_back();
        }
        
        for (size_t i = 0; i < adj[v].size(); i++) {
            int u = adj[v][i].first;
            ll w = adj[v][i].second;
            pq.push(State(d + w, u, src));
        }
    }
    
    vector<int> result;
    for (int v = c + 1; v <= n; v++) {
        if ((int)best[v].size() >= k && best[v][k - 1].first <= r) {
            result.push_back(v);
        }
    }
    
    cout << result.size() << "\n";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << "\n";
    }
    
    return 0;
}
```
