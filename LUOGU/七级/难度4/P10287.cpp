#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) if (indeg[i] == 0) q.push(i);
    vector<vector<int>> dp(n + 1, vector<int>(11, 0));
    vector<vector<int>> merged(n + 1, vector<int>(11, 0));
    int ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int k = 1; k <= 10; k++) dp[u][k] = merged[u][k];
        int maxBelow = 0;
        for (int k = 1; k <= a[u]; k++) maxBelow = max(maxBelow, dp[u][k]);
        dp[u][a[u]] = max(dp[u][a[u]], maxBelow + 1);
        for (int k = 1; k <= 10; k++) ans = max(ans, dp[u][k]);
        for (int v : g[u]) {
            for (int k = 1; k <= 10; k++) merged[v][k] = max(merged[v][k], dp[u][k]);
            if (--indeg[v] == 0) q.push(v);
        }
    }
    cout << ans << "\n";
    return 0;
}
