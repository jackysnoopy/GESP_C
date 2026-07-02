#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 305;
const int MOD = 1000000007;

long long dp[MAXN][MAXN];

int main() {
    int n;
    while (cin >> n && n) {
        memset(dp, 0, sizeof(dp));
        dp[1][1] = 1;
        
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i][j] = (dp[i-1][j-1] + (i-1) * dp[i-1][j]) % MOD;
            }
        }
        
        long long ans = 0;
        for (int j = 1; j <= n; j++) {
            ans = (ans + dp[n][j]) % MOD;
        }
        cout << ans << "\n";
    }
    return 0;
}
