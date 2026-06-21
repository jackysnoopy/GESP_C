#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; long long k;
    cin >> n >> m >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // dp[i] = min cost to pack oranges 1..i (1-indexed).
    // dp[0] = 0.
    // dp[i] = min over j in [max(1, i-m+1), i] of dp[j-1] + k + (i-j+1) * (max(a[j..i]) - min(a[j..i])).
    //
    // For n <= 20000, m <= 1000: O(n*m) = 2e7. Acceptable.
    // But computing max/min for each [j,i] is O(m) per state, making it O(n*m^2) = 2e10. Too slow.
    //
    // Optimization: iterate j from i down to max(1, i-m+1), maintaining max and min.
    vector<long long> dp(n + 1, 1e18);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        long long cur_max = a[i - 1], cur_min = a[i - 1];
        for (int j = i; j >= max(1, i - m + 1); j--) {
            cur_max = max(cur_max, a[j - 1]);
            cur_min = min(cur_min, a[j - 1]);
            long long cost = dp[j - 1] + k + (i - j + 1) * (cur_max - cur_min);
            dp[i] = min(dp[i], cost);
        }
    }
    cout << dp[n] << "\n";
    return 0;
}
