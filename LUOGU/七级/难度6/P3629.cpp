#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, K;
vector<int> adj[250001];
int sz[250001];
int ans = 0;

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void solve(int u, int p) {
    int mx = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        solve(v, u);
        mx = max(mx, sz[v]);
    }
    mx = max(mx, n - sz[u]);
    if (mx < K) ans++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> K;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, 0);
    solve(1, 0);
    
    cout << ans << endl;
    return 0;
}
