#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF = 1e9;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, V, E; cin >> n >> m >> V >> E;
    vector<int> c(n + 1), d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    vector<double> k(n + 1);
    for (int i = 1; i <= n; ++i) cin >> k[i];
    vector<vector<int>> dist(V + 1, vector<int>(V + 1, INF));
    for (int i = 1; i <= V; ++i) dist[i][i] = 0;
    for (int i = 0; i < E; ++i) {
        int u, v, w; cin >> u >> v >> w;
        dist[u][v] = dist[v][u] = min(dist[u][v], w);
    }
    for (int k2 = 1; k2 <= V; ++k2)
        for (int i = 1; i <= V; ++i)
            for (int j = 1; j <= V; ++j)
                if (dist[i][k2] < INF && dist[k2][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k2] + dist[k2][j]);
    vector<vector<double>> dp(n + 1, vector<double>(m + 2, 1e18));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[i - 1][0] + dist[c[i - 1]][c[i]];
        for (int j = 1; j <= min(i, m); ++j) {
            double d00 = dist[c[i - 1]][c[i]];
            double d01 = dist[c[i - 1]][d[i]];
            double d10 = dist[d[i - 1]][c[i]];
            double d11 = dist[d[i - 1]][d[i]];
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + d00);
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + d00 * k[i] + d01 * (1 - k[i]));
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + d00 * k[i - 1] + d10 * (1 - k[i - 1]));
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] +
                d00 * k[i] * k[i - 1] + d01 * k[i] * (1 - k[i - 1]) +
                d10 * (1 - k[i]) * k[i - 1] + d11 * (1 - k[i]) * (1 - k[i - 1]));
        }
    }
    double ans = 1e18;
    for (int j = 0; j <= m; ++j) ans = min(ans, dp[n][j]);
    printf("%.2f\n", ans);
    return 0;
}
