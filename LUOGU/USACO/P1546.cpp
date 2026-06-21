#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int fa[105];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Edge> edges;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int w; cin >> w;
            if (i < j && w > 0) edges.push_back({i, j, w});
        }
    for (int i = 1; i <= n; i++) fa[i] = i;
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    int ans = 0, cnt = 0;
    for (auto& e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) {
            fa[fu] = fv;
            ans += e.w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    cout << ans << "\n";
    return 0;
}
