#include <iostream>
#include <cstring>
using namespace std;
int t[5][10];
int dp[6][26];
int pre[6][26];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 10; j++)
            cin >> t[i][j];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= 25; j++) {
            if (dp[i][j] >= 0x3f3f3f3f) continue;
            for (int k = 1; k <= 10 && j + k <= 25; k++) {
                if (dp[i][j] + t[i][k - 1] < dp[i + 1][j + k]) {
                    dp[i + 1][j + k] = dp[i][j] + t[i][k - 1];
                    pre[i + 1][j + k] = k;
                }
            }
        }
    }
    cout << dp[5][25] << "\n";
    int rem = 25;
    int ans[5];
    for (int i = 4; i >= 0; i--) {
        ans[i] = pre[i + 1][rem];
        rem -= ans[i];
    }
    for (int i = 0; i < 5; i++) { if (i) cout << " "; cout << ans[i]; }
    cout << "\n";
    return 0;
}
