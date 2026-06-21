#include <iostream>
#include <algorithm>
using namespace std;
int n, a[250], dp[250][250], ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    ans = *max_element(a, a+n);
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i+len <= n; i++) {
            int j = i+len-1;
            for (int k = i; k < j; k++) {
                if (dp[i][k] && dp[i][k] == dp[k+1][j]) {
                    dp[i][j] = max(dp[i][j], dp[i][k]+1);
                }
            }
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << "\n";
    return 0;
}
