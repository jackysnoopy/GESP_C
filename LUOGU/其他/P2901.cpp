#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, K;
    cin >> n >> m >> K;
    vector<vector<pair<int,int>>> adj(n + 1), radj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        radj[v].push_back({u, w});
    }
    vector<int> h(n + 1, INF);
    h[1] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > h[u]) continue;
        for (auto [v, w] : radj[u]) {
            if (h[v] > d + w) { h[v] = d + w; pq.emplace(h[v], v); }
        }
    }
    vector<int> cnt(n + 1, 0);
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> apq;
    apq.emplace(h[n], n, 0);
    vector<int> result;
    while (!apq.empty() && (int)result.size() < K) {
        auto [f, u, g] = apq.top(); pq.pop();
        if (u == 1) { result.push_back(g); continue; }
        if (cnt[u] >= K) continue;
        cnt[u]++;
        for (auto [v, w] : adj[u]) {
            apq.emplace(g + w + h[v], v, g + w);
        }
    }
    for (int i = 0; i < K; ++i) {
        if (i < (int)result.size()) cout << result[i] << '\n';
        else cout << -1 << '\n';
    }
    return 0;
}
