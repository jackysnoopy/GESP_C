#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<bool> vis;

int dfs(int u) {
    vis[u] = true;
    int cnt = 1;
    for (int v : adj[u]) {
        if (!vis[v]) cnt += dfs(v);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        adj.assign(n + 1, vector<int>());
        vis.assign(n + 1, false);
        for (int i = 0; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int ans = 2;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                int sz = dfs(i);
                if (sz % 2 == 1) {
                    ans = 3;
                    break;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
