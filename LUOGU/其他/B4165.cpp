#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
const int LOG = 18;

struct Edge {
    int u, v, w;
};

int par[MAXN], dep[MAXN], up[MAXN][LOG];
int mx[MAXN][LOG], mn[MAXN][LOG];
vector<pair<int,int>> adj[MAXN];

int find(int x) {
    while (par[x] != x) par[x] = par[par[x]], x = par[x];
    return x;
}

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
        mx[u][i] = max(mx[u][i-1], mx[up[u][i-1]][i-1]);
        mn[u][i] = min(mn[u][i-1], mn[up[u][i-1]][i-1]);
    }
    for (auto &e : adj[u]) {
        int v = e.first, w = e.second;
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        mx[v][0] = mn[v][0] = w;
        dfs(v, u);
    }
}

pair<int,int> query(int a, int b) {
    int retmx = 0, retmn = 1e9 + 1;
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = LOG - 1; i >= 0; i--) {
        if (dep[a] - (1 << i) >= dep[b]) {
            retmx = max(retmx, mx[a][i]);
            retmn = min(retmn, mn[a][i]);
            a = up[a][i];
        }
    }
    if (a == b) return {retmx, retmn};
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[a][i] != up[b][i]) {
            retmx = max(retmx, max(mx[a][i], mx[b][i]));
            retmn = min(retmn, min(mn[a][i], mn[b][i]));
            a = up[a][i];
            b = up[b][i];
        }
    }
    retmx = max(retmx, max(mx[a][0], mx[b][0]));
    retmn = min(retmn, min(mn[a][0], mn[b][0]));
    return {retmx, retmn};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    for (int i = 1; i <= n; i++) par[i] = i;
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });
    for (auto &e : edges) {
        int pu = find(e.u), pv = find(e.v);
        if (pu != pv) {
            par[pu] = pv;
            adj[e.u].push_back({e.v, e.w});
            adj[e.v].push_back({e.u, e.w});
        }
    }
    mx[1][0] = 0;
    mn[1][0] = 1e9 + 1;
    dfs(1, 1);
    while (k--) {
        int t;
        cin >> t;
        pair<int,int> res = query(1, t);
        cout << res.first - res.second + 1 << "\n";
    }
    return 0;
}
