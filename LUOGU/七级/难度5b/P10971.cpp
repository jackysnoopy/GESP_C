#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> g(n);
    for (int i = 0; i < n; i++) cin >> g[i];

    // Sort by greedy degree in decreasing order
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) { return g[a] > g[b]; });

    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + g[order[i]];
    }

    // DP: dp[i][j] = minimum total anger for first i children using j cookies
    const long long INF = 1e18;
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == INF) continue;
            // Give next group k children (i+1..i+k) exactly c cookies
            for (int k = 1; k <= n - i; k++) {
                for (int c = 1; j + k * c <= m; c++) {
                    long long anger = (pref[i + k] - pref[i]) * i;
                    dp[i + k][j + k * c] = min(dp[i + k][j + k * c], dp[i][j] + anger);
                }
            }
        }
    }

    cout << dp[n][m] << "\n";

    // Reconstruct a valid assignment
    vector<int> cookies(n, 1);
    int remaining = m - n;
    for (int i = n - 1; i >= 0 && remaining > 0; i--) {
        int add = min(remaining, m - n);
        cookies[i] += add;
        remaining -= add;
    }

    for (int i = 0; i < n; i++) {
        cout << cookies[i] << (i + 1 < n ? " " : "\n");
    }

    return 0;
}
