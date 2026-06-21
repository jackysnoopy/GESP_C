#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, S, T;
    cin >> N >> M >> S >> T;

    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
    }

    vector<long long> dist(N + 1, 1e18);
    vector<int> parent(N + 1, -1);
    vector<int> edge_color(N + 1, -1);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[S] = 0;
    pq.push({0, S});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& [v, c] : adj[u]) {
            if (dist[u] + c < dist[v]) {
                dist[v] = dist[u] + c;
                parent[v] = u;
                edge_color[v] = c;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[T] == 1e18) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path;
    int cur = T;
    while (cur != S) {
        path.push_back(edge_color[cur]);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());

    if (path.size() > 1000000) {
        cout << "TOO LONG\n";
    } else {
        for (int i = 0; i < (int)path.size(); i++) {
            if (i) cout << " ";
            cout << path[i];
        }
        cout << "\n";
    }

    return 0;
}
