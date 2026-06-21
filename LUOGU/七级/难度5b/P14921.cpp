#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int best_node = 0, best_val = INT_MAX;
    for (int s = 0; s < n; s++) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u])
                if (dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }
        }
        int maxd = *max_element(dist.begin(), dist.end());
        if (maxd < best_val) { best_val = maxd; best_node = s; }
    }
    cout << best_node + 1 << "\n";
    return 0;
}
