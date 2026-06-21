#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int fa[500001], rk[500001], dist[500001];
int find(int x) {
    if (fa[x] == x) return x;
    int r = find(fa[x]);
    dist[x] ^= dist[fa[x]];
    fa[x] = r; return r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> vals = {0};
    vector<tuple<int,int,int>> cons;
    for (int i = 0; i < n; ++i) {
        int a,b; string s;
        cin >> a >> b >> s;
        int t = (s == "odd") ? 1 : 0;
        vals.push_back(a-1); vals.push_back(b);
        cons.push_back({a-1, b, t});
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto getId = [&](int x) { return lower_bound(vals.begin(), vals.end(), x) - vals.begin(); };
    int m = vals.size();
    for (int i = 0; i < m; ++i) { fa[i] = i; rk[i] = 0; dist[i] = 0; }
    int ans = n;
    for (int i = 0; i < n; ++i) {
        int a,b,t; tie(a,b,t) = cons[i];
        a = getId(a); b = getId(b);
        int ra = find(a), rb = find(b);
        if (ra == rb) {
            if ((dist[a] ^ dist[b]) != t) { ans = i; break; }
        } else {
            if (rk[ra] < rk[rb]) { fa[ra] = rb; dist[ra] = dist[a] ^ dist[b] ^ t; }
            else { fa[rb] = ra; dist[rb] = dist[a] ^ dist[b] ^ t; if (rk[ra] == rk[rb]) rk[ra]++; }
        }
    }
    cout << ans << '\n';
    return 0;
}
