#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, H, Delta;
    cin >> N >> H >> Delta;
    static int dp[2005][2005];
    static int cnt[2005][2005];
    static int suffix[2006];
    memset(dp, 0, sizeof(dp));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < N; i++) {
        int ki;
        cin >> ki;
        for (int j = 0; j < ki; j++) { int t; cin >> t; if (t >= 0 && t <= H) cnt[i][t]++; }
    }
    for (int j = 0; j <= H; j++) { if (j <= 1) dp[0][j] = cnt[0][j]; }
    for (int i = 1; i < N; i++) {
        suffix[H + 1] = 0;
        for (int j = H; j >= 0; j--) suffix[j] = max(suffix[j + 1], dp[i - 1][j]);
        for (int j = 0; j <= H; j++) {
            int best = dp[i - 1][j];
            if (j + 1 <= H) best = max(best, dp[i - 1][j + 1]);
            best = max(best, suffix[j + 1]);
            dp[i][j] = best + cnt[i][j];
        }
    }
    int ans = 0;
    for (int j = 0; j <= H; j++) ans = max(ans, dp[N - 1][j]);
    cout << ans << "\n";
    return 0;
}
