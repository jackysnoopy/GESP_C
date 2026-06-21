#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 10005;
const int LOGN = 14;
struct Edge { int u, v, w; };
int fa[MAXN], dep[MAXN], mn[MAXN][LOGN], par[MAXN][LOGN];
vector<pair<int,int>> adj[MAXN];
bool vis[MAXN];
void dfs(int u, int p, int d, int w) {
    vis[u] = true;
    fa[u] = p;
    dep[u] = d;
    mn[u][0] = w;
    par[u][0] = p;
    for (int i = 1; i < LOGN; i++) {
        par[u][i] = par[par[u][i-1]][i-1];
        mn[u][i] = min(mn[u][i-1], mn[par[u][i-1]][i-1]);
    }
    for (auto& e : adj[u]) {
        if (!vis[e.first]) dfs(e.first, u, d+1, e.second);
    }
}
int query(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int ans = 1e9;
    for (int i = LOGN-1; i >= 0; i--)
        if (dep[par[u][i]] >= dep[v]) { ans = min(ans, mn[u][i]); u = par[u][i]; }
    if (u == v) return ans;
    for (int i = LOGN-1; i >= 0; i--)
        if (par[u][i] != par[v][i]) { ans = min(ans, min(mn[u][i], mn[v][i])); u = par[u][i]; v = par[v][i]; }
    ans = min(ans, min(mn[u][0], mn[v][0]));
    return ans;
}
bool cmp(const Edge& a, const Edge& b) { return a.w > b.w; }
int f[MAXN];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) cin >> edges[i].u >> edges[i].v >> edges[i].w;
    sort(edges.begin(), edges.end(), cmp);
    for (int i = 1; i <= n; i++) f[i] = i;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (find(u) != find(v)) {
            f[find(u)] = find(v);
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i]) { par[i][0] = i; mn[i][0] = 1e9; dfs(i, 0, 0, 1e9); }
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (find(x) != find(y)) cout << -1 << endl;
        else cout << query(x, y) << endl;
    }
    return 0;
}