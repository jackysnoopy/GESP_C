#include <iostream>
#include <vector>
using namespace std;
vector<int> adj[10001];
int dp[10001][3]; // 0=自己有塔 1=被孩子覆盖 2=被父亲覆盖
void dfs(int u, int fa) {
    dp[u][0] = 1; dp[u][1] = 0; dp[u][2] = 1e9;
    int diff = 1e9;
    for (int v : adj[u]) {
        if (v == fa) continue;
        dfs(v, u);
        dp[u][0] += min(dp[v][0], min(dp[v][1], dp[v][2]));
        dp[u][2] += min(dp[v][0], dp[v][1]);
        dp[u][1] += min(dp[v][0], dp[v][1]);
        diff = min(diff, dp[v][0] - min(dp[v][0], dp[v][1]));
    }
    dp[u][1] += diff;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cout << min(dp[1][0], dp[1][1]) << "\n";
    return 0;
}
