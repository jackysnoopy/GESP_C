#include <iostream>
using namespace std;
const int MAXN = 50001;
int fa[MAXN], dist[MAXN];
int find(int x) {
    if (fa[x] == x) return x;
    int r = find(fa[x]);
    dist[x] = (dist[x] + dist[fa[x]]) % 3;
    fa[x] = r; return r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) { fa[i] = i; dist[i] = 0; }
    int ans = 0;
    while (m--) {
        int t, x, y; cin >> t >> x >> y;
        if (x > n || y > n) { ans++; continue; }
        int rx = find(x), ry = find(y);
        if (t == 1) {
            if (rx == ry && (dist[x] - dist[y] + 3) % 3 != 0) ans++;
            else if (rx != ry) { fa[rx] = ry; dist[rx] = (dist[y] - dist[x] + 3) % 3; }
        } else {
            if (rx == ry && (dist[x] - dist[y] + 3) % 3 != 1) ans++;
            else if (rx != ry) { fa[rx] = ry; dist[rx] = (dist[y] - dist[x] + 2) % 3; }
        }
    }
    cout << ans << '\n';
    return 0;
}
