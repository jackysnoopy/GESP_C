#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int n, s;
    while (cin >> n >> s && (n || s)) {
        int dp[301][21];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= s; j++) {
                for (int k = 0; k <= j; k++) {
                    dp[j][i] += dp[j - k][i - 1];
                }
            }
        }
        cout << dp[s][n] << endl;
    }
    return 0;
}
