#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        indeg[v]++;
    }
    vector<int> topo;
    queue<int> q;
    for (int i = 1; i <= n; ++i) if (!indeg[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (auto& e : adj[u]) {
            if (--indeg[e.first] == 0) q.push(e.first);
        }
    }
    vector<double> E(n + 1, 0);
    for (int i = (int)topo.size() - 1; i >= 0; --i) {
        int u = topo[i];
        int k = (int)adj[u].size();
        if (k == 0) continue;
        for (auto& e : adj[u])
            E[u] += (E[e.first] + e.second) / k;
    }
    printf("%.2f\n", E[1]);
    return 0;
}
