#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    vector<vector<pair<int,long long>>> g(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        long long cost = 1;
        if (v[x] > v[y]) cost = -(v[x] - v[y]) + 1;
        else cost = (v[y] - v[x]) + 1;
        g[x].push_back(make_pair(y, cost));
    }
    vector<long long> dist(n, LLONG_MAX);
    dist[a] = 0;
    queue<int> q;
    q.push(a);
    vector<bool> inq(n, false);
    inq[a] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (auto &pr : g[u]) {
            int v = pr.first;
            long long w = pr.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inq[v]) { q.push(v); inq[v] = true; }
            }
        }
    }
    if (dist[b] == LLONG_MAX) cout << "No solution\n";
    else cout << dist[b] << "\n";
    return 0;
}
