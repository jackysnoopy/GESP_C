#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, k;
vector<vector<int>> adj;
int ans;
int dfs(int u, int parent) {
    vector<int> ds;
    ds.push_back(0);
    for (int v : adj[u]) {
        if (v == parent) continue;
        int hv = dfs(v, u);
        if (hv >= 0) ds.push_back(hv + 1);
    }
    sort(ds.begin(), ds.end(), greater<int>());
    int d1 = ds[0];
    int d2 = (ds.size() >= 2) ? ds[1] : 0;
    if (d1 + d2 >= k) {
        ans++;
        return -1;
    }
    return d1;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    ans = 0;
    dfs(1, 0);
    cout << ans << "\n";
    return 0;
}
