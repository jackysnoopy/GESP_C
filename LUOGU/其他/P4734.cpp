#include <iostream>
using namespace std;
long long dp[1001][1001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i-1][j];
            if (j > 0) dp[i][j] += dp[i][j-1];
        }
    }
    cout << dp[n][m] << "\n";
    return 0;
}
