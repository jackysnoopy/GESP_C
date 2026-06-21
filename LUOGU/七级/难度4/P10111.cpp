#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n - 1), c(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) cin >> b[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    
    // 1胜0, 2胜1, 0胜2 => my胜opp 当 (my+2)%3==opp
    auto score = [&](int round, int my) {
        int opp = c[round];
        if (my == opp) return a[round];
        if ((my + 2) % 3 == opp) return 2 * a[round];
        return 0;
    };
    
    // dp[j][t] = 当前轮出j，已换t次牌时的最大得分（已扣除罚分）
    const long long NEG = LLONG_MIN / 2;
    vector<vector<long long>> dp(3, vector<long long>(n, NEG));
    for (int j = 0; j < 3; j++) dp[j][0] = score(0, j);
    
    for (int i = 1; i < n; i++) {
        vector<vector<long long>> ndp(3, vector<long long>(n, NEG));
        for (int j = 0; j < 3; j++) { // 上一轮出的牌
            for (int t = 0; t < i; t++) { // 之前换了t次
                if (dp[j][t] == NEG) continue;
                // 不换牌，继续出j
                ndp[j][t] = max(ndp[j][t], dp[j][t] + score(i, j));
                // 换牌到k
                for (int k = 0; k < 3; k++) {
                    if (k == j) continue;
                    ndp[k][t+1] = max(ndp[k][t+1], dp[j][t] + score(i, k) - b[t]);
                }
            }
        }
        dp = ndp;
    }
    
    long long ans = LLONG_MIN;
    for (int j = 0; j < 3; j++)
        for (int t = 0; t < n; t++)
            if (dp[j][t] != NEG) ans = max(ans, dp[j][t]);
    cout << ans << "\n";
    return 0;
}
