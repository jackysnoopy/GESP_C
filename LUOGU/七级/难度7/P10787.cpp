#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
vector<pair<int, int>> edges;
vector<int> adj[MAXN];
int depth[MAXN];
int parent[MAXN];
int tin[MAXN], tout[MAXN];
int timer = 0;

void dfs(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    tin[u] = timer++;
    for (auto& [v, idx] : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
    tout[u] = timer++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int c, n, m;
    cin >> c >> n >> m;
    
    edges.clear();
    for (int i = 1; i <= n; i++) adj[i].clear();
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    
    dfs(1, 0, 0);
    
    // 存储约束
    vector<pair<int, int>> constraints(m);
    for (int i = 0; i < m; i++) {
        cin >> constraints[i].first >> constraints[i].second;
    }
    
    // 构建答案
    string ans(n - 1, '0');
    
    // 对于每条边，决定方向
    for (int i = 0; i < n - 1; i++) {
        auto [u, v] = edges[i];
        
        // 如果u是v的父节点
        if (parent[v] == u) {
            // 检查是否有约束要求v不能到达u
            bool must_reverse = false;
            for (auto& [a, b] : constraints) {
                if (a == v && b == u) {
                    must_reverse = true;
                    break;
                }
            }
            
            if (must_reverse) {
                ans[i] = '1';
            }
        } else {
            // 如果v是u的父节点
            bool must_reverse = false;
            for (auto& [a, b] : constraints) {
                if (a == u && b == v) {
                    must_reverse = true;
                    break;
                }
            }
            
            if (must_reverse) {
                ans[i] = '1';
            }
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
