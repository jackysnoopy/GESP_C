#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, d, s;
    cin >> n >> k >> d >> s;
    vector<pair<int,int>> taxis(k);
    for (int i = 0; i < k; i++) cin >> taxis[i].first >> taxis[i].second;
    // dp[i][j] = min cost to send i people using first j taxis
    // Use greedy: assign people to earliest taxis that fit
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 1e18));
    dp[0][0] = 0;
    for (int j = 1; j <= k; j++) {
        for (int i = 0; i <= n; i++) dp[i][j] = dp[i][j-1];
        int t = taxis[j-1].first, z = taxis[j-1].second;
        for (int i = 0; i <= n; i++) {
            if (dp[i][j-1] < 1e18) {
                int take = min(z, n - i);
                long long cost = dp[i][j-1] + (long long)take * t + (long long)take * d;
                if (cost < dp[i + take][j]) dp[i + take][j] = cost;
            }
        }
    }
    if (dp[n][k] >= 1e18) cout << "impossible\n";
    else cout << dp[n][k] << "\n";
    return 0;
}
