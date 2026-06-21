#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n), r(n, 1) { for (int i = 0; i < n; i++) p[i] = i; }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x;
        if (r[x] == r[y]) r[x]++;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    // Edge weight: max(a_i, a_j) + max(b_i, b_j)
    // For MST, we need O(n log n) edges.
    // Sort by a_i. For each node, connect to neighbors in sorted order.
    // Also sort by b_i and connect neighbors.
    
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    
    struct Edge { long long w; int u, v; };
    vector<Edge> edges;
    
    // Sort by a, connect adjacent pairs
    sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; });
    for (int i = 0; i < n - 1; i++) {
        int u = idx[i], v = idx[i+1];
        long long w = max(a[u], a[v]) + max(b[u], b[v]);
        edges.push_back({w, u, v});
    }
    
    // Sort by b, connect adjacent pairs
    sort(idx.begin(), idx.end(), [&](int i, int j) { return b[i] < b[j]; });
    for (int i = 0; i < n - 1; i++) {
        int u = idx[i], v = idx[i+1];
        long long w = max(a[u], a[v]) + max(b[u], b[v]);
        edges.push_back({w, u, v});
    }
    
    // Sort edges by weight and run Kruskal
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    
    DSU dsu(n);
    long long total = 0;
    vector<pair<int,int>> tree_edges;
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            tree_edges.push_back({e.u, e.v});
            if ((int)tree_edges.size() == n - 1) break;
        }
    }
    
    cout << total << "\n";
    for (auto& e : tree_edges) {
        cout << e.first + 1 << " " << e.second + 1 << "\n";
    }
    
    return 0;
}
