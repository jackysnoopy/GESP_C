#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 20001;
vector<pair<int,int>> adj[MAXN];
int sz[MAXN], mx[MAXN], vis[MAXN], n, K;
long long ans;
void get_sz(int u, int p) {
    sz[u] = 1; mx[u] = 0;
    for (auto &e : adj[u]) {
        int v = e.first; if (v == p || vis[v]) continue;
        get_sz(v, u); sz[u] += sz[v]; mx[u] = max(mx[u], sz[v]);
    }
}
int get_cen(int u, int p, int tot) {
    mx[u] = max(mx[u], tot - sz[u]);
    for (auto &e : adj[u]) {
        int v = e.first;
        if (v == p || vis[v]) continue;
        int c = get_cen(v, u, tot);
        if (c >= 0) return c;
    }
    if (mx[u] <= tot / 2) return u;
    return -1;
}
vector<int> dists;
void get_dist(int u, int p, int d) {
    dists.push_back(d);
    for (auto &e : adj[u]) {
        int v = e.first, w = e.second;
        if (v == p || vis[v]) continue;
        get_dist(v, u, d + w);
    }
}
void calc(int u) {
    vis[u] = 1;
    vector<int> all = {0};
    for (auto &e : adj[u]) {
        int v = e.first, w = e.second;
        if (vis[v]) continue;
        dists.clear();
        get_dist(v, u, w);
        sort(dists.begin(), dists.end());
        for (int d : dists) {
            int cnt = upper_bound(all.begin(), all.end(), K - d) - all.begin();
            ans += cnt;
        }
        for (int d : dists) all.push_back(d);
        sort(all.begin(), all.end());
    }
    for (auto &e : adj[u]) {
        int v = e.first;
        if (vis[v]) continue;
        get_sz(v, 0);
        int c = get_cen(v, 0, sz[v]);
        if (c >= 0) calc(c);
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w}); adj[v].push_back({u, w});
    }
    cin >> K;
    get_sz(1, 0);
    int c = get_cen(1, 0, n);
    calc(c);
    cout << ans << '\n';
    return 0;
}
