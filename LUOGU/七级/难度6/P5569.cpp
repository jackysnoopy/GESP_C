#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 305;
const long long INF = 1e18;

long long a[MAXN], sum[MAXN];
long long dp[MAXN][MAXN];
int opt[MAXN][MAXN];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;
            for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                long long val = dp[i][k] + dp[k + 1][j];
                if (val < dp[i][j]) {
                    dp[i][j] = val;
                    opt[i][j] = k;
                }
            }
            dp[i][j] += sum[j] - sum[i - 1];
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}
