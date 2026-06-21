#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n, m;
long long x[1001], y[1001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    // DP: for each subset of items, compute sum_x and sum_y
    // Then for each query (a,b), maximize min(a + sum_x, b + sum_y)
    // Since n <= 1000, we can't enumerate all subsets
    // But |sum_x| <= 10^5, so we can use DP on sum_x
    // DP[k] = maximum sum_y achievable with sum_x = k
    const int OFFSET = 100000;
    vector<long long> dp(2 * OFFSET + 1, -1e18);
    dp[OFFSET] = 0;
    for (int i = 0; i < n; i++) {
        if (x[i] >= 0) {
            for (int k = 2 * OFFSET; k >= x[i]; k--) {
                dp[k] = max(dp[k], dp[k - x[i]] + y[i]);
            }
        } else {
            for (int k = -x[i]; k <= 2 * OFFSET; k++) {
                dp[k] = max(dp[k], dp[k - x[i]] + y[i]);
            }
        }
    }
    cin >> m;
    while (m--) {
        long long a, b;
        cin >> a >> b;
        long long ans = max(a, b); // k=0 case
        for (int k = 0; k <= 2 * OFFSET; k++) {
            if (dp[k] > -1e17) {
                long long sx = k - OFFSET;
                ans = max(ans, min(a + sx, b + dp[k]));
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
