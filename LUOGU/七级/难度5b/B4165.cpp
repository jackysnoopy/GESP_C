#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
const int INF = 1e9 + 7;

struct Edge {
    int u, v, w;
};

vector<Edge> edges;
int parent[MAXN], rank_[MAXN];

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (rank_[x] < rank_[y]) swap(x, y);
    parent[y] = x;
    if (rank_[x] == rank_[y]) rank_[x]++;
    return true;
}

bool cmp(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    
    // Kruskal算法求最小生成树
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank_[i] = 0;
    }
    
    sort(edges.begin(), edges.end(), cmp);
    
    vector<vector<pair<int, int>>> mst(n + 1);
    for (const Edge& e : edges) {
        if (unite(e.u, e.v)) {
            mst[e.u].push_back({e.v, e.w});
            mst[e.v].push_back({e.u, e.w});
        }
    }
    
    // 处理每个查询
    for (int i = 0; i < k; i++) {
        int t;
        cin >> t;
        
        // BFS/DFS找从1到t的路径
        vector<bool> visited(n + 1, false);
        vector<int> dist(n + 1, INF);
        vector<int> maxW(n + 1, 0);
        vector<int> minW(n + 1, INF);
        
        dist[1] = 0;
        maxW[1] = 0;
        minW[1] = INF;
        visited[1] = true;
        
        // 简单的DFS
        function<void(int)> dfs = [&](int u) {
            for (const auto& [v, w] : mst[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    dist[v] = dist[u] + w;
                    maxW[v] = max(maxW[u], w);
                    minW[v] = min(minW[u], w);
                    dfs(v);
                }
            }
        };
        
        dfs(1);
        
        // 计算花费：sum - max + min
        cout << dist[t] - maxW[t] + minW[t] << endl;
    }
    
    return 0;
}
