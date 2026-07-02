#include <iostream>
#include <cstring>
using namespace std;

int N, T, M;
int t[105], m[105];
int dp[1005][1005];

int main() {
    int P;
    cin >> P;
    while (P--) {
        cin >> N >> T >> M;
        for (int i = 1; i <= N; i++)
            cin >> t[i] >> m[i];

        memset(dp, -1, sizeof(dp));
        dp[0][0] = 0;

        for (int i = 1; i <= N; i++) {
            for (int j = T; j >= 0; j--) {
                for (int k = M; k >= 0; k--) {
                    if (dp[j][k] >= 0) {
                        int nj = j + t[i];
                        int nk = k + m[i];
                        if (nj <= T && nk <= M) {
                            dp[nj][nk] = max(dp[nj][nk], dp[j][k] + 1);
                        }
                    }
                }
            }
        }

        int ans = 0;
        for (int j = 0; j <= T; j++)
            for (int k = 0; k <= M; k++)
                ans = max(ans, dp[j][k]);

        cout << ans << endl;
    }
    return 0;
}
