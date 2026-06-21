#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m, s, t;
        cin >> n >> m >> s >> t;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        if (s == t) { cout << 0 << "\n"; continue; }
        vector<int> distT(n, -1);
        distT[t] = 0;
        queue<int> q;
        q.push(t);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) if (distT[v] == -1) { distT[v] = distT[u] + 1; q.push(v); }
        }
        auto mexCost = [&](int u) -> long long {
            if (u == s) return 0;
            if (u < s) return (long long)u + 1;
            return (long long)u;
        };
        long long ans = mexCost(t);
        for (int u = 0; u < n; u++) {
            if (distT[u] != -1) ans = min(ans, mexCost(u) + distT[u]);
        }
        cout << ans << "\n";
    }
    return 0;
}
