#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> adj[100001];
int dist[100001];
void bfs(int s, vector<int>& d, int n) {
    for (int i = 1; i <= n; i++) d[i] = -1;
    d[s] = 0;
    vector<int> q; q.push_back(s);
    int idx = 0;
    while (idx < (int)q.size()) {
        int u = q[idx++];
        for (int v : adj[u])
            if (d[v] == -1) { d[v] = d[u]+1; q.push_back(v); }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dista(n+1), distb(n+1);
    bfs(1, dista, n);
    int a = 1;
    for (int i = 1; i <= n; i++) if (dista[i] > dista[a]) a = i;
    bfs(a, dista, n);
    int b = 1;
    for (int i = 1; i <= n; i++) if (dista[i] > dista[b]) b = i;
    bfs(b, distb, n);
    int center = 1;
    for (int i = 1; i <= n; i++)
        if (max(dista[i], distb[i]) < max(dista[center], distb[center]))
            center = i;
    vector<int> dcenter(n+1);
    bfs(center, dcenter, n);
    vector<int> dists;
    for (int i = 1; i <= n; i++) dists.push_back(dcenter[i]);
    sort(dists.begin(), dists.end());
    cout << dists[n-k] << "\n";
    return 0;
}
