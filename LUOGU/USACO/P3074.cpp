#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> t(n + 1);
    for (int i = 1; i <= n; i++) cin >> t[i];
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        indeg[b]++;
    }
    // Topological sort with earliest start time
    vector<long long> finish(n + 1, 0);
    queue<int> q;
    for (int i = 1; i <= n; i++) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            finish[v] = max(finish[v], finish[u] + t[u]);
            if (--indeg[v] == 0) q.push(v);
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, finish[i] + t[i]);
    cout << ans << "\n";
    return 0;
}
