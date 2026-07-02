#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, t;
    cin >> n >> m >> t;
    
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    
    // DP：dp[i][j] = 使用前i套轮胎跑j圈的最小时间
    // dp[i][j] = min(dp[i-1][k] + t + sum of a[i]+b[i]*(l-1)^2 for l=1..j-k)
    
    // 优化：对于每套轮胎i，计算跑l圈的时间
    // cost[i][l] = l*a[i] + b[i] * sum((k-1)^2 for k=1..l)
    //            = l*a[i] + b[i] * (l-1)*l*(2l-1)/6
    
    // 使用滚动数组
    vector<long long> dp(m + 1, 1e18);
    dp[0] = 0;
    
    for (int i = 0; i < n; i++) {
        vector<long long> ndp(m + 1, 1e18);
        
        // 预计算轮胎i跑l圈的成本
        vector<long long> cost(m + 1, 0);
        for (int l = 1; l <= m; l++) {
            cost[l] = cost[l-1] + a[i] + b[i] * (l-1) * (l-1);
        }
        
        for (int j = 0; j <= m; j++) {
            if (dp[j] >= 1e18) continue;
            // 使用轮胎i跑0圈
            ndp[j] = min(ndp[j], dp[j]);
            // 使用轮胎i跑l圈
            for (int l = 1; j + l <= m; l++) {
                long long newCost = dp[j] + (i > 0 ? t : 0) + cost[l];
                ndp[j + l] = min(ndp[j + l], newCost);
            }
        }
        
        dp = ndp;
    }
    
    cout << dp[m] << "\n";
    return 0;
}
