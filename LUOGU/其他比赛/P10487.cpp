#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> matchL, matchR;
vector<bool> vis;

bool dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v]) continue;
        vis[v] = true;
        if (matchR[v] == 0 || dfs(matchR[v])) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    adj.resize(n + 1);
    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
    for (int i = 1; i <= n; ++i) reach[i][i] = true;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        reach[u][v] = true;
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (i != j && reach[i][j]) adj[i].push_back(j);
    matchL.assign(n + 1, 0);
    matchR.assign(n + 1, 0);
    int match = 0;
    for (int i = 1; i <= n; ++i) {
        vis.assign(n + 1, false);
        if (dfs(i)) match++;
    }
    cout << n - match << '\n';
    return 0;
}
