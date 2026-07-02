#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1e5 + 5;
const int LOG = 17;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};

vector<Edge> edges;
int parent[MAXN], rank_[MAXN];
int up[MAXN][LOG], minEdge[MAXN][LOG], depth[MAXN];
vector<pair<int, int>> tree[MAXN];
bool visited[MAXN];

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank_[x] < rank_[y]) swap(x, y);
    parent[y] = x;
    if (rank_[x] == rank_[y]) rank_[x]++;
}

void dfs(int u, int p, int w, int d) {
    visited[u] = true;
    up[u][0] = p;
    minEdge[u][0] = w;
    depth[u] = d;
    
    for (int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
        minEdge[u][i] = min(minEdge[u][i-1], minEdge[up[u][i-1]][i-1]);
    }
    
    for (auto& [v, weight] : tree[u]) {
        if (!visited[v]) {
            dfs(v, u, weight, d + 1);
        }
    }
}

int query(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    int ans = 1e9;
    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            ans = min(ans, minEdge[u][i]);
            u = up[u][i];
        }
    }
    
    if (u == v) return ans;
    
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            ans = min(ans, min(minEdge[u][i], minEdge[v][i]));
            u = up[u][i];
            v = up[v][i];
        }
    }
    
    return min(ans, min(minEdge[u][0], minEdge[v][0]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank_[i] = 0;
        visited[i] = false;
    }
    
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    
    sort(edges.begin(), edges.end());
    
    for (auto& e : edges) {
        if (find(e.u) != find(e.v)) {
            unite(e.u, e.v);
            tree[e.u].push_back({e.v, e.w});
            tree[e.v].push_back({e.u, e.w});
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            up[i][0] = i;
            minEdge[i][0] = 1e9;
            dfs(i, i, 1e9, 0);
        }
    }
    
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (find(u) != find(v)) {
            cout << -1 << "\n";
        } else {
            cout << query(u, v) << "\n";
        }
    }
    
    return 0;
}