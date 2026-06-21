#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    auto solve = [&](int l, int r) -> long long {
        if (l > r) return 0;
        int len = r - l + 1;
        if (len < m) return -1e18;
        vector<vector<long long>> dp(len+1, vector<long long>(m+1, -1e18));
        dp[0][0] = 0;
        for (int i = 1; i <= len; i++) {
            dp[i][0] = 0;
            for (int j = 1; j <= m; j++) {
                dp[i][j] = dp[i-1][j];
                if (i >= 2) dp[i][j] = max(dp[i][j], dp[i-2][j-1] + a[l+i-1]);
                else if (j == 1) dp[i][j] = max(dp[i][j], (long long)a[l+i-1]);
            }
        }
        return dp[len][m];
    };
    long long ans1 = solve(1, n-1);
    long long ans2 = a[0];
    if (m > 1) { long long r = solve(2, n-2); if(r > -1e17) ans2 += r; else ans2 = -1e18; }
    long long ans = max(ans1, ans2);
    if (ans < -1e17) cout << "Error!" << endl;
    else cout << ans << endl;
    return 0;
}