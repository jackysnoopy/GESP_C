#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, P, Q;
        cin >> n >> P >> Q;
        vector<int> p(n), c(n);
        for (int i = 0; i < n; i++) cin >> p[i] >> c[i];
        // dp[s] = min cost to achieve total strength s (cap at P)
        // Any strength >= P is treated as P
        vector<int> dp(P + 1, 1e9);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int s = P; s >= 0; s--) {
                int ns = min(P, s + p[i]);
                dp[ns] = min(dp[ns], dp[s] + c[i]);
            }
        }
        if (dp[P] <= Q) cout << dp[P] << "\n";
        else cout << -1 << "\n";
    }
    return 0;
}
