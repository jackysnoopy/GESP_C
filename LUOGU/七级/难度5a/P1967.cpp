#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 10005;
const int LOG = 15;

struct Edge {
    int u, v, w;
};

int n, m, q;
Edge edges[50005];
int dsu[MAXN], dep[MAXN], anc[MAXN][LOG], mn[MAXN][LOG];
bool vis[MAXN];
vector<pair<int,int>> g[MAXN];

int find(int x) {
    return dsu[x] == x ? x : dsu[x] = find(dsu[x]);
}

void kruskal() {
    for (int i = 1; i <= n; i++) dsu[i] = i;
    sort(edges, edges + m, [](const Edge& a, const Edge& b) {
        return a.w > b.w;
    });
    int cnt = 0;
    for (int i = 0; i < m && cnt < n - 1; i++) {
        int u = find(edges[i].u), v = find(edges[i].v);
        if (u != v) {
            dsu[u] = v;
            g[edges[i].u].push_back({edges[i].v, edges[i].w});
            g[edges[i].v].push_back({edges[i].u, edges[i].w});
            cnt++;
        }
    }
}

void dfs(int u, int p, int w, int d) {
    vis[u] = true;
    dep[u] = d;
    anc[u][0] = p;
    mn[u][0] = w;
    for (int i = 1; i < LOG; i++) {
        int mid = anc[u][i-1];
        anc[u][i] = anc[mid][i-1];
        mn[u][i] = min(mn[u][i-1], mn[mid][i-1]);
    }
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i].first;
        int w2 = g[u][i].second;
        if (!vis[v]) dfs(v, u, w2, d + 1);
    }
}

int query(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int ans = 1e9;
    for (int i = LOG - 1; i >= 0; i--) {
        if (dep[anc[x][i]] >= dep[y]) {
            ans = min(ans, mn[x][i]);
            x = anc[x][i];
        }
    }
    if (x == y) return ans;
    for (int i = LOG - 1; i >= 0; i--) {
        if (anc[x][i] != anc[y][i]) {
            ans = min(ans, min(mn[x][i], mn[y][i]));
            x = anc[x][i];
            y = anc[y][i];
        }
    }
    ans = min(ans, min(mn[x][0], mn[y][0]));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    kruskal();
    memset(anc, 0, sizeof(anc));
    memset(mn, 0x3f, sizeof(mn));
    memset(dep, 0, sizeof(dep));
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, 0, 0x3f3f3f3f, 0);
        }
    }
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (find(x) != find(y)) cout << "-1\n";
        else cout << query(x, y) << "\n";
    }
    return 0;
}
