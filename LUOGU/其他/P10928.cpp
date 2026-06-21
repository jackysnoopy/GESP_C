#include <iostream>
#include <algorithm>
using namespace std;
struct Edge { int u, v, w; };
int fa[6001], sz[6001];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        Edge e[6001];
        for (int i = 0; i < n - 1; i++) cin >> e[i].u >> e[i].v >> e[i].w;
        sort(e, e + n - 1, [](const Edge& a, const Edge& b) { return a.w < b.w; });
        for (int i = 1; i <= n; i++) { fa[i] = i; sz[i] = 1; }
        long long ans = 0;
        for (int i = 0; i < n - 1; i++) {
            int ru = find(e[i].u), rv = find(e[i].v);
            long long w = e[i].w;
            // All edges between components must have weight > w
            // Minimum is w+1, so add sz[ru]*sz[rv]*(w+1-w) = sz[ru]*sz[rv]*1
            // Wait, the new edges must have weight > w, so minimum is w+1
            // But we want to minimize total weight
            // For each pair (u', v') where u' in component of u, v' in component of v
            // we need edge weight > w, so minimum is w+1
            ans += (long long)sz[ru] * sz[rv] * (w + 1) - (long long)sz[ru] * sz[rv] * w;
            // Actually: each new edge between the two components needs weight >= w+1
            // Total new edges: sz[ru]*sz[rv] - 1 (minus the MST edge)
            // Each costs w+1
            ans += (long long)(sz[ru] * sz[rv] - 1) * (w + 1);
            // Wait, let me reconsider. The original MST edge costs w.
            // All other edges between the two components must have weight > w, so >= w+1
            // Number of such edges: sz[ru]*sz[rv] - 1
            // Total cost from new edges: (sz[ru]*sz[rv] - 1) * (w+1)
            if (sz[ru] < sz[rv]) swap(ru, rv);
            fa[rv] = ru;
            sz[ru] += sz[rv];
        }
        cout << ans << "\n";
    }
    return 0;
}
