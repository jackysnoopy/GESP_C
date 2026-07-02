#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 2000005;
vector<int> adj[MAXN];
int c[MAXN], n, m, ans;
int dfs(int u) {
    int cnt = 0;
    for (int v : adj[u]) cnt += dfs(v);
    cnt += c[u];
    if (cnt >= m) { ans++; return 0; }
    return cnt;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        int k; cin >> k;
        for (int j = 0; j < k; j++) { int v; cin >> v; adj[i].push_back(v); }
    }
    dfs(0);
    cout << ans << endl;
    return 0;
}