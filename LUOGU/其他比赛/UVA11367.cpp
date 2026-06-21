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
