#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
long long A[20], B[20];
long long dp[20][201];
long long cost(int x, int i) {
    if (x == 0) return 0;
    long long res = A[i];
    for (int j = 1; j < (int)B[i]; j++) res *= x;
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> A[i] >> B[i];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[i][j] >= 0x3f3f3f3f3f3f3f3fLL) continue;
            for (int k = 0; j + k <= n; k++) {
                dp[i + 1][j + k] = min(dp[i + 1][j + k], dp[i][j] + cost(k, i));
            }
        }
    }
    cout << dp[m][n] << "\n";
    return 0;
}
