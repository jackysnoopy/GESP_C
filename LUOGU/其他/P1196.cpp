#include <iostream>
#include <cmath>
using namespace std;
const int MAXN = 30001;
int fa[MAXN], sz[MAXN], dist[MAXN];
int find(int x) {
    if (fa[x] == x) return x;
    int r = find(fa[x]);
    dist[x] += dist[fa[x]];
    fa[x] = r; return r;
}
void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    fa[x] = y; dist[x] = sz[y]; sz[y] += sz[x];
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    for (int i = 1; i < MAXN; ++i) { fa[i] = i; sz[i] = 1; dist[i] = 0; }
    int T; cin >> T;
    while (T--) {
        char op; int x, y;
        cin >> op >> x >> y;
        if (op == 'M') merge(x, y);
        else {
            if (find(x) != find(y)) cout << -1 << '\n';
            else cout << abs(dist[x] - dist[y]) - 1 << '\n';
        }
    }
    return 0;
}
