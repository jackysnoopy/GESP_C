#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(n, 1e9));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w; u--; v--;
        g[u][v] = g[v][u] = min(g[u][v], w);
    }
    int ans = 1e9;
    for (int root = 0; root < n; root++) {
        vector<int> dist(n, 1e9);
        vector<bool> vis(n, false);
        dist[root] = 0;
        for (int t = 0; t < n; t++) {
            int u = -1;
            for (int i = 0; i < n; i++)
                if (!vis[i] && (u == -1 || dist[i] < dist[u])) u = i;
            vis[u] = true;
            for (int v = 0; v < n; v++)
                if (g[u][v] < 1e9)
                    dist[v] = min(dist[v], dist[u] + g[u][v]);
        }
        int cost = 0;
        for (int i = 0; i < n; i++)
            if (i != root) cost += dist[i] * (dist[i] + 1);
        ans = min(ans, cost);
    }
    cout << ans << endl;
    return 0;
}