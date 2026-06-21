#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> a;
    if (n - m - 1 > 0) {
        a.resize(n - m - 1);
        for (int i = 0; i < n - m - 1; i++) cin >> a[i];
    }

    vector<long long> dist(n + 1, 1e18);
    dist[1] = 0;
    vector<bool> visited(n + 1, false);

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;
        }
        visited[u] = true;
        for (auto& [v, w] : adj[u]) {
            dist[v] = min(dist[v], dist[u] + w);
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            ans = (ans + min(dist[i] + dist[j], (long long)1e18)) % (1000000007);
        }
    }

    cout << ans << "\n";
    return 0;
}
