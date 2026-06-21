#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> t(n + 1);
    for (int i = 1; i <= n; i++) cin >> t[i];
    vector<pair<int,int>> edges(n - 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> edges[i].first >> edges[i].second;
        adj[edges[i].first].push_back(edges[i].second);
        adj[edges[i].second].push_back(edges[i].first);
    }
    
    // Root the tree at the node with maximum value
    int root = 1;
    for (int i = 2; i <= n; i++) {
        if (t[i] > t[root]) root = i;
    }
    
    // DFS to compute subtree max and parent
    vector<int> parent(n + 1, 0);
    vector<int> subtree_max(n + 1);
    vector<vector<int>> children(n + 1);
    
    function<void(int,int)> dfs = [&](int u, int p) {
        parent[u] = p;
        subtree_max[u] = t[u];
        for (int v : adj[u]) {
            if (v == p) continue;
            children[u].push_back(v);
            dfs(v, u);
            subtree_max[u] = max(subtree_max[u], subtree_max[v]);
        }
    };
    dfs(root, 0);
    
    // Generate deletion order: process each node, delete edges to children
    // with largest subtree_max first
    vector<pair<int,int>> order;
    function<void(int)> gen = [&](int u) {
        vector<int> ch = children[u];
        sort(ch.begin(), ch.end(), [&](int a, int b) {
            return subtree_max[a] > subtree_max[b];
        });
        for (int v : ch) {
            order.push_back({u, v});
            gen(v);
        }
    };
    gen(root);
    
    // Simulate the deletion order
    vector<bool> edge_alive(n - 1, true);
    auto find_edge = [&](int u, int v) -> int {
        for (int i = 0; i < n - 1; i++) {
            if ((edges[i].first == u && edges[i].second == v) ||
                (edges[i].first == v && edges[i].second == u)) {
                return i;
            }
        }
        return -1;
    };
    
    long long total_cost = 0;
    for (auto& e : order) {
        int ei = find_edge(e.first, e.second);
        edge_alive[ei] = false;
        
        // BFS from e.first in the current graph (alive edges only)
        vector<bool> vis(n + 1, false);
        queue<int> q;
        q.push(e.first); vis[e.first] = true;
        long long max1 = t[e.first];
        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int i = 0; i < n - 1; i++) {
                if (!edge_alive[i]) continue;
                int a = edges[i].first, b = edges[i].second;
                if (a == node && !vis[b]) { vis[b] = true; q.push(b); max1 = max(max1, t[b]); }
                if (b == node && !vis[a]) { vis[a] = true; q.push(a); max1 = max(max1, t[a]); }
            }
        }
        
        // BFS from e.second
        vector<bool> vis2(n + 1, false);
        q = queue<int>();
        q.push(e.second); vis2[e.second] = true;
        long long max2 = t[e.second];
        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int i = 0; i < n - 1; i++) {
                if (!edge_alive[i]) continue;
                int a = edges[i].first, b = edges[i].second;
                if (a == node && !vis2[b]) { vis2[b] = true; q.push(b); max2 = max(max2, t[b]); }
                if (b == node && !vis2[a]) { vis2[a] = true; q.push(a); max2 = max(max2, t[a]); }
            }
        }
        
        total_cost += max1 + max2;
    }
    
    cout << total_cost << endl;
    return 0;
}
