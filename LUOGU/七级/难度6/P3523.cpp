#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 300005;
vector<int> adj[MAXN];
int d[MAXN], has[MAXN], n, m, cnt;
int dfs(int u, int p, int mid) {
    int mx = -1e9;
    for (int v : adj[u]) {
        if (v == p) continue;
        int r = dfs(v, u, mid);
        mx = max(mx, r + 1);
    }
    if (has[u]) mx = max(mx, 0);
    if (mx >= mid) { cnt++; return -1e9; }
    return mx;
}
bool check(int mid) {
    cnt = 0;
    dfs(1, 0, mid);
    if (cnt > m) return false;
    if (cnt < m) return true;
    int r = dfs(1, 0, mid);
    return r < 0;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { int x; cin >> x; has[i] = x; }
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b); adj[b].push_back(a);
    }
    int lo = 0, hi = n, ans = n;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) { ans = mid; hi = mid - 1; }
        else lo = mid + 1;
    }
    cout << ans << endl;
    return 0;
}