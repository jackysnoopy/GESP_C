#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<long long>> dp(n + 2, vector<long long>(n + 2, 0));
    for (int len = 2; len <= n + 1; len++) {
        for (int i = 0; i + len <= n + 1; i++) {
            int j = i + len;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + a[i] + a[j]);
            }
        }
    }

    cout << dp[0][n + 1] << "\n";
    return 0;
}
