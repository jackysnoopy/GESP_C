#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        adj[u].push_back({v, l});
        adj[v].push_back({u, l});
    }

    vector<long long> dist(n + 1, 0);
    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.push_back(1);
    parent[1] = 0;

    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (auto& [v, l] : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                dist[v] = dist[u] + l;
                order.push_back(v);
            }
        }
    }

    long long lo = 0, hi = dist[n];
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        int placed = 0;
        long long last = 0;

        for (int i = 1; i <= n; i++) {
            if (dist[i] - last > mid) {
                placed++;
                last = dist[i];
            }
        }

        if (placed <= k) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << "\n";
    return 0;
}
