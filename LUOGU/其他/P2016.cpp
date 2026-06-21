#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
int dp[1505][2];

void dfs(int u, int p) {
    dp[u][0] = 0;
    dp[u][1] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n; i++) {
        int id, k; cin >> id >> k;
        for (int j = 0; j < k; j++) {
            int v; cin >> v;
            adj[id].push_back(v);
            adj[v].push_back(id);
        }
    }
    dfs(0, -1);
    cout << min(dp[0][0], dp[0][1]) << "\n";
    return 0;
}
