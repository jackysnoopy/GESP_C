#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u != v) { // ignore self-loops
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    vector<bool> vis(n + 1, false);
    int comps = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            comps++;
            queue<int> q;
            q.push(i);
            vis[i] = true;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : g[u])
                    if (!vis[v]) { vis[v] = true; q.push(v); }
            }
        }
    }
    cout << comps - 1 << "\n";
    return 0;
}
