#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 10005;
vector<pair<int,long long>> adj[MAXN];
long long vis[MAXN], xor_to[MAXN];
long long basis[64]; int bcnt = 0;
void insert(long long x) {
    for (int i = 62; i >= 0; --i) {
        if (!((x >> i) & 1)) continue;
        if (!basis[i]) { basis[i] = x; bcnt++; return; }
        x ^= basis[i];
    }
}
void dfs(int u) {
    vis[u] = 1;
    for (auto &e : adj[u]) {
        int v = e.first; long long w = e.second;
        if (!vis[v]) { xor_to[v] = xor_to[u] ^ w; dfs(v); }
        else insert(xor_to[u] ^ xor_to[v] ^ w);
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; long long w; cin >> u >> v >> w;
        adj[u].push_back({v, w}); adj[v].push_back({u, w});
    }
    dfs(1);
    long long ans = xor_to[n];
    for (int i = 62; i >= 0; --i)
        ans = max(ans, ans ^ basis[i]);
    cout << ans << '\n';
    return 0;
}
