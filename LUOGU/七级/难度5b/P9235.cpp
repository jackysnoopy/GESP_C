#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100005;
const int LOG = 17;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const { return w > o.w; }
};

int n, m, q;
int parent[MAXN], rnk[MAXN];
int up[MAXN][LOG], minW[MAXN][LOG], dep[MAXN];
vector<pair<int,int>> tree[MAXN];
bool vis[MAXN];

int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }

bool unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return false;
    if (rnk[a] < rnk[b]) swap(a, b);
    parent[b] = a;
    if (rnk[a] == rnk[b]) rnk[a]++;
    return true;
}

void dfs(int u, int p, int w, int d) {
    vis[u] = true;
    up[u][0] = p;
    minW[u][0] = w;
    dep[u] = d;
    for (int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
        minW[u][i] = min(minW[u][i-1], minW[up[u][i-1]][i-1]);
    }
    for (size_t i = 0; i < tree[u].size(); i++) {
        int v = tree[u][i].first, ew = tree[u][i].second;
        if (v != p) dfs(v, u, ew, d + 1);
    }
}

int query(int a, int b) {
    if (!vis[a] || !vis[b]) return -1;
    if (find(a) != find(b)) return -1;
    if (a == b) return -1;
    int ans = 10000000;
    if (dep[a] < dep[b]) swap(a, b);
    int diff = dep[a] - dep[b];
    for (int i = 0; i < LOG; i++) {
        if (diff & (1 << i)) {
            ans = min(ans, minW[a][i]);
            a = up[a][i];
        }
    }
    if (a == b) return ans;
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[a][i] != up[b][i]) {
            ans = min(ans, min(minW[a][i], minW[b][i]));
            a = up[a][i];
            b = up[b][i];
        }
    }
    ans = min(ans, min(minW[a][0], minW[b][0]));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    sort(edges.begin(), edges.end());
    for (int i = 1; i <= n; i++) { parent[i] = i; rnk[i] = 0; }
    for (size_t i = 0; i < edges.size(); i++) {
        if (unite(edges[i].u, edges[i].v)) {
            tree[edges[i].u].push_back({edges[i].v, edges[i].w});
            tree[edges[i].v].push_back({edges[i].u, edges[i].w});
        }
    }
    memset(minW, 0x3f, sizeof(minW));
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i, i, 10000000, 0);
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << query(x, y) << "\n";
    }
    return 0;
}
