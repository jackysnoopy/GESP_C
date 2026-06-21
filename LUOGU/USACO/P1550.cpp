#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge { int u, v, w; };
int fa[305];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    vector<Edge> edges;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int p; cin >> p;
            if (i < j && p > 0) edges.push_back({i, j, p});
        }
    // Add virtual node 0 representing well-digging
    for (int i = 1; i <= n; i++) edges.push_back({0, i, w[i]});
    int total = n + 1;
    for (int i = 0; i <= n; i++) fa[i] = i;
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    int ans = 0, cnt = 0;
    for (auto& e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) { fa[fu] = fv; ans += e.w; cnt++; if (cnt == total - 1) break; }
    }
    cout << ans << "\n";
    return 0;
}
